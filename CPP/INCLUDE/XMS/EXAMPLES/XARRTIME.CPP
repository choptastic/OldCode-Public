//--------------------------------------------------------------------------
//
//      XARRTIME.CPP: timing test for XMS array class.
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
//      1.0     Jun 1993        Initial coding
//      2.0     Nov 1993        Renamed from XMSBENCH to XARRTIME and
//                              generally reorganised
//                              
//--------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "xmsarray.h"
#include "xms.h"

//--------------------------------------------------------------------------
//
//      Global data.
//
const int lapse = 91;   // timer ticks per test (91 ticks = 5 seconds)
volatile long far* timer = (volatile long far*) MK_FP(0x40,0x6C);
                        // pointer to BIOS timer count


//--------------------------------------------------------------------------
//
//      Display statistics.
//
void stats (int size, long loops)
{
    printf ("%9ld", loops);
    printf ("%12.2f Mb/s\n", (size * loops) / (lapse * 1e6 / 18.2));
}

//--------------------------------------------------------------------------
//
//      Test function.
//
//      This performs a timing test for an XMS array of a specified
//      type with a specified number of elements and cache size for
//      a specified number of iterations.
//
template<class T> void test (T* value, long elems, unsigned buff)
{
    long ticks;

    //--- allocate the array and report status
    printf ("\nAllocation of %ld items of %u bytes each ...",
            elems, sizeof(T)); fflush (stdout);
    XMSarray<T> a(elems, buff);
    printf ("\b\b\b%s\n%ld bytes of XMS free",
            (a.valid() ? "succeeded" : "failed"),
            XMS::available());
    if (!a)
    {   printf (".\n");
        return;
    }
    printf (", buffer size = %u bytes.\nEach test takes 5 seconds.\n\n", buff);

    //--- display headings
    printf ("             Items copied   Transfer rate\n");
    long i;

    //--- write test: a[i] = value
    printf ("Writing:     "); fflush (stdout);
    ticks = *timer + lapse;
    for (i = 0; *timer < ticks; i++)
        a[i%elems] = *value;
    stats (sizeof(T), i);

    //--- read test: a[i] = value
    printf ("Reading:     "); fflush (stdout);
    ticks = *timer + lapse;
    for (i = 0; *timer < ticks; i++)
        *value = a[i%elems];
    stats (sizeof(T), i);

    //--- copy test 1: a[0] = a[0]
    //    (Item copied from cache; gives raw cache speed)
    printf ("Copying (1): "); fflush (stdout);
    ticks = *timer + lapse;
    for (i = 0; *timer < ticks; i++)
        a[0] = a[0];
    stats (sizeof(T), i);

    //--- copy test 2: a[0] = a[elems-1]
    //    (Cache cruncher: items never cached, gives raw XMS speed)
    printf ("Copying (2): "); fflush (stdout);
    ticks = *timer + lapse;
    for (i = 0; *timer < ticks; i++)
        a[0] = a[elems - 1];
    stats (sizeof(T), i);
}

//--------------------------------------------------------------------------
//
//      Type definitions for array element types.
//
struct T1 { char x[10]; }    t1;
struct T2 { char x[100]; }   t2;
struct T3 { char x[1000]; }  t3;
struct T4 { char x[10000]; } t4;


//--------------------------------------------------------------------------
//
//      Main program.
//
void main ()
{
    printf ("XMS array timing test: %ld bytes of XMS free initially\n",
            XMS::available());
    for (;;)
    {   printf ("\nChoose size of array items:\n"
                "  1) 10 bytes\n"
                "  2) 100 bytes\n"
                "  3) 1000 bytes\n"
                "  4) 10000 bytes\n"
                "  X) Exit program\n");
        char buff [80];
        for (;;)
        {
            printf ("Enter your choice: ");
            fgets (buff, 80, stdin);
            if ((buff[0] == 'x' || buff[0] == 'X') && buff[1] == '\n')
                exit (0);
            if (buff[0] < '1' || buff[0] > '5' || buff[1] != '\n')
                printf ("Invalid choice!\a\n");
            else
                break;
        }

        printf ("Enter number of array elements: ");
        long e;
        scanf ("%ld", &e);
        while (getchar() != '\n')
            continue;
        printf ("Enter size of internal buffer:  ");
        unsigned b;
        scanf ("%u", &b);
        while (getchar() != '\n')
            continue;

        switch (buff[0])
        {
          case '1':
            test (&t1, e, b);
            break;
          case '2':
            test (&t2, e, b);
            break;
          case '3':
            test (&t3, e, b);
            break;
          case '4':
            test (&t4, e, b);
            break;
        }
    }
}
