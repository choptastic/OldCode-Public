//--------------------------------------------------------------------------
//
//      XMSTIME.CPP: timing test for XMS class.
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
#include <dos.h>
#include <limits.h>

//--------------------------------------------------------------------------
//
//      Global data.
//
DOSerror e;             // guard against critical errors and control-breaks
long size;              // XMS transfer size in bytes
const int lapse = 91;   // timer ticks per test (91 ticks = 5 seconds)
volatile long far* timer = (volatile long far*) MK_FP(0x40,0x6C);
                        // pointer to tick counter in BIOS data area

//--------------------------------------------------------------------------
//
//      Display statistics.
//
void stats (long loops)
{
    printf ("%9ld", loops);
    printf ("%12.2f Mb/s\n", (size * loops) / (lapse * 1e6 / 18.2));
}

//--------------------------------------------------------------------------
//
//      Main program.
//
//      This prompts for a block size and a number of iterations, and then
//      copies a block from real memory to XMS, from XMS to XMS, and from
//      XMS back to real memory.  Each test is iterated the requested
//      number of times, and mean timings are displayed for each test.
//
void main ()
{
    for (;;)
    {
        //--- Create XMS blocks of specified size
        printf ("\nXMS timing test: %ld bytes of XMS available\n\n"
                "Enter XMS block size (0 to exit): ", XMS::available());
        if (scanf ("%ld", &size) == 0 || size < 0 || size > UINT_MAX)
        {   while (getchar() != '\n')
                continue;
            printf ("Value between 0 and %u required; try again!\n", UINT_MAX);
            continue;
        }
        if (size == 0)
            break;
        if ((size & 1) == 1)
            printf ("Odd size: rounding down to %ld bytes\n", (size &= ~1));
        XMS a(size), b(size);
        if (!a || !b)
        {   fprintf (stderr, "Not enough XMS (request = %ld bytes)\n", size);
            continue;
        }

        //--- Create conventional array of specified size
        char* c = new char[size];
        if (c == 0)
        {   fprintf (stderr, "Not enough real memory (request = %u bytes)\n",
                     unsigned (size));
            continue;
        }
    
        //--- Display headings
        printf ("Transferring %u bytes; each test takes 5 seconds.\n",
                unsigned(size));
        printf ("\n                Iterations  Transfer rate\n");
    
        long ticks, i;

        //--- Copy real memory to XMS
        printf ("Real -> XMS:  ");
        ticks = *timer + lapse;
        for (i = 0; *timer < ticks; i++)
            XMS::copy (a[0], c, size);
        stats (i);

        //--- Copy XMS to XMS
        printf ("XMS  -> XMS:  ");
        ticks = *timer + lapse;
        for (i = 0; *timer < ticks; i++)
            XMS::copy (b[0], a[0], size);
        stats (i);
    
        //--- Copy XMS to real memory
        printf ("XMS  -> Real: ");
        ticks = *timer + lapse;
        for (i = 0; *timer < ticks; i++)
            XMS::copy (c, b[0], size);
        stats (i);

        //--- Delete real memory block
        delete c;
    }
}
