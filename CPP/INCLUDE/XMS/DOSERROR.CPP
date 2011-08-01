//--------------------------------------------------------------------------
//
//      DOSERROR.CPP: body of DOS critical error/control-break handler.
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


#include <dos.h>

//--------------------------------------------------------------------------
//
//      Type declarations and static data.
//
typedef void interrupt (*Handler) (...);    // interrupt handler type

static DOSerror* instance = 0;              // current DOSerror instance


//--------------------------------------------------------------------------
//
//      Control-break interrupt handler.
//
//      This calls the current instance's "controlBreak" member function.
//
void interrupt DOSerror::CtrlBreak ()
{
    instance->controlBreak ();
}


//--------------------------------------------------------------------------
//
//      Critical error interrupt handler.
//
//      This calls the current instance's "criticalError" member function.
//      It also checks the return value to prevent ABORT being selected;
//      anything other than IGNORE or RETRY will be interpreted as FAIL.
//
void interrupt DOSerror::Critical (unsigned, unsigned di, unsigned,
                                   unsigned, unsigned,    unsigned,
                                   unsigned, unsigned,    unsigned ax)
{
    ax = instance->criticalError (di & 0x00FF);
    if (ax != IGNORE && ax != RETRY)
        ax = FAIL;
}

//--------------------------------------------------------------------------
//
//      DOSerror constructor.
//
//      This checks if there is an existing instance of a class derived
//      from DOSerror; if not, the existing interrupt vectors are replaced.
//      
DOSerror::DOSerror ()
{
    oldInstance = instance;
    instance = this;
    oldCtrlBreak = getvect (0x23);
    oldCritical = getvect (0x24);
    setvect (0x23, Handler (CtrlBreak));
    setvect (0x24, Handler (Critical));
}


//--------------------------------------------------------------------------
//
//      DOSerror destructor.
//
//      This checks if there is an existing instance of a class derived
//      from DOSerror; if so, the original interrupt vectors are restored.
//      The global "counter" is used to guard against nested instance
//      scopes.
//
DOSerror::~DOSerror ()
{
    setvect (0x23, oldCtrlBreak);
    setvect (0x24, oldCritical);
    instance = oldInstance;
}
