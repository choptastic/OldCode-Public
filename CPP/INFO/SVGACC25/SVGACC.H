/* SVGACC Include File for Microsoft compatible C/C++ compilers
 * Copyright 1993-1997 by Stephen L. Balkum and Daniel A. Sill
 * Zephyr Software P.O. Box 7704, Austin, Texas  78713-7704
 * Last Update 1/1/96
 */

#ifndef SVGACC_H
#define SVGACC_H

typedef unsigned char byte;

typedef struct {
    char r;
    char g;
    char b;
} RGB;

typedef RGB PaletteData[256];

typedef struct {
    byte hotspotx;
    byte hotspoty;
    byte data[384];
} MouseCursor;

typedef struct {
    byte width;
    byte height;
    byte data[4096];
} Font;

typedef enum {
    NO_ACTION = 0,
    SET,
    XOR,
    OR,
    AND
} PixelMode;

typedef enum {
    UNKNOWN = 0,
    ACUMOS,
    ATI,
    AHEADA,
    AHEADB,
    CHIPSTECH,
    CIRRUS,
    EVEREX,
    GENOA,
    NCR,
    OAKTECH,
    PARADISE,
    REALTEK,
    TRIDENT,
    TSENG3,
    TSENG4,
    VESA,
    VIDEO7,
    AVANCE,
    MXIC,
    PRIMUS
} VGAChipset;

typedef struct {
    unsigned int width;
    unsigned int height;
    byte data[1];
} RasterBlock;

typedef struct {
    int x;
    int y;
} D2Point;

typedef struct {
    int x;
    int y;
    int z;
} D3Point;

typedef struct {
    int eyex;
    int eyey;
    int eyez;
    int scrd;
    int theta;
    int phi;
} ProjParameters;

#ifdef __cplusplus
extern "C" {
#endif

/* Global variables */
extern const int far maxx;
extern const int far maxy;
extern const int far viewx1;
extern const int far viewy1;
extern const int far viewx2;
extern const int far viewy2;

/* 'BLocK' methods to manipulate RasterBlocks on and off the screen */

extern int  far blkget (int x1, int y1, int x2, int y2, RasterBlock far *gfxblk);
extern void far blkput (PixelMode mode, int x, int y, RasterBlock far *gfxblk);
extern void far blkresize (unsigned newxsize, unsigned newysize, RasterBlock far *sourcegfxblk, RasterBlock far *destgfxblk);
extern int  far blkrotate (int ang, int backfill, RasterBlock far *sourcegfxblk, RasterBlock far *destgfxblk);
extern int  far blkrotatesize (int ang, RasterBlock far *sourcegfxblk);

/* 'BYTECOPY' method for fast memory copy */

extern void far bytecopy (void far *src, void far *dst, unsigned long numbytes);

/* '2D' methods to transform D2Points */

extern void far d2rotate (int points, int xorigin, int yorigin, int ang, D2Point far *inary, D2Point far *outary);
extern void far d2scale (int points, int xscale, int yscale, D2Point far *inary, D2Point far *outary);
extern void far d2translate (int points, int xtrans, int ytrans, D2Point far *inary, D2Point far *outary);

/* '3D' methods to transform D3Points */

extern int  far d3project (int points, ProjParameters far *params, D3Point far *inary, D2Point far *outary);
extern void far d3rotate (int points, int xorigin, int yorigin, int zorigin, int zrang, int yrang, int xrang, D3Point far *inary, D3Point far *outary);
extern void far d3scale (int points, int xscale, int yscale, int zscale, D3Point far *inary, D3Point far *outary);
extern void far d3translate (int points, int xtrans, int ytrans, int ztrans, D3Point far *inary, D3Point far *outary);

/* 'DRaW' methods for placing text and graphics primitives on screen */

extern void far drwaline (int colrbits, int colr, int x1, int y1, int x2, int y2);
extern void far drwbox (PixelMode mode, int colr, int x1, int y1, int x2, int y2);
extern void far drwcirarc (PixelMode mode, int colr, int centerx, int centery, int radius, long startang, long endang);
extern void far drwcircle (PixelMode mode, int colr, int centerx, int centery, int radius);
extern void far drwcubicbezier (PixelMode mode, int colr, D2Point far *pon1, D2Point far *poff1, D2Point far *poff2, D2Point far *pon2);
extern void far drwellarc (PixelMode mode, int colr, int centerx, int centery, int radiusx, int radiusy, long startang, long endang);
extern void far drwellipse (PixelMode mode, int colr, int centerx, int centery, int radiusx, int radiusy);
extern void far drwfillbox (PixelMode mode, int colr, int x1, int y1, int x2, int y2);
extern void far drwfillcircle (PixelMode mode, int colr, int centerx, int centery, int radius);
extern void far drwfillellipse (PixelMode mode, int colr, int centerx, int centery, int radiusx, int radiusy);
extern void far drwline (PixelMode mode, int colr, int x1, int y1, int x2, int y2);
extern void far drwpoint (PixelMode mode, int colr, int x, int y);
extern void far drwstring (PixelMode mode, int fcolr, int bcolr, const char far *strng, int x, int y);
extern void far drwstringdn (PixelMode mode, int fcolr, int bcolr, const char far *strng, int x, int y);
extern void far drwstringlt (PixelMode mode, int fcolr, int bcolr, const char far *strng, int x, int y);
extern void far drwstringrt (PixelMode mode, int fcolr, int bcolr, const char far *strng, int x, int y);

/* 'FILL' methods for filling various regions on screen with a color */

extern void far fillarea (int xseed, int yseed, int bordercolr, int fillcolr);
extern void far fillconvexpoly (int colr, int points, D2Point far *inary);
extern void far fillpoly (int colr, int points, D2Point far *inary);
extern void far fillcolor (int xseed, int yseed, int oldcolr, int newcolr);
extern void far fillpage (int colr);
extern void far fillscreen (int colr);
extern void far fillview (int colr);

/* 'FONT' methods for setting the current font */

extern void far fontgetinfo (int far *wdth, int far *hght);
extern void far fontset (Font far *font);
extern void far fontsystem (void);

/* 'GET' methods to return information held by library */

extern void far getlaststring (RasterBlock far *strnggfxblk);
extern long far getarccos (long cosvalue);
extern long far getarcsin (long sinvalue);
extern long far getarctan (long tanvalue);
extern long far getcos (long angle);
extern int  far getpoint (int x, int y);
extern long far getsin (long angle);
extern long far gettan (long angle);

/* 'JOYSTICK' method to read joysticks' status */

extern void far joystickinfo (int far *jax, int far *jay, int far *jabuts, int far *jbx, int far *jby, int far *jbbuts);

/* 'MOUSE' methods to interact with mouse driver */

extern void far mousebutpress (int reqbut, int far *xloc, int far *yloc, int far *num, int far *mbuts);
extern void far mousebutrelease (int reqbut, int far *xloc, int far *yloc, int far *num, int far *mbuts);
extern void far mousecursordefault (void);
extern void far mousecursorset (MouseCursor far *mousecursor);
extern void far mouseenter (void);
extern void far mouseexit (void);
extern void far mousehide (void);
extern void far mouseinfo (int far *drvmajorver, int far *drvminorver, int far *mousetype, int far *irqnumber);
extern void far mouselocset (int xloc, int yloc);
extern void far mouserangeset (int x1, int y1, int x2, int y2);
extern void far mouserestorestate (byte far *mousebuf);
extern void far mousesavestate (byte far *mousebuf);
extern void far mousesensset (int xsens, int ysens, int dblspdthresh);
extern void far mouseshow (void);
extern void far mousestatus (int far *x, int far *y, int far *mbuts);
extern int  far mousestoragesize (void);

extern void far overscanset (int colr);

/* 'PAGE' methods to control paging abilities */

extern int  far pageactive (int page);
extern int  far pagedisplay (int x, int y, int page);

/* 'PALette' methods to manipulate and activate palettes */

extern void far palchgauto (RGB far *pal, RGB far *newpal, int firstcolr, int lastcolr, int speed);
extern void far palchgstep (RGB far *pal, RGB far *newpal, int firstcolr, int lastcolr, int percent);
extern void far palcopy (RGB far *srcpal, RGB far *destpal, int firstcolr, int lastcolr);
extern void far paldimstep (RGB far *pal, int firstcolr, int lastcolr, int percent);
extern void far palget (RGB far *pal, int firstcolr, int lastcolr);
extern void far palioauto (RGB far *pal, int firstcolr, int lastcolr, int speed);
extern void far palrotate (RGB far *pal, int firstcolr, int lastcolr, int shift);
extern void far palset (RGB far *pal, int firstcolr, int lastcolr);

/* 'PCX' methods to read / write PCX files and place images on screen */

extern int  far pcxgetinfo (const char far *name, int far *pcxxsize, int far *pcxysize, int far *numcolors, RGB far *pal);
extern int  far pcxmake (int x1, int y1, int x2, int y2, const char far *name);
extern int  far pcxput (PixelMode mode, int xloc, int yloc, const char far *name);

/* 'RESolution' methods to set various video modes */

extern int  far res320 (void);
extern int  far res640 (void);
extern int  far res640l (void);
extern int  far res800 (void);
extern int  far res1024 (void);
extern int  far res1280 (void);
extern int  far restext (void);

/* 'SCROLL' methods for scrolling various sections of the screen */

extern void far scrolldn (int x1, int y1, int x2, int y2, int num, int colr);
extern void far scrolllt (int x1, int y1, int x2, int y2, int num, int colr);
extern void far scrollrt (int x1, int y1, int x2, int y2, int num, int colr);
extern void far scrollup (int x1, int y1, int x2, int y2, int num, int colr);

/* 'Sync' DELAY method */

extern void far sdelay (int count);

/* 'SET' methods to adjust library internal variables */

extern void far setcard (VGAChipset chip, int mem);
extern void far setview (int x1, int y1, int x2, int y2);

/* 'SPRITE' methods for manipulating sprites on and off screen */

extern int  far spritecolldetect (int transcolr, int x1, int y1, int x2, int y2, RasterBlock far *sprite1, RasterBlock far *sprite2);
extern void far spritegap (int transcolr, int x, int y, RasterBlock far *sprite, RasterBlock far *spritebkgnd);
extern void far spriteget (int transcolr, int x, int y, RasterBlock far *sprite, RasterBlock far *spritebkgnd);
extern void far spriteput (PixelMode mode, int transcolr, int x, int y, RasterBlock far *sprite);

/* 'VIDEO' methods to interact with video mode and display */

extern int  far videomodeget (void);
extern void far videomodeset (int videomode);
extern void far videooff (void);
extern void far videoon (void);

/* 'Identification' methods to discover WHICH hardware is available */

extern int  far whichcpu (void);
extern int  far whichjoystick (void);
extern int  far whichmem (void);
extern int  far whichmouse (void);
extern VGAChipset far whichvga (void);
extern int  far whichxms (unsigned int far *xmskbytesavail, unsigned int far *xmshandlesavail);

/* 'XMS' methods to store and retrieve extended memory */

extern int  far xmsallocate (unsigned int reqkbytes);
extern int  far xmsblkget (int x1, int y1, int x2, int y2);
extern int  far xmsblkput (PixelMode mode, int x, int y, int xmshandle);
extern int  far xmscopy (int xmssrchandle, long srcoffset, int xmsdesthandle, long destoffset, unsigned long count);
extern int  far xmserror (void);
extern int  far xmsfree (int xmshandle);
extern int  far xmsget (int xmshandle, long offset, void far *destmem, unsigned long count);
extern int  far xmsput (void far *sourcemem, int xmshandle, long offset, unsigned long count);
extern int  far xmsscreenget (void);
extern int  far xmsscreenput (int xmshandle);

#ifdef __cplusplus
}
#endif

#endif
/* SVGACC_H */


 