//--------------------------------------------------------------------------
//
//      XARRTEST.CPP: test program for XMS array class.
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

#include <stdio.h>
#include <dos.h>
#include "doserror.h"
#include "xmsarray.h"
#include "xms.h"


//--------------------------------------------------------------------------
//
//      Global data.
//
DOSerror e;                     // prevent critical errors and control-breaks
XMSarray<char>* arrs [100];     // array of pointers to XMS arrays
int narrs = 0;                  // number of arrays


//--------------------------------------------------------------------------
//
//      Function prototypes.
//
char menu ();                   // display menu & get user's choice
void XMSstats ();               // 1. XMS statistics
void arraysizes ();             // 2. Array sizes
void allocate ();               // 3. Allocate array
void deallocate ();             // 4. Deallocate array
void copy ();                   // 5. Copy array

//--------------------------------------------------------------------------
//
//      Main program.
//
//      A menu of choices is displayed, allowing the user to exercise
//      each of the XMS array functions available.
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
                arraysizes ();
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
    for (int i = 0; i < narrs; i++)
        delete arrs[i];
}

//--------------------------------------------------------------------------
//
//      Display menu and get user choice.
//
//      The choice must be a line containing a single character from 1 to 5
//      (or X for exit).
//
char menu ()
{
    printf ("\nChoose desired operation:\n"
            "  1) XMS statistics\n"
            "  2) Array sizes\n"
            "  3) Allocate array\n"
            "  4) Deallocate array\n"
            "  5) Copy array\n"
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
//      Display XMS statistics.
//
void XMSstats ()
{
    printf ("XMS available: %ld bytes\nLargest block: %ld bytes\n",
            XMS::available(), XMS::largest());
}


//--------------------------------------------------------------------------
//
//      Display array sizes.
//
void arraysizes ()
{
    int flag = 0;
    for (int i = 0; i < narrs; i++)
    {   if (arrs[i] != 0)
        {   printf ("Array %d: size = %ld\n", i+1, arrs[i]->size());
            flag = 1;
        }
    }
    if (flag == 0)
        printf ("No arrays allocated!\n");
}

//--------------------------------------------------------------------------
//
//      Allocate array.
//
//      Attempt to allocate a new array of a specified size and report the
//      result.
//
void allocate ()
{
    printf ("Enter array size: ");
    long size;
    scanf ("%ld", &size);
    while (getchar() != '\n')
        continue;
    arrs [narrs++] = new XMSarray<char> (size);
    printf ("Array %d: ", narrs);
    printf ("requested %ld items, granted %ld items.\n",
            size, arrs[narrs-1]->size());
    if (!arrs[narrs-1]->valid())
        delete arrs[--narrs];
}


//--------------------------------------------------------------------------
//
//      Deallocate array.
//
//      Attempt to deallocate an existing array and report the result.
//
void deallocate ()
{
    printf ("Enter array number: ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        continue;
    if (b < 0 || b >= narrs || arrs[b] == 0)
        printf ("No such array!\n");
    else
    {   delete arrs[b];
        arrs[b] = 0;
        printf ("Array %d deallocated.\n", b+1);
    }
}

//--------------------------------------------------------------------------
//
//      Copy to/from XMS.
//
//      Prompts for an array number.  An array of random numbers is created
//      in conventional memory, copied to the specified XMS array, copied
//      back to conventional memory, and finally compared with the original
//      array.
//
void copy ()
{
    printf ("Enter array number: ");
    int b;
    scanf ("%d", &b); b--;
    while (getchar() != '\n')
        continue;
    if (b < 0 || b >= narrs || arrs[b] == 0)
    {   printf ("No such array!\n");
        return;
    }

    const chunksize = 16384;
    int size = (arrs[b]->size() > chunksize ? chunksize : arrs[b]->size());
    int chunks = arrs[b]->size() / chunksize + 1;
    char* x = new char [size];
    char* y = new char [size];
    if (x == 0 || y == 0)
    {   printf ("Not enough real memory!\n");
        return;
    }

    randomize ();
    printf ("Copying will be done in %d chunks of %d bytes each...\n",
            chunks, size);
    int fail;
    for (long i = 0; i < chunks; i++)
    {   int j;
        fail = 0;
        printf ("Chunk %ld: ", i + 1);
        for (j = 0; j < size && i * size + j < arrs[b]->size(); j++)
            x[j] = random (255);
        printf ("writing... ");
        for (j = 0; j < size && i * size + j < arrs[b]->size(); j++)
            arrs[b]->at(i * size + j) = x[j];
        printf ("reading... ");
        for (j = 0; j < size && i * size + j < arrs[b]->size(); j++)
            y[j] = arrs[b]->at(i * size + j);
        printf ("verifying... ");
        for (j = 0; j < size && i * size + j < arrs[b]->size(); j++)
            if (x[j] != y[j])
            {   printf ("error at offset %ld.\n", i * size + j);
                fail = 1;
                break;
            }
        if (!fail)
            printf ("OK.\n");
    }
    if (!fail)
        printf ("Copy test successful.\n");
    delete x;
    delete y;
}
