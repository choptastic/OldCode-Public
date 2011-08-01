//--------------------------------------------------------------------------
//
//      HMATEST.CPP: Test program for HMA class.
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
HMA* desc;              // pointer to HMA descriptors


//--------------------------------------------------------------------------
//
//      Function prototypes.
//
char menu ();           // display menu & get user's choice
void allocate ();       // 1. Allocate block
void deallocate ();     // 2. Deallocate block
void copy ();           // 3. Copy block

//--------------------------------------------------------------------------
//
//      Main program.
//
//      A menu of choices is displayed, allowing the user to exercise
//      each of the HMA functions available (except HMA to HMA copying).
//
void main ()
{
    char choice;
    for (;;)
    {
        choice = menu ();
        if (choice == 'X')
            break;

        switch (choice)
        {
            case '1':
                allocate ();
                break;
            case '2':
                deallocate ();
                break;
            case '3':
                copy ();
                break;
        }
    }
    delete desc;
}


//--------------------------------------------------------------------------
//
//      Display menu and get user choice.
//
//      The choice must be a line containing a single character from 1 to 3
//      (or X for exit).
//
char menu ()
{
    printf ("\nChoose desired operation:\n"
            "  1) Allocate block\n"
            "  2) Deallocate block\n"
            "  3) Copy block\n"
            "  X) Exit program\n");
    char buff [80];
    for (;;)
    {
        printf ("Enter your choice: ");
        fgets (buff, 80, stdin);
        if ((buff[0] == 'x' || buff[0] == 'X') && buff[1] == '\n')
            return 'X';
        if (buff[0] < '1' || buff[0] > '3' || buff[1] != '\n')
            printf ("Invalid choice!\a\n");
        else
            break;
    }
    printf ("\n");
    return buff[0];
}

//--------------------------------------------------------------------------
//
//      Allocate block.
//
//      Attempt to allocate a block of a specified size in the HMA and
//      report the result.
//
void allocate ()
{
    printf ("Enter block size: ");
    unsigned size;
    scanf ("%u", &size);
    while (getchar() != '\n')
        continue;
    desc = new HMA (size);
    printf ("Requested %u bytes, granted %u bytes",
            size, desc->size());
    if (!desc->valid())
    {   printf (" (error code %02X)", !*desc);
        delete desc;
    }
    printf (".\n");
}


//--------------------------------------------------------------------------
//
//      Deallocate block.
//
//      Attempt to deallocate an existing block and report the result.
//
void deallocate ()
{
    delete desc;
    desc = 0;
    printf ("HMA deallocated.\n");
}

//--------------------------------------------------------------------------
//
//      Copy to/from HMA block.
//
//      Prompts for a block number.  An array of random numbers of the
//      specified size is created in conventional memory, copied to the
//      specified block starting at the specified offset, copied back to
//      conventional memory, and finally compared with the original block.
//
void copy ()
{
    unsigned i;
    
    // transfer size s, offset offset
    printf ("Enter transfer size: ");
    unsigned s;
    scanf ("%u", &s);
    while (getchar() != '\n')
        { ; }
    printf ("Enter HMA offset:    ");
    unsigned offset;
    scanf ("%u", &offset);
    while (getchar() != '\n')
        { ; }

    char* x = new char [s];
    char* y = new char [s];
    if (x == 0 || y == 0)
    {   printf ("Not enough real memory!\n");
        return;
    }

    printf ("Copying %u bytes to/from HMA offset %u.\n", s, offset);
    printf ("Generating random data... "); fflush (stdout);
    randomize ();
    for (i = 0; i < s; i++)
        x[i] = random (256);
    printf ("done.\n");

    printf ("Copying random data to HMA... "); fflush (stdout);
    printf ("copied %u bytes.\n", HMA::copy (desc->at(offset), x, s));

    printf ("Copying data back from HMA... "); fflush (stdout);
    printf ("copied %u bytes.\n", (s = HMA::copy (y, desc->at(offset), s)));

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
