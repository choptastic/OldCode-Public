//--------------------------------------------------------------------------
//
//      XMSARRAY.H: header file for XMSarray class library.
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
//      NOTE: compilation problems due to template implementation bugs
//            have been reported for Borland C++ 3.0; these problems may
//            also arise with other compiler versions.
//      Revision history:
//      1.0     Jun 1993        Initial coding
//      1.01    Sep 1993        Filenames changed from XMS.* to XMSARRAY.*
//                              Documentation updated & clarified
//      2.0     Nov 1993        Member function "at" added
//                              Some minor tidying up done
//                              
//--------------------------------------------------------------------------

#ifndef __XMSARRAY_H
#define __XMSARRAY_H

//--------------------------------------------------------------------------
//
//      Class XMSarrayBase: base class for XMS array classes.
//
//      This class encapsulates the XMS interface required by XMSarray
//      and XMSitem, and is not intended for direct use.
//
class XMSarrayBase
{
    friend class XMSmanager;

  public:
    int  valid     ()                   { return state; }
    int  operator! ()                   { return !state; }

  protected:
    XMSarrayBase   (const XMSarrayBase& array);
                                        // constructor used by XMSItem
    XMSarrayBase   (long items, unsigned size, unsigned cachesize);
                                        // constructor used by XMSarray
    void free ();                       // free an XMS array
    int  mask (int n);                  // mask out offset field of address

    void* get (long base, int offset);  // get an XMS value for reading
    void* put (long base, int offset);  // get an XMS value for writing

  private:
    struct XMSbuffer* buffer;
    int               state;
};

//--------------------------------------------------------------------------
//
//      Class XMSarray: XMS array class.
//
//      The constructor parameters specify the number of array elements
//      required and (optionally) the size of the internal cache in bytes
//      to be used for buffering accesses to small items.  The cache size
//      will be rounded up to a power of 2 times the item size.  The only
//      things you can do with an XMSarray are:
//          * Subscript it (e.g. x[i] or x.at(i))
//          * Check if it has been allocated successfully
//            (e.g. x.valid() or !x)
//
//      The template parameter T must be a type capable of being assigned
//      to which does not have a constructor or a destructor.
//
template<class T> class XMSarray : public XMSarrayBase
{
  public:
    XMSarray   (long size, unsigned cachesize = 2048)
                    : XMSarrayBase (size, sizeof(T), cachesize)
                    { items = size < 0 ? 1 : size + 1; }
    ~XMSarray  ()                         { free (); }
    long       size ()                    { return items - 1; }
    XMSItem<T> at         (long index);   // subscript operator
    XMSItem<T> operator[] (long index)    { return at (index); }

  private:
    long items;
};


//--------------------------------------------------------------------------
//
//      Class XMSItem: XMS data item class.
//
//      This is a helper class which represents a single element of an
//      XMSarray.  Users cannot create objects of this type directly;
//      XMSItems are only created as a result of subscripting an XMSarray.
//      You can perform the following operations on an XMSItem:
//          * Assign a new value to it (e.g. x[i] = y)
//          * Get its value (e.g. y = x[i])
//
template<class T> class XMSItem : public XMSarrayBase
{
    friend class XMSarray<T>;

  public:
    XMSItem& operator= (XMSItem& value);  // copy one array element to another
    XMSItem& operator= (const T& value);  // assign new value to array element
    operator T         ();                // get value of array element

  private:
    XMSItem  (long i, XMSarray<T>& b);
    long     base;
    int      offset;
};

//--------------------------------------------------------------------------
//
//      Template functions.
//
template<class T>
inline XMSItem<T> XMSarray<T>::at (long index)
{
    long i = (index >= 0 && index < items) ? index : items;
    return XMSItem<T> (i, *this);
}


template<class T>
inline XMSItem<T>::XMSItem (long i, XMSarray<T>& b)
    : XMSarrayBase (b)
{
    offset = mask(i) * sizeof(T);
    base   = i * sizeof(T) - offset;
}


template<class T>
inline XMSItem<T>& XMSItem<T>::operator= (XMSItem<T>& value)
{
    if (valid())
    {   T temp = *(T*) value.get(value.base,value.offset);
        T* ptr = (T*) put(base,offset);
        if (ptr != 0)
            *ptr = temp;
    }
    return *this;
}


template<class T>
inline XMSItem<T>& XMSItem<T>::operator= (const T& value)
{
    if (valid())
        *(T*) put(base,offset) = value;
    return *this;
}


template<class T>
inline XMSItem<T>::operator T ()
{
    return *(T*) get(base,offset);      // this is for DOS -- dereferencing
}                                       // (void*)0 is okay, gives garbage
                                        // (I'd prefer exceptions...)

#include<xmsarray.cpp>
#endif
