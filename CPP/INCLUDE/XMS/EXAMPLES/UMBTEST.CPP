//--------------------------------------------------------------------------
//
//      UMBTEST.CPP: Test program for UMB class.
//      Copyright (c) J.English 1993.
//      Author's address: je@unix.brighton.ac.uk
//
//      Permission is granted to use copy and distribute the
//      information contained in this file provided that this
//      copyright notice is retained intact and that any software
//      or other document incorporating this file or parts thereof
//      makes the source code for the library of which this file
//      is a part freely available.
//
//--------------------------------------------------------------------------
//
//      Revision history:
//      2.0     Nov 1993        Initial coding
//
//--------------------------------------------------------------------------

#include "xms.h"
#include "doserror.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//--------------------------------------------------------------------------
//
//      Global data.
//
DOSerror e;             // guard against critical errors and control-breaks
UMB* desc [10];         // array of pointers to UMB descriptors
int ndesc = 0;          // number of descriptors


//--------------------------------------------------------------------------
//
//      Function prototypes.
//
char menu ();           // display menu & get user's choice
void UMBstats ();       // 1. UMB statistics
void blocksizes ();     // 2. List block sizes
void allocate ();       // 3. Allocate block
void deallocate ();     // 4. Deallocate block
void copy ();           // 5. Copy block

//--------------------------------------------------------------------------
//
//      Main program.
//
//      A menu of choices is displayed, allowing the user to exercise
//      each of the UMB functions available.
//
void main ()
{
    char choice;
    UMBstats ();
    for (;;)
    {
        choice = menu ();
        if (choice == 'X')
            break;

        switch (choice)
        {
            case '1':
                UMBstats ();
                break;
            case '2':
                blocksizes ();
                break;
            case '3':
                allocate ();
                break;
            case '4':
                deallocate ();
                break;
            case '5':
                copy ();
                break;
        }
    }
    for (int i = 0; i < ndesc; i++)
        delete desc[i];
}

//--------------------------------------------------------------------------
//
//      Display menu and get user choice.
//
//      The choice must be a line containing a single character from 1 to 4
//      (or X for exit).
//
char menu ()
{
    printf ("\nChoose desired operation:\n"
            "  1) Display UMB statistics\n"
            "  2) List block sizes\n"
            "  3) Allocate block\n"
            "  4) Deallocate block\n"
            "  5) Copy block\n"
            "  X) Exit program\n");
    char buff [80];
    for (;;)
    {
        printf ("Enter your choice: ");
        fgets (buff, 80, stdin);
        if ((buff[0] == 'x' || buff[0] == 'X') && buff[1] == '\n')
            return 'X';
        if (buff[0] < '1' || buff[0] > '5' || buff[1] != '\n')
            printf ("Invalid choice!\a\n");
        else
            break;
    }
    printf ("\n");
    return buff[0];
}


//--------------------------------------------------------------------------
//
//      Display UMB statistics.
//
void UMBstats ()
{
    printf ("Largest available UMB block: %ld bytes.\n", UMB::largest());
}


//--------------------------------------------------------------------------
//
//      List block sizes.
//
void blocksizes ()
{
    int flag = 0;
    for (int i = 0; i < ndesc; i++)
    {   if (desc[i] != 0)
        {   printf ("Block %d: size = %ld\n", i+1, desc[i]->size());
            flag = 1;
        }
    }
    if (flag == 0)
        printf ("No blocks allocated!\n");
}

//--------------------------------------------------------------------------
//
//      Allocate block.
//
//      Attempt to allocate a new block of a specified size and report the
//      result.
//
void allocate ()
{
    printf ("Enter block size: ");
    long size;
    scanf ("%ld", &size);
    while (getchar() != '\n')
        continue;
    desc [ndesc++] = new UMB (size);
    printf ("Block %d: ", ndesc);
    printf ("requested %ld bytes, granted %ld bytes (",
            size, desc[ndesc-1]->size());
    if (!desc[ndesc-1]->valid())
    {   printf ("error code %02X", !*desc[ndesc-1]);
        delete desc[--ndesc];
    }
    else
        printf ("address %p", desc[ndesc-1]->addr());
    printf (").\n");
}


//--------------------------------------------------------------------------
//
//      Deallocate block.
//
//      Attempt to deallocate an existing block and report the result.
//
void deallocate ()
{
    printf ("Enter block number: ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        continue;
    if (b < 0 || b >= ndesc || desc[b] == 0)
        printf ("No such block!\n");
    else
    {   delete desc[b];
        desc[b] = 0;
        printf ("Block %d deallocated.\n", b+1);
    }
}

//--------------------------------------------------------------------------
//
//      Copy to/from UMB block.
//
//      Prompts for a block number.  An array of random numbers of the
//      specified size is created in conventional memory, copied to the
//      specified block starting at the specified offset, copied back to
//      conventional memory, and finally compared with the original block.
//
void copy ()
{
    unsigned i;
    printf ("Enter block number: ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        { ; }
    if (b < 0 || b >= ndesc || desc[b] == 0)
    {   printf ("No such block!\n");
        return;
    }
    char far* umb = (char far*) desc[b]->addr();
    unsigned s = desc[b]->size();
    if (s != desc[b]->size())
    {   printf ("Block larger than 64K; "
                "only the first 64K-1 bytes will be copied\n");
        s = 0xFFFF;
    }
    char* x = new char [s];
    char* y = new char [s];
    if (x == 0 || y == 0)
    {   printf ("Not enough real memory!\n");
        return;
    }

    printf ("Generating random data... "); fflush (stdout);
    randomize ();
    for (i = 0; i < s; i++)
        x[i] = random (256);
    printf ("done.\n");

    printf ("Copying random data to UMB... "); fflush (stdout);
    for (i = 0; i < s; i++)
        umb[i] = x[i];
    printf ("done.\n");

    printf ("Copying random data back from UMB... "); fflush (stdout);
    for (i = 0; i < s; i++)
        y[i] = umb[i];
    printf ("done.\n");

    for (i = 0; i < s; i++)
    {   if (x[i] != y[i])
        {   printf ("Verification error at offset %u.\n", i);
            break;
        }
    }
    if (i == s)
        printf ("Copy verified successfully.\n");

    delete x;
    delete y;
}
