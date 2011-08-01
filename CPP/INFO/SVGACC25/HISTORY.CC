REVISION HISTORY FOR SVGACC.LIB - HI-RES, 256-COLOR GRAPHICS LIB FOR
MICROSOFT COMPATIBLE C/C++ COMPILERS (MS, BORLAND, SYMANTEC).

SVGACC20.ZIP was the inital release of the C version of our graphics library.
However, we have had several releases of the MS QuickBASIC version.  Below
is the history for the QuickBASIC versions:

-----------------------------------------------------------------------------
-1.0 Initial release - June, 1993.  SVGAQB10.ZIP                            -
-                                                                           -
-1.1 Release - August, 1993.  SVGAQB11.ZIP                                  -
-    Bugs Fixed: GIFGETINFO - not closing successful files                  -
-                DRWLINE - not always drawing endpoints                     -
-                DRWBOX - drawing incorrectly when X2<X1 and/or Y2<Y1       -
-    Improved:   FILLAREA - speed increase of about 150%                    -
-                F ILLCOLOR - speed increase of about 65%                    -
-                Increased library's granularity                            -
-    Additions:  BYTECOPY, PALCOPY, GETMAXX, GETMAXY, GETARCCOS, GETARCSIN, -
-                    GETARCTAN, GETCOS, GETSIN, GETTAN                      -
-                                                                           -
-1.2 Release - August, 1993.  SVGAQB12.ZIP                                  -
-    Bugs Fixed: FILLAREA - not always making it to the far left            -
-                FILLCOLOR - not always making it to the far left           -
-                                                                           -
-1.2a Release - September, 1993. SVGAQB12a (registered version only)        -
-    Bugs Fixed: SPRITEPUT - had problems if spriteXloc = MAXX              -
-                SPRITEGAP - had problems if spriteXloc = MAXX              -
-                                                                           -
-2.0 Release - March, 1994. SVGAQB20.ZIP                                    -
-    Additions:  BLKRESIZE, BLKROTATE, BLKROTATESIZE, DRWFILBOX,            -
-                    DRWFILCIRCLE, DRWFILELLISPE, FILLSCREEN, FILLPAGE,     -
-                    GIFMAKE, PAGEDISPLAY, PAGEACTIVE, RES640L, SPRITEGET,  -
-                    SPRITECOLLDETECT, WHICHXMS, XMSALLOCATE, XMSFREE,      -
-                    XMSGET, XMSPUT, XMSCOPY, XMSERROR                      -
-                                                                           -
-----------------------------------------------------------------------------

2.0 Initial release - March, 1994. SVGACC20.ZIP

2.0a Release - March, 1994. SVGACC20a (registered version only)
     Bugs Fixed:  res640l,res640,res800,res1024 - Some VESA BIOSs were not
                     preserving the processor SI & DI registers after a 
                     video mode change.

2.0b Release - April, 1994. SVGACC20b (registered version only)
     Bugs Fixed:  drwfillcircle - not clipping properly
                  drwfillellipse - not clipping properly
     Improved:    drwbox - speed increase of about 102%
                  drwcircle - speed increase of about 33%
                  drwellipse - speed increase of about 44%
                  drwline - speed increase of about 42%
                  drwfillbox - speed increase of about 317%
                  drwfillcircle - speed increase of about 248%
                  drwfillellipse - speed increase of about 190%

2.1 Release - May, 1994. SVGACC21.ZIP
     Bugs Fixed:  setcard - setup needed for pagedisplay was not completed.
     Improved:    drwbox - speed increase of about 8%
                  drwline - speed increase of about 42%
                  drwfillbox - speed increase of about 97%
                  drwfillcircle - speed increase of about 88%
                  drwfillellipse - speed increase of about 80%
                  fillview - speed increase of about 62%
     Additions:   res1280, fillconvexpoly

2.1a Release - August, 1994.  SVGACC21a (registered version only)
     Bugs Fixed:  drwfillcircle,drwfillellipse - When using the 'XOR' mode,
                     some lines were drawn twice resulting in a 'sun set'
                     effect.
                  drwline - using the 'AND' mode on a horizontal line 
                     resulted in the first few pixels (left most) actually
                     being drawn in the 'SET' mode; this bug also affected 
                     the following functions (only when using the 'AND' 
                     mode): drwfillbox, drwfillcircle, drwfillellipse, 
                     fillconvexpoly, fillview.
                  Registered disks did not include the 'EDTMOUSE.TXT' and
                     'EDTFONT.TXT' as stated in the file 'PACKING.LST'. 
                     These files were however included in the main 
                     documentation files.
     Improved:    drwfillcircle - speed increase of about 16%
                  drwfillellipse - speed increase of about 30%
                    
2.1b Release - September, 1994.  SVGACC21b (registered version only)
     Bugs Fixed:  Some newer VESA cards with dual 'window' support were not 
                     bank switching properly.

2.1c Release - November, 1994.  SVGACC21c (registered version only)
     Bugs Fixed:  Mouse routines rewritten to support ALL mice. 

2.2  Release - January, 1995.  SVGACC22 (registered version only)
     Bugs Fixed:  fillarea - not always making it to left edge when left edge
                     was the viewport and not the border color.
                  fillcolor - not always making it to left edge when left 
                     edge was the viewport and not the border color.
                  gifmake - under certain circumstances would produce a 
                     corrupt GIF file.
     Improved:    Increased library's granularity
                  blkget - speed increase of about 33%
                  scrolldn - speed increase of about 39%
                  scrolllt - speed increase of about 25%
                  scrollrt - speed increase of about 72%
                  scrollup - speed increase of about 26%
                  spritegap - speed increase of about 29%
                  spriteget - speed increase of about 20%
                  fillconvexpoly - speed increase of about 5%
     Additions:   drwcirarc, drwellarc, drwcubicbezier, fillpoly, xmsblkget, 
                     xmsblkput, xmsscreenput, xmsscreenput

2.3  Release - January, 1995.  SVGACC23.ZIP
     Removed:     gifgetinfo, gifmake,gifput - Unisys, owner of patent on 
                     LZW compression, now requires paying royalties for use 
                     of technology.  LZW compression is used in the GIF 
                     specification.
     Additions:   pcxgetinfo, pcxmake,pcxput

2.3a Release - February, 1995.  SVGACC23 (registered version only)
     Bugs Fixed:  pcxmake - minor errors in header file

2.3b Release - February, 1995.  SVGACC23 (registered version only)
     Bugs Fixed:  pcxput - not correctly displaying PCX file whose width
                     is an odd number

2.3c Release - March, 1995.  SVGACC23 (registered version only)
     Bugs Fixed: blkput - using the 'AND' mode resulted in most pixels 
                     being drawn in the 'XOR' mode; this bug also affected 
                     the following functions (only when using the 'AND' 
                     mode): drwstring, drwstringdn, drwstringlt, 
                     drwstringrt, pcxput

2.3d Release - April, 1995.  SVGACC23 (not offically released)
     Bugs Fixed: d3project - not catching over/underflow properly

2.3e Release - April, 1995.  SVGACC23 (registered version only)
     Improved:   whichxms - changed internal structure 

2.4  Release - January, 1996.  SVGACC24.ZIP
     Changed:    The order form (file name "ORDER.FRM") was simplified.
     Additions:  A new credit card order form (file name "CHARGEIT.FRM")
 
2.4a Release - March, 1996. SVGACC24 (shareware & registered patch available)
     Bugs Fixed:   res640l, res640, res800, res1024, res1280 - fixed a bug with 
                      some VESA cards that use non-standard "bytes-per-scanline"
                      values.
                   scrollup, scrolldn, scrolllt, scrollrt - not correctly 
                      scrolling the specified number of lines.
                   setview - will now allow X1 = X2 and Y1 = Y2 (previously 
                      X1 < X2 and Y1 < Y2 was enforced).
2.5  Release - March, 1997. SVGACC25
     Bugs Fixed:   Serveral functions had a problems with Matrox cards
     Additions:    All functions that were available only the the the registered version
                      are now in the shareware version, these include: fillconvexpoly,
                      fillpoly, pcxmake, xmsallocate, xmsblkget, xmsblkput, xmscopy,
                      xmserror, xmsfree, xmsget, xmsput, xmsscreenget & xmsscreenput.
                   ASM Source code is now available (see the file "SRC_CODE.TXT")	
 