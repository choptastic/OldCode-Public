//--------------------------------------------------------------------------
//
//      XMSTEST.CPP: Test program for XMS class.
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
XMS* desc [100];        // array of pointers to XMS descriptors
int ndesc = 0;          // number of descriptors


//--------------------------------------------------------------------------
//
//      Function prototypes.
//
char menu ();           // display menu & get user's choice
void XMSstats ();       // 1. XMS statistics
void blocksizes ();     // 2. List block sizes
void allocate ();       // 3. Allocate block
void deallocate ();     // 4. Deallocate block
void copy ();           // 5. Copy block
void resize ();         // 6. Resize block

//--------------------------------------------------------------------------
//
//      Main program.
//
//      A menu of choices is displayed, allowing the user to exercise
//      each of the XMS functions available (with the exception of
//      XMS-to-XMS copying).
//
void main ()
{
    XMSstats();

    char choice;
    for (;;)
    {
        choice = menu ();
        if (choice == 'X')
            break;

        switch (choice)
        {
            case '1':
                XMSstats ();
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
            case '6':
                resize ();
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
//      The choice must be a line containing a single character from 1 to 6
//      (or X for exit).
//
char menu ()
{
    printf ("\nChoose desired operation:\n"
            "  1) XMS statistics\n"
            "  2) List block sizes\n"
            "  3) Allocate block\n"
            "  4) Deallocate block\n"
            "  5) Copy block\n"
            "  6) Resize block\n"
            "  X) Exit program\n");
    char buff [80];
    for (;;)
    {
        printf ("Enter your choice: ");
        fgets (buff, 80, stdin);
        if ((buff[0] == 'x' || buff[0] == 'X') && buff[1] == '\n')
            return 'X';
        if (buff[0] < '1' || buff[0] > '6' || buff[1] != '\n')
            printf ("Invalid choice!\a\n");
        else
            break;
    }
    printf ("\n");
    return buff[0];
}


//--------------------------------------------------------------------------
//
//      Display XMS statistics.
//
void XMSstats ()
{
    printf ("XMS available: %ld bytes\nLargest block: %ld bytes\n",
            XMS::available(), XMS::largest());
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
    desc [ndesc++] = new XMS (size);
    printf ("Block %d: ", ndesc);
    printf ("requested %ld bytes, granted %ld bytes.\n",
            size, desc[ndesc-1]->size());
    if (!desc[ndesc-1]->valid())
        delete desc[--ndesc];
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
//      Copy to/from XMS.
//
//      Prompts for a block number and a transfer size.  An array of random
//      numbers of the specified size is created in conventional memory,
//      copied to the specified block starting at the specified offset,
//      copied back to conventional memory, and finally compared with the
//      original block.
//
void copy ()
{
    printf ("Enter block number:  ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        continue;
    if (b < 0 || b >= ndesc || desc[b] == 0)
    {   printf ("No such block!\n");
        return;
    }

    printf ("Enter transfer size: ");
    unsigned s;
    scanf ("%u", &s);
    while (getchar() != '\n')
        continue;
    char* x = new char [s];
    char* y = new char [s];
    if (x == 0 || y == 0)
    {   printf ("Not enough real memory!\n");
        return;
    }

    printf ("Enter block offset:  ");
    long p;
    scanf ("%ld", &p);
    while (getchar() != '\n')
        continue;
    printf ("Copying %u bytes to/from XMS block %d, offset %ld.\n", s, b, p);
    printf ("Generating random data... "); fflush (stdout);
    randomize ();
    for (unsigned i = 0; i < s; i++)
        x[i] = random (256);
    printf ("done.\n");

    XMS::error r = XMS::copy (desc[b]->at(p), x, s);
    printf ("Random data copied to XMS, result code %02X\n", int(r));
    if (r == XMS::SUCCESS)
    {   r = XMS::copy (y, desc[b]->at(p), s);
        printf ("Data copied back from XMS, result code %02X\n", int(r));
        if (r == XMS::SUCCESS)
        {   for (i = 0; i < s; i++)
            {   if (x[i] != y[i])
                {   printf ("Verification error at offset %u.\n", i);
                    break;
                }
            }
            if (i == s)
                printf ("Copy verified successfully.\n");
        }
    }
    delete x;
    delete y;
}

//--------------------------------------------------------------------------
//
//      Resize an existing block.
//
//      Attempt to resize an existing XMS allocation and report the result.
//
void resize ()
{
    printf ("Enter block number: ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        continue;
    if (b < 0 || b >= ndesc || desc[b] == 0)
    {   printf ("No such block!\n");
        return;
    }

    printf ("Current size:   %ld\nEnter new size: ", desc[b]->size());
    long size;
    scanf ("%ld", &size);
    while (getchar() != '\n')
        continue;
    XMS::error r = desc[b]->resize (size);
    if (r == XMS::SUCCESS)
        printf ("Requested %ld, granted %ld.\n", size, desc[b]->size());
    else
        printf ("Resize failed: error code = %02X\n", int(r));
}
