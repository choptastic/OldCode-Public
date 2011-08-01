#---------------------------------------------------------------------------
#
#       MAKEFILE.MAK: makefile for XMS class libraries.
#       Copyright (c) J.English 1993.
#       Author's address: je@unix.brighton.ac.uk
#
#       Permission is granted to use copy and distribute the
#       information contained in this file provided that this
#       copyright notice is retained intact and that any software
#       or other document incorporating this file or parts thereof
#       makes the source code for the library of which this file
#       is a part freely available.
#
#---------------------------------------------------------------------------

.AUTODEPEND
.SILENT

#----- Symbol definitions -----

DIR   = d:\borlandc                 # Borland C++ directory -- change to suit
MODEL = l                           # Memory model (s, m, l, c, h or t)
CC    = bcc -m$(MODEL) -I$(INC)\include -L$(LIB)\lib

#----- Default compilation rule -----

.cpp.obj:
    $(CC) -c $.

#----- Compilation rules -----

all: xmstest.exe xmstime.exe umbtest.exe hmatest.exe xarrtest.exe xarrtime.exe

xmstest.exe:    xmstest.obj xms.obj doserror.obj
    $(CC) xmstest.obj xms.obj doserror.obj

xmstime.exe:    xmstime.obj xms.obj doserror.obj
    $(CC) xmstime.obj xms.obj doserror.obj

umbtest.exe:    umbtest.obj xms.obj doserror.obj
    $(CC) umbtest.obj xms.obj doserror.obj

hmatest.exe:    hmatest.obj xms.obj doserror.obj
    $(CC) hmatest.obj xms.obj doserror.obj

xarrtest.exe:   xarrtest.obj xmsarray.obj xms.obj doserror.obj
    $(CC) xarrtest.obj xmsarray.obj xms.obj doserror.obj

xarrtime.exe:   xarrtime.obj xmsarray.obj xms.obj doserror.obj
    $(CC) xarrtime.obj xmsarray.obj xms.obj doserror.obj

xms.obj:        xms.cpp
doserror.obj:   doserror.cpp
xmstest.obj:    xmstest.cpp
umbtest.obj:    umbtest.cpp
hmatest.obj:    hmatest.cpp
xmstime.obj:    xmstime.cpp
xarrtest.obj:   xarrtest.cpp
xarrtime.obj:   xarrtime.cpp

#----- Other targets -----

clean:                              # clean up directory
    del *.obj

print:                              # print sources
    print *.doc *.mak *.h *.cpp
