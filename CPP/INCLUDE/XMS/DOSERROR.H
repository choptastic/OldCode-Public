//--------------------------------------------------------------------------
//
//      DOSERROR.H: header file for DOS critical error/ctrl-break handler.
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
//      2.0     Nov 1993        This file added to provide error handling
//                              facilities
//
//--------------------------------------------------------------------------

#ifndef __DOSERROR_H
#define __DOSERROR_H

#include <stdlib.h>

//--------------------------------------------------------------------------
//
//      Class DOSerror.
//
//      Instances of this class (or derivations thereof) intercept critical
//      errors and control-break interrupts to prevent programs from being
//      unceremoniously terminated.  The default action is to return an
//      automatic FAIL response to critical errors and to ignore control-
//      break events.  Derived classes can overload the member functions
//      "criticalError" and "controlBreak" as desired to provide more
//      application-specific functionality.  Instances may be nested if
//      desired; the most recently-declared instance will intercept all
//      critical errors and control-break events.
//
class DOSerror
{
    typedef void interrupt (*Handler) (...);

  public:
    DOSerror ();                        // install an error handler
    virtual ~DOSerror ();               // uninstall handler

  protected:
    enum    error                       { IGNORE = 0, RETRY = 1, FAIL = 3 };
    virtual error criticalError (int)   { return FAIL; }
    virtual void  controlBreak  ()      { }

  private:
    void*  operator new (size_t)        { return 0; }
                                        // ... to prevent heap allocation
    static void interrupt CtrlBreak     ();
    static void interrupt Critical      (unsigned, unsigned di, unsigned,
                                         unsigned, unsigned,    unsigned,
                                         unsigned, unsigned,    unsigned ax);
    DOSerror* oldInstance;
    Handler   oldCtrlBreak;
    Handler   oldCritical;
};


#include<doserror.cpp>

#endif
