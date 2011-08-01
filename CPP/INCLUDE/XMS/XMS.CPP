//--------------------------------------------------------------------------
//
//      XMS.CPP: body of XMS interface library.
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
#include <mem.h>
#include <stdlib.h>

//--------------------------------------------------------------------------
//
//      Data structure declarations.
//
struct XMSmove              // descriptor for XMS moves
{
    long count;             // ... number of bytes to move
    int  srchandle;         // ... source handle (0 for real memory)
    long srcoffset;         // ... source offset (or far pointer)
    int  dsthandle;         // ... destination handle (0 for real memory)
    long dstoffset;         // ... destination offset (or far pointer)
};


//--------------------------------------------------------------------------
//
//      Constants.
//
const long K    = 1024;     // size of a kilobyte in bytes
const int  PARA = 16;       // size of a paragraph in bytes


//--------------------------------------------------------------------------
//
//      Globals (statics).
//
static void far (*XMSdriver)() = 0;     // pointer to XMS driver routine
static int      XMSinited      = 0;     // has XMSinit been called already?
static XMSmove  descriptor;             // why use more than one?
static int      A20enabled;             // original A20 state

//--------------------------------------------------------------------------
//
//      XMSinit: initialise XMS system (first time only).
//
//      The first time it is called, this function locates the XMS driver
//      and allocates a handle for a zero-byte block.  It returns TRUE if
//      a handle was successfully allocated.  Subsequent calls return the
//      same value.
//
static XMS::error XMSinit ()
{
    //--- check if this is the first time XMSinit has been called
    if (XMSinited == 0)
    {
        //--- now it isn't!
        XMSinited = 1;

        //--- check if an XMS driver is present (magic spell)
        REGS r;
        r.x.ax = 0x4300;
        int86 (0x2F, &r, &r);
        if (r.h.al != 0x80)
            return XMS::NO_DRIVER;

        //--- get the XMS driver's address (magic spell)
        SREGS s;
        r.x.ax = 0x4310;
        int86x (0x2F, &r, &r, &s);
        XMSdriver = (void far (*)()) MK_FP(s.es,r.x.bx);
    }

    //--- return success indicator
    return (XMSdriver != 0 ? XMS::SUCCESS : XMS::NO_DRIVER);
}


//--------------------------------------------------------------------------
//
//      XMScopy: copy block to/from XMS.
//
//      This function copies data in accordance with the parameters set
//      up in the structure "descriptor".  Overlapping blocks may not be
//      handled correctly (as per XMS specification).  It does nothing if
//      XMS initialisation fails.
//
static XMS::error XMScopy ()
{
    XMS::error result = XMSinit ();
    if (result == XMS::SUCCESS)
    {   _SI = FP_OFF (&descriptor);
        _AH = 0x0B;
        XMSdriver ();
        if (_AX == 0)
            result = XMS::error (_BL);
    }
    return result;
}

//--------------------------------------------------------------------------
//
//      XMS::XMS.
//
//      Constructor for class XMS.  Initialises XMSdriver if necessary,
//      and attempts to allocate a block of the specified number of bytes
//      (which will be rounded up to the nearest K).
//
XMS::XMS (long size)
{
    handle = 0;
    allocation = 0;
    if ((status = XMSinit()) == SUCCESS)
    {   int result = 0;
        int realsize;
        size += K - 1;
        int request = size / K;
        _DX = request;
        _AH = 0x09;
        XMSdriver ();
        result = _AX;
        if (result)
        {   handle = _DX;
            _AH = 0x0E;
            XMSdriver ();
            result = _AX;
            realsize = _DX;
        }
        else
            status = error (_BL);
        if (result)
            allocation = realsize * K;
    }
}


//--------------------------------------------------------------------------
//
//      XMS::~XMS: release the XMS handle (if any).
//
XMS::~XMS ()
{
    if (handle)
    {   _DX = handle;
        _AH = 0x0A;
        XMSdriver ();
    }
}

//--------------------------------------------------------------------------
//
//      XMS::resize.
//
//      Resize existing XMS allocation.
//
XMS::error XMS::resize (long newsize)
{
    error result = (XMSdriver == 0 ? NO_DRIVER : INVALID_OBJECT);
    int size;
    if (handle)
    {   result = SUCCESS;
        newsize += K - 1;
        int request = newsize / K;
        _DX = handle;
        _BX = request;
        _AH = 0x0F;
        XMSdriver ();
        if (_AX != 0)
        {   _DX = handle;
            _AH = 0x0E;
            XMSdriver ();
            size = _DX;
        }
        if (_AX != 0)
            allocation = size * K;
        else
            result = error (_BL);
    }
    return result;
}


//--------------------------------------------------------------------------
//
//      XMS::at.
//
//      Returns a descriptor identifying a particular byte offset in a
//      particular XMS object for use in the "copy" operations below.
//
XMS::XMSptr XMS::at (long offset)
{
    XMSptr p = { handle, offset };
    return p;
}

//--------------------------------------------------------------------------
//
//      XMS::copy.
//
//      Copy from XMS to XMS.
//
XMS::error XMS::copy (const XMS::XMSptr& to,
                      const XMS::XMSptr& from,
                      unsigned len)
{
    if (from.handle == 0 || to.handle == 0)
        return (XMSdriver == 0 ? NO_DRIVER : INVALID_OBJECT);
    descriptor.count     = len;
    descriptor.srchandle = from.handle;
    descriptor.srcoffset = from.offset;
    descriptor.dsthandle = to.handle;
    descriptor.dstoffset = to.offset;
    return XMScopy ();
}


//--------------------------------------------------------------------------
//
//      XMS::copy.
//
//      Copy from XMS to conventional memory.
//
XMS::error XMS::copy (void far* to,
                      const XMS::XMSptr& from,
                      unsigned len)
{
    if (from.handle == 0)
        return (XMSdriver == 0 ? NO_DRIVER : INVALID_OBJECT);
    descriptor.count     = len;
    descriptor.srchandle = from.handle;
    descriptor.srcoffset = from.offset;
    descriptor.dsthandle = 0;
    descriptor.dstoffset = long (to);
    return XMScopy ();
}


//--------------------------------------------------------------------------
//
//      XMS::copy.
//
//      Copy from conventional memory to XMS.
//
XMS::error XMS::copy (const XMS::XMSptr& to,
                      void far* from,
                      unsigned len)
{
    if (to.handle == 0)
        return (XMSdriver == 0 ? NO_DRIVER : INVALID_OBJECT);
    descriptor.count     = len;
    descriptor.srchandle = 0;
    descriptor.srcoffset = long (from);
    descriptor.dsthandle = to.handle;
    descriptor.dstoffset = to.offset;
    return XMScopy ();
}

//--------------------------------------------------------------------------
//
//      XMS::available.
//
//      Returns the total size of available XMS.
//
long XMS::available ()
{
    if (XMSinit () == SUCCESS)
    {   _AH = 0x08;
        XMSdriver ();
        return _DX * K;
    }
    else
        return 0;
}


//--------------------------------------------------------------------------
//
//      XMS::largest.
//
//      Returns the size of the largest unallocated XMS block available.
//
long XMS::largest ()
{
    if (XMSinit () == SUCCESS)
    {   _AH = 0x08;
        XMSdriver ();
        return _AX * K;
    }
    else
        return 0;
}

//--------------------------------------------------------------------------
//
//      UMB::UMB.
//
//      Attempt to construct a UMB block of the specified size.
//
UMB::UMB (long size)
{
    address = 0;
    allocation = 0;
    if (size > (64 * K - 1) * PARA)
        status = XMS::BLOCK_TOO_BIG;
    else if ((status = XMSinit()) == XMS::SUCCESS)
    {   size += PARA - 1;
        _DX = unsigned (size/PARA);
        _AH = 0x10;
        XMSdriver ();
        if (_AX != 0)
        {   int bx = _BX;
            address = MK_FP (bx,0);
            allocation = unsigned (_DX);
        }
        else
            status = XMS::error (_BL);
    }
    allocation *= PARA;
}


//--------------------------------------------------------------------------
//
//      UMB::~UMB.
//
//      Destroy UMB block if it has been created successfully.
//
UMB::~UMB ()
{
    if (address != 0)
    {   _DX = FP_SEG (address);
        _AH = 0x11;
        XMSdriver ();
    }
}


//--------------------------------------------------------------------------
//
//      UMB::largest.
//
//      Return size of largest available UMB block.
//
long UMB::largest ()
{
    long size = 0;
    if (XMSinit () == XMS::SUCCESS)
    {   _AH = 0x10;
        _DX = 0xFFFF;
        XMSdriver ();
        size = unsigned (_DX);
    }
    return size * PARA;
}

//--------------------------------------------------------------------------
//
//      HMA::HMA.
//
//      Attempt to allocate HMA for a block of the specified size.
//
HMA::HMA (unsigned size)
{
    allocation = 0;
    if (size > (64 * K) - PARA)
        status = XMS::BLOCK_TOO_BIG;
    else if ((status = XMSinit()) == XMS::SUCCESS)
    {   _DX = size;
        _AH = 0x01;
        XMSdriver ();
        if (_AX != 0)
        {   allocation = size;
            _AH = 0x07;
            XMSdriver ();
            A20enabled = _AX;
            if (!A20enabled)
            {   _AH = 0x03;
                XMSdriver ();
                if (_AX != 0)
                    return;
            }
        }
        status = XMS::error (_BL);
    }
}


//--------------------------------------------------------------------------
//
//      HMA::~HMA.
//
//      Release HMA if it has been allocated successfully.
//
HMA::~HMA ()
{
    if (status == XMS::SUCCESS)
    {   _AH = 0x02;
        XMSdriver ();
        if (!A20enabled)
        {   _AH = 0x04;
            XMSdriver ();
            A20enabled = !_AX;
        }
    }
}


//--------------------------------------------------------------------------
//
//      HMA::at.
//
HMA::HMAptr HMA::at (unsigned offset)
{
    HMAptr h = { this, offset };
    return h;
}

//--------------------------------------------------------------------------
//
//      HMA::copy.
//
//      Copy a block from one offset in the HMA to another.  The two
//      blocks should not overlap.
//
unsigned HMA::copy (const HMAptr& to, const HMAptr& from, unsigned len)
{
    if (!to.hma->valid() || !from.hma->valid())
        return 0;
    if (len > to.hma->size() - to.offset)
        len = to.hma->size() - to.offset;
    if (len > from.hma->size() - from.offset)
        len = from.hma->size() - from.offset;
    _fmemcpy (MK_FP (0xFFFF, 0x0010 + to.offset),
              MK_FP (0xFFFF, 0x0010 + from.offset),
              len);
    return len;
}


//--------------------------------------------------------------------------
//
//      HMA::copy.
//
//      Copy a block from the HMA to conventional memory.
//
unsigned HMA::copy (void far* to, const HMAptr& from, unsigned len)
{
    if (!from.hma->valid())
        return 0;
    if (len > from.hma->size() - from.offset)
        len = from.hma->size() - from.offset;
    _fmemcpy (to, MK_FP (0xFFFF, 0x0010 + from.offset), len);
    return len;
}


//--------------------------------------------------------------------------
//
//      HMA::copy.
//
//      Copy a block from conventional memory to the HMA.
//
unsigned HMA::copy (const HMAptr& to, void far* from, unsigned len)
{
    if (!to.hma->valid())
        return 0;
    if (len > to.hma->size() - to.offset)
        len = to.hma->size() - to.offset;
    _fmemcpy (MK_FP (0xFFFF, 0x0010 + to.offset), from, len);
    return len;
}
