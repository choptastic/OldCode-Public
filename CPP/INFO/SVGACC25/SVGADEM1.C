/****************************************************************************

      'SVGACC' A Super Vga Graphics Library for use with Microsoft compatible
      C/C++ compilers
      Copyright 1993-1997 by Stephen L. Balkum and Daniel A. Sill

    **************** UNREGISTERD SHAREWARE VERSION ***********************
    * FOR EVUALATION ONLY. NOT FOR RESALE IN ANY FORM. SOFTWARE WRITTEN  *
    * USING THIS UNREGISTERED SHAREWARE GRAPHICS LIBRARY MAY NOT BY SOLD *
    * OR USED FOR ANY PURPOSE OTHER THAN THE EVUALTION OF THIS LIBRARY.  *
    **********************************************************************

    **************** NO WARRANTIES AND NO LIABILITY **********************
    * Stephen L. Balkum and Daniel A. Sill provide no warranties, either *
    * expressed or implied, of merchantability, or fitness, for a        *
    * particular use or purpose of this SOFTWARE and documentation.      *
    * In no event shall Stephen L. Balkum or Daniel A. Sill be held      *
    * liable for any damages resulting from the use or misuse of the     *
    * SOFTWARE and documentation.                                        *
    **********************************************************************

    ************** U.S. GOVERNMENT RESTRICTED RIGHTS *********************
    * Use, duplication, or disclosure of the SOFTWARE and documentation  *
    * by the U.S. Government is subject to the restictions as set forth  *
    * in subparagraph (c)(1)(ii) of the Rights in Technical Data and     *
    * Computer Software cluse at DFARS 252.227-7013.                     *
    * Contractor/manufacturer is Stephen L. Balkum and Daniel A. Sill,   *
    * P.O. Box 7704, Austin, Texas 78713-7704                            *
    **********************************************************************

    **********************************************************************
    * By using this SOFTWARE or documentation, you agree to the above    *
    * terms and conditions.                                              *
    **********************************************************************

 ***************************************************************************/

#define MODULE

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#include "svgacc.h"
#include "svgademo.h"

#define randnum(size) (rand() % (int)(size))

/***********
 * DOBLOCK *
 ***********/

char doblock(void)
{
    int i, colr;
    int xinc, yinc, x1, y1, x2, y2;
    int cntx, cnty;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    RasterBlock far *gfxblk;
    RasterBlock far *gfxblk2;
    RasterBlock far *spritebkgnd;

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 5: Block function and Sprites");
    palset(pal,0,255);

    /*
     * Show Block Get (draw some circles and "get a chunk of them")
     */

    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"blkget(x1,y1,x2,y2,GfxBlock);");
    drwstring(SET,7,0,buf,10,16);
    colr = 16;
    for(i=0;i<=maxx/2;i++) {
        drwcircle(SET,colr,maxx/4+i,maxy/2,maxy/5);
        colr+=2;
        if(colr>255)
            colr = 16;
    }

    xinc = maxx/20;
    yinc = maxy/20;
    x1 = maxx/2-xinc;
    y1 = maxy/2-yinc;
    x2 = maxx/2+xinc;
    y2 = maxy/2+yinc;
    i = (x2-x1+1)*(y2-y1+1)+4;
    gfxblk = _fmalloc(i);
    if (!gfxblk) {
        restext();
        printf("ERROR: Allocating memory for gfxblk: %d bytes\n",i);
        exit(1);
    }
    drwbox(SET,0,x1,y1,x2,y2);
    blkget(x1,y1,x2,y2,gfxblk);

    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        fillscreen(0);
        _ffree(gfxblk);
        return(ret);
    }

    /*
     * Show Block Rotate and Sprite Stuff
     */
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"blkrotate(angle,backfill,GfxBlockSrc,GfxBlockDst);");
    drwstring(SET,7,0,buf,10,16);
    sprintf(buf,"spritegap(transcolor,x,y,SpriteArray,BkGndArray);");
    drwstring(SET,7,0,buf,10,32);
    sprintf(buf,"spriteput(transcolor,x,y,SpriteArray);");
    drwstring(SET,7,0,buf,10,48);
    cntx = (x2-x1) / 2 + x1;
    cnty = (y2-y1) / 2 + y1;
    fillarea(x1+2,y1+2,0,0);
    i = blkrotatesize(45,gfxblk);
    spritebkgnd = _fmalloc(i);
    if (!spritebkgnd) {
        restext();
        printf("ERROR: Allocating memory for spritebkgnd: %d bytes\n",i);
        exit(1);
    }
    gfxblk2 = _fmalloc(i);
    if (!gfxblk2) {
        restext();
        printf("ERROR: Allocating memory for gfxblk2: %d bytes\n",i);
        exit(1);
    }
    blkget(x1,y1,x2,y2,spritebkgnd);
    setview(0,64,maxx,maxy);

    for(i=0;i<=360;i+=4) {
        blkrotate(i,1,gfxblk,gfxblk2);
        spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);
        spritegap(1,cntx-(gfxblk2->width)/2,cnty-(gfxblk2->height)/2,gfxblk2,spritebkgnd);
        sdelay(4);
    }
    spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);
    blkput(SET,x1,y1,gfxblk);

    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        fillscreen(0);
        palset(pal,16,255);
        _ffree(gfxblk);
        _ffree(gfxblk2);
        _ffree(spritebkgnd);
        return(ret);
    }

    /*
     * Show Block Resize and Sprite Stuff
     */
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"blkresize(Width,Height,GfxBlockSrc,GfxBlockDst);");
    drwstring(SET,7,0,buf,10,16);
    sprintf(buf,"spritegap(transcolor,x,y,SpriteArray,BkGndArray);");
    drwstring(SET,7,0,buf,10,32);
    sprintf(buf,"spriteput(transcolor,x,y,SpriteArray);");
    drwstring(SET,7,0,buf,10,48);
    fillarea(x1+2,y1+2,0,0);
    blkget(x1,y1,x2,y2,spritebkgnd);
    setview(0,64,maxx,maxy);

    i = (x2-x1+1+xinc)*(y2-y1+1+xinc)+4;

    spritebkgnd = _frealloc(spritebkgnd,i);
    if (!spritebkgnd) {
        restext();
        printf("ERROR: reallocating memory for spritebkgnd: %d bytes\n",i);
        exit(1);
    }

    gfxblk2 = _frealloc(gfxblk2,i);
    if (!gfxblk2) {
        restext();
        printf("ERROR: reallocating memory for gfxblk2: %d bytes\n",i);
        exit(1);
    }

    for(i=0;i<=xinc;i++) {
        blkresize((gfxblk->width)-i,(gfxblk->height)-i,gfxblk,gfxblk2);
        spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);
        spritegap(1,cntx-(gfxblk2->width)/2,cnty-(gfxblk2->height)/2,gfxblk2,spritebkgnd);
        sdelay(3);
    }
    spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);

    for(i=xinc;i>=0;i--) {
        blkresize((gfxblk->width)-i,(gfxblk->height)-i,gfxblk,gfxblk2);
        spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);
        spritegap(1,cntx-(gfxblk2->width)/2,cnty-(gfxblk2->height)/2,gfxblk2,spritebkgnd);
        sdelay(3);
    }
    spriteput(SET,1,cntx-(spritebkgnd->width)/2,cnty-(spritebkgnd->height)/2,spritebkgnd);
    blkput(SET,x1,y1,gfxblk);

    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        fillscreen(0);
        palset(pal,16,255);
        setview(0,0,maxx,maxy);
        _ffree(gfxblk);
        _ffree(gfxblk2);
        _ffree(spritebkgnd);
        return(ret);
    }


    /*
     * Show Block Put (put the "chunks" randomly around the screen)
     */
    setview(0,16,maxx,32);
    fillview(0);
    sprintf(buf,"blkput(mode,x,y,GfxBlock);");
    drwstring(SET,7,0,buf,10,16);
    xinc = maxx/10;
    yinc = maxy/10;
    setview(0,32,maxx,maxy);
    for(i=0;i<=maxx/2;i++) {
        x1 = randnum(maxx + xinc) - xinc;
        y1 = randnum(maxy + yinc) - yinc;
        blkput(SET,x1,y1,gfxblk);
    }

    _ffree(gfxblk);
    _ffree(gfxblk2);
    _ffree(spritebkgnd);
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        fillscreen(0);
        return(ret);
    }

    return(ret);

}



/**********
 * DOCLIP *
 **********/

char doclip(void)
{
    struct dcoord {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    int i, j, k;
    int xinc, x, y, x1, y1, x2, y2;
    int xsub, radx, rady;
    int wdth, hgth, spcingx, spcingy;
    struct dcoord b[4];
    char ret;
    char title[TITLEN];
    char buf[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 2: Clipping capability");
    palset(pal,0,255);

    /*
     * Set up the windows
     */

    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"All pimitives automatically clip");
    drwstring(SET,7,0,buf,10,16);

    wdth = (maxx + 1) * 4 / 9;
    spcingx = ((maxx + 1) - wdth * 2) / 3;
    hgth = (maxy + 1 - 35) * 4 / 9;
    spcingy = ((maxy + 1 - 35) - hgth * 2) / 3;
    xinc = wdth * 3 / 2;
    xsub = wdth / 4;

    b[0].x1 = spcingx;
    b[0].x2 = b[0].x1 + wdth;
    b[0].y1 = spcingy + 35;
    b[0].y2 = b[0].y1 + hgth;

    b[1].x2 = maxx - spcingx;
    b[1].x1 = b[1].x2 - wdth;
    b[1].y1 = spcingy + 35;
    b[1].y2 = b[1].y1 + hgth;

    b[2].x2 = maxx - spcingx;
    b[2].x1 = b[2].x2 - wdth;
    b[2].y2 = maxy - spcingy;
    b[2].y1 = b[2].y2 - hgth;

    b[3].x1 = spcingx;
    b[3].x2 = b[3].x1 + wdth;
    b[3].y2 = maxy - spcingy;
    b[3].y1 = b[3].y2 - hgth;

    for(i=0;i<4;i++)
        drwbox(SET,15,b[i].x1++,b[i].y1++,b[i].x2--,b[i].y2--);

    /*
     * Show the clipping
     */
    for(i=0;i<=maxx/6;i++)
        for(j=0;j<4;j++) {
            setview(b[j].x1,b[j].y1,b[j].x2,b[j].y2);
            switch (j) {
                case 0:
                    for(k=0;k<6;k++) {
                        x = b[j].x1 + randnum(xinc) - xsub;
                        y = b[j].y1 + randnum(xinc) - xsub;
                        drwpoint(SET,randnum(16),x,y);
                    }
                    break;
                case 1:
                    x1 = b[j].x1 + randnum(xinc) - xsub;
                    y1 = b[j].y1 + randnum(xinc) - xsub;
                    x2 = b[j].x1 + randnum(xinc) - xsub;
                    y2 = b[j].y1 + randnum(xinc) - xsub;
                    drwline(SET,randnum(16),x1,y1,x2,y2);
                    break;
                case 2:
                    x = b[j].x1 + randnum(xinc) - xsub;
                    y = b[j].y1 + randnum(xinc) - xsub;
                    radx = randnum(wdth) / 2;
                    drwcircle(SET,randnum(16),x,y,radx);
                    break;
                case 3:
                    x = b[j].x1 + randnum(xinc) - xsub;
                    y = b[j].y1 + randnum(xinc) - xsub;
                    radx = randnum(wdth) / 2;
                    rady = randnum(wdth) / 2;
                    drwellipse(SET,randnum(16),x,y,radx,rady);
                    break;
            }
        }

    setview(0,0,maxx,maxy);

    ret = getkey();

    return(ret);

}

/**********
 * DOFILL *
 **********/

char dofill(void)
{
    struct dcoord {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    int i, colr;
    int x, y;
    int radx, rady;
    int wdth, hgth, spcingx, spcingy;
    struct dcoord b[4];
    char ret;
    char title[TITLEN];
    char buf[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 3: Filling functions");
    palset(pal,0,255);

    /*
     * Set up the windows
     */

    fillscreen(10);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"fillscreen(color);");
    drwstring(SET,7,0,buf,10,16);

    ret = getkey();
    if ((ret == 's') || (ret == 'q'))
        return(ret);

    /*
     * Set up windows and show viewport fill
     */
    fillscreen(0);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"fillview(color);");
    drwstring(SET,7,0,buf,10,16);

    wdth = (maxx + 1) * 4 / 9;
    spcingx = ((maxx + 1) - wdth * 2) / 3;
    hgth = (maxy + 1 - 35) * 4 / 9;
    spcingy = ((maxy + 1 - 35) - hgth * 2) / 3;

    b[0].x1 = spcingx;
    b[0].x2 = b[0].x1 + wdth;
    b[0].y1 = spcingy + 35;
    b[0].y2 = b[0].y1 + hgth;

    b[1].x2 = maxx - spcingx;
    b[1].x1 = b[1].x2 - wdth;
    b[1].y1 = spcingy + 35;
    b[1].y2 = b[1].y1 + hgth;

    b[2].x2 = maxx - spcingx;
    b[2].x1 = b[2].x2 - wdth;
    b[2].y2 = maxy - spcingy;
    b[2].y1 = b[2].y2 - hgth;

    b[3].x1 = spcingx;
    b[3].x2 = b[3].x1 + wdth;
    b[3].y2 = maxy - spcingy;
    b[3].y1 = b[3].y2 - hgth;

    for(i=0;i<4;i++)
        drwbox(SET,15,b[i].x1++,b[i].y1++,b[i].x2--,b[i].y2--);

    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show the clipping
     */
    for(i=0;i<4;i++) {
        setview(b[i].x1,b[i].y1,b[i].x2,b[i].y2);
        fillview(i+10);
    }

    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret == 's') || (ret == 'q'))
        return(ret);

    /*
     * Set up windows and show area fill
     */
    fillscreen(0);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"fillarea(xseed,yseed,bordercolor,fillcolor);");
    drwstring(SET,7,0,buf,10,16);

    drwbox(SET,15,5,35,maxx-4,maxy-4);
    setview(6,36,maxx-5,maxy-5);

    colr=1;
    for(i=0;i<=maxx/10;i++) {
        x = 50 + randnum(maxx-50);
        y = 50 + randnum(maxy-50);
        radx = 2 + randnum(maxx/20);
        rady = 2 + randnum(maxy/20);
        drwellipse(SET,colr++,x,y,radx,rady);
        if (colr>9)
            colr = 1;
    }

    for(i=0;i<=maxx/15;i++) {
        x = 50 + randnum(maxx-50);
        y = 50 + randnum(maxy-50);
        radx = 2 + randnum(maxx/20);
        rady = 2 + randnum(maxy/20);
        drwellipse(SET,12,x,y,radx,rady);
    }

    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        return(ret);
    }

    fillarea(7,37,12,10);

    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret == 's') || (ret == 'q'))
        return(ret);

    /*
     * Setup windows and show color fill
     */
    fillscreen(0);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"fillcolor(xseed,yseed,oldcolor,fillcolor);");
    drwstring(SET,7,0,buf,10,16);

    drwbox(SET,15,5,35,maxx-4,maxy-4);
    setview(6,36,maxx-5,maxy-5);

    colr=1;
    for(i=0;i<=maxx/10;i++) {
        x = 50 + randnum(maxx-50);
        y = 50 + randnum(maxy-50);
        radx = 2 + randnum(maxx/20);
        rady = 2 + randnum(maxy/20);
        drwellipse(SET,colr++,x,y,radx,rady);
        if (colr>9)
            colr = 1;
    }

    for(i=0;i<=maxx/15;i++) {
        x = 50 + randnum(maxx-50);
        y = 50 + randnum(maxy-50);
        radx = 2 + randnum(maxx/20);
        rady = 2 + randnum(maxy/20);
        drwellipse(SET,12,x,y,radx,rady);
    }

    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        return(ret);
    }

    fillcolor(7,37,0,10);

    setview(0,0,maxx,maxy);

    ret = getkey();

    return(ret);

}


/*********
 * DOPAL *
 *********/

char dopal(void)
{
    int x1, x2, y1, y2;
    int i, colr;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 4: Palette functions");
    palset(orgpal,0,255);

    /*
     * Show palette set/get
     */

    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"palget(pal,beg,end),palset(pal,beg,end)");
    drwstring(SET,7,0,buf,10,16);

    colr = 16;
    x1 = 10;
    x2 = maxx - 9;
    y1 = 35;
    y2 = maxy - 9;
    i = 0;
    while (y1+i < y2-i) {
        drwbox(SET,colr++,x1+i,y1+i,x2-i,y2-i);
        if (colr>255)
            colr = 16;
        i++;
    }
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }
    palset(pal,16,255);
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        fillscreen(0);
        return(ret);
    }

    /*
     * Show palette auto fade out/in
     */
    setview(0,16,maxx,32);
    fillview(0);
    sprintf(buf,"palioauto(pal,beg,end,speed);");
    drwstring(SET,7,0,buf,10,16);
    palioauto(pal,16,255,-2);
    palioauto(pal,16,255,2);
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show palette auto fade to
     */
    setview(0,16,maxx,32);
    fillview(0);
    sprintf(buf,"palchgauto(pal,newpal,beg,end,speed);");
    drwstring(SET,7,0,buf,10,16);
    palchgauto(pal,pal2,16,255,2);
    palchgauto(pal2,pal,16,255,2);
    ret = getkey();
    if ((ret == 's') || (ret == 'q')) {
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show palette rotate
     */
    setview(0,16,maxx,32);
    fillview(0);
    sprintf(buf,"palrotate(pal,beg,end,shift);");
    drwstring(SET,7,0,buf,10,16);
    for(i=0;i<=240;i++) {
        palrotate(pal,16,255,2);
        palget(pal,16,255);
    }
    for(i=0;i<=120;i++) {
        palrotate(pal,16,255,-8);
        palget(pal,16,255);
    }
    ret = getkey();
    if ((ret == 's') || (ret == 'q'))
        setview(0,0,maxx,maxy);

    return(ret);

}


/***********
 * DOPRIMS *
 ***********/

char doprims(void)
{

    int x1, x2, y1, y2;
    int maxrad, radx, rady;
    int i, colr, num, sang, eang;
    int ofst, intsbits, numlevels;
    D2Point p1, off1, off2, p2;

    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    PaletteData pal;

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 1: Primitives");
    palset(orgpal,0,255);

    /*
     * Draw some points
     */

    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwpoint(mode,color,x,y);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx * 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        drwpoint(SET,colr++,x1,y1);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some lines
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwline(mode,color,x1,y1,x2,y2);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 6;

    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        x2 = randnum(maxx);
        y2 = randnum(maxy);
        drwline(SET,colr++,x1,y1,x2,y2);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some antialiased lines
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwaline(colorbits,color,x1,y1,x2,y2);  [antialised lines]");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    num = maxx / 8;
    intsbits = 3; /* provide 2^3=8 shades */
    numlevels = 1 << intsbits;
    palget(pal,0,255);
    for (i=0;i<numlevels;i++) {

        /* do not shade completely to zero:  colors range from 63 - 28 */

        /* blue */
        ofst = 128 + numlevels * 0 + i;
        pal[ofst].r = 0;
        pal[ofst].g = 0;
        pal[ofst].b = (char)(63-35*i/(numlevels-1));

        /* green */
        ofst = 128 + numlevels * 1 + i;
        pal[ofst].r = 0;
        pal[ofst].g = (char)(63-35*i/(numlevels-1));
        pal[ofst].b = 0;

        /* cyan */
        ofst = 128 + numlevels * 2 + i;
        pal[ofst].r = 0;
        pal[ofst].g = (char)(63-35*i/(numlevels-1));
        pal[ofst].b = (char)(63-35*i/(numlevels-1));

        /* red */
        ofst = 128 + numlevels * 3 + i;
        pal[ofst].r = (char)(63-35*i/(numlevels-1));
        pal[ofst].g = 0;
        pal[ofst].b = 0;

        /* magenta */
        ofst = 128 + numlevels * 4 + i;
        pal[ofst].r = (char)(63-35*i/(numlevels-1));
        pal[ofst].g = 0;
        pal[ofst].b = (char)(63-35*i/(numlevels-1));

        /* yellow */
        ofst = 128 + numlevels * 5 + i;
        pal[ofst].r = (char)(63-35*i/(numlevels-1));
        pal[ofst].g = (char)(63-35*i/(numlevels-1));
        pal[ofst].b = 0;

        /* white */
        ofst = 128 + numlevels * 6 + i;
        pal[ofst].r = (char)(63-35*i/(numlevels-1));
        pal[ofst].g = (char)(63-35*i/(numlevels-1));
        pal[ofst].b = (char)(63-35*i/(numlevels-1));

    }
    palset(pal,0,255);
    colr = 0;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        x2 = randnum(maxx);
        y2 = randnum(maxy);
        drwaline(intsbits,128+colr*numlevels,x1,y1,x2,y2);
        colr++;
        if (colr>6)
            colr = 0;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    palset(orgpal,0,255);
    if ((ret=='s') || (ret=='q'))
        return(ret);


    /*
     * Draw some boxes
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwbox(mode,color,x1,y1,x2,y2);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 10;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        x2 = randnum(maxx);
        y2 = randnum(maxy);
        drwbox(SET,colr++,x1,y1,x2,y2);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some filled boxes
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwfillbox(mode,color,x1,y1,x2,y2);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 15;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        x2 = randnum(maxx);
        y2 = randnum(maxy);
        drwfillbox(SET,colr++,x1,y1,x2,y2);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some circles
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwcircle(mode,color,cx,cy,radius);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 20;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        drwcircle(SET,colr++,x1,y1,radx);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some filled circles
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwfillcircle(mode,color,cx,cy,radius);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 25;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        drwfillcircle(SET,colr++,x1,y1,radx);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Draw some ellipses
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwellipse(mode,color,cx,cy,radiusx,radiusy);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 20;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        rady = randnum(maxrad);
        drwellipse(SET,colr++,x1,y1,radx,rady);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();


    /*
     * Draw some filled ellipses
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwfillellipse(mode,color,cx,cy,radiusx,radiusy);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 25;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        rady = randnum(maxrad);
        drwfillellipse(SET,colr++,x1,y1,radx,rady);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);


    /*
     * Draw some circular arcs
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwcirarc(mode,color,cx,cy,radius,startang,endang);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 20;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        sang = randnum(360);
        eang = randnum(360) + sang;
        drwcirarc(SET,colr++,x1,y1,radx,sang,eang);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);


    /*
     * Draw some elliptical arcs
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwellarc(mode,color,cx,cy,radiusx,radiusy,startang,endang);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 20;
    maxrad = maxx / 2;
    for(i=0;i<num;i++) {
        x1 = randnum(maxx);
        y1 = randnum(maxy);
        radx = randnum(maxrad);
        rady = randnum(maxrad);
        sang = randnum(360);
        eang = randnum(360) + sang;
        drwellarc(SET,colr++,x1,y1,radx,rady,sang,eang);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);


    /*
     * Draw some cubic bezier curves
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwcubicbezier(mode,color,pon1,poff1,poff2,pon2);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 1;
    num = maxx / 20;
    for(i=0;i<num;i++) {
        p1.x = randnum(maxx);
        p1.y = randnum(maxy);
        off1.x = randnum(maxx);
        off1.y = randnum(maxy);
        off2.x = randnum(maxx);
        off2.y = randnum(maxy);
        p2.x = randnum(maxx);
        p2.y = randnum(maxy);
        drwcubicbezier(SET,colr++,&p1,&off1,&off2,&p2);
        if (colr>15)
            colr = 1;
    }
    setview(0,0,maxx,maxy);
    ret = getkey();
    return(ret);

}


/************
 * DOSCROLL *
 ************/

char doscroll(void)
{
    int i, j, colr, num, totnum;
    int a, b, c, d;
    int x1, x2, y1, y2;
    int spcing, skip;
    long numbanks, numpages, banksperpage;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    char buf2[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 7: Scroll functions");
    palset(pal,0,255);
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);

    spcing = (maxy - 32) / 5;
    x1 = (maxx + 1) / 2 - spcing;
    y1 = (maxy + 1 - 32) / 2 + 32 - spcing;
    x2 = (maxx + 1) / 2 + spcing;
    y2 = (maxy + 1 - 32) / 2 + 32 + spcing;
    skip = spcing / 15;
    num = spcing / skip;
    if (spcing / 2 != (float)spcing / 2.)
        spcing++;


    drwbox(SET,12,x1++,y1++,x2--,y2--);
    colr = 16;
    sprintf(buf2,"TEXT text TEXT");

    /*
     * Show scrollup
     */
    setview(0,16,maxx,maxy);
    sprintf(buf,"scrollup(x1,y1,x2,y2,numlines,fillcolor);");
    drwstring(SET,7,0,buf,10,16);
    setview(x1,y1,x2,y2);
    fillview(0);
    totnum = maxx / 10;
    for(i=0;i<totnum;i++) {
        a = randnum(maxx);
        b = randnum(maxy);
        c = randnum(maxx);
        d = randnum(maxy);
        drwline(SET,colr,a,b,c,d);
        colr += 3;
        if (colr > 255)
            colr = 16;
    }
    drwstring(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringlt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringrt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringdn(SET,7,0,buf2,x1+spcing,y1+spcing);

    for(i=0;i<num;i++)
        scrollup(x1,y1,x2,y2,skip,0);

    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Show scrolllt
     */
    setview(0,16,maxx,maxy);
    sprintf(buf,"scrolllt(x1,y1,x2,y2,numlines,fillcolor);");
    drwstring(SET,7,0,buf,10,16);
    setview(x1,y1,x2,y2);
    fillview(0);
    totnum = maxx / 10;
    for(i=0;i<totnum;i++) {
        a = randnum(maxx);
        b = randnum(maxy);
        c = randnum(maxx);
        d = randnum(maxy);
        drwline(SET,colr,a,b,c,d);
        colr += 3;
        if (colr > 255)
            colr = 16;
    }
    drwstring(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringlt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringrt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringdn(SET,7,0,buf2,x1+spcing,y1+spcing);

    for(i=0;i<num;i++)
        scrolllt(x1,y1,x2,y2,skip,0);

    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Show scrolldn
     */
    setview(0,16,maxx,maxy);
    sprintf(buf,"scrolldn(x1,y1,x2,y2,numlines,fillcolor);");
    drwstring(SET,7,0,buf,10,16);
    setview(x1,y1,x2,y2);
    fillview(0);
    totnum = maxx / 10;
    for(i=0;i<totnum;i++) {
        a = randnum(maxx);
        b = randnum(maxy);
        c = randnum(maxx);
        d = randnum(maxy);
        drwline(SET,colr,a,b,c,d);
        colr += 3;
        if (colr > 255)
            colr = 16;
    }
    drwstring(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringlt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringrt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringdn(SET,7,0,buf2,x1+spcing,y1+spcing);

    for(i=0;i<num;i++)
        scrolldn(x1,y1,x2,y2,skip,0);

    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Show scrollrt
     */
    setview(0,16,maxx,maxy);
    sprintf(buf,"scrollrt(x1,y1,x2,y2,numlines,fillcolor);");
    drwstring(SET,7,0,buf,10,16);
    setview(x1,y1,x2,y2);
    fillview(0);
    totnum = maxx / 10;
    for(i=0;i<totnum;i++) {
        a = randnum(maxx);
        b = randnum(maxy);
        c = randnum(maxx);
        d = randnum(maxy);
        drwline(SET,colr,a,b,c,d);
        colr += 3;
        if (colr > 255)
            colr = 16;
    }
    drwstring(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringlt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringrt(SET,7,0,buf2,x1+spcing,y1+spcing);
    drwstringdn(SET,7,0,buf2,x1+spcing,y1+spcing);

    for(i=0;i<num;i++)
        scrollrt(x1,y1,x2,y2,skip,0);

    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    /*
     * Show paging
     */
     setview(0,0,maxx,maxy);

    /*
     * check to see if card supports changing the diplay offset
     */

    if (pagedisplay(0,0,0) == 0) {
        fillscreen(0);
        drwstring(SET,7,0,title,10,0);
        sprintf(buf,"Sorry, This video card does not support");
        drwstring(SET,7,0,buf,10,16);
        sprintf(buf,"changing the display offset in this");
        drwstring(SET,7,0,buf,10,32);
        sprintf(buf,"video mode. Unable to do the paging demo.");
        drwstring(SET,7,0,buf,10,48);
        sprintf(buf,"Press a key...");
        drwstring(SET,7,0,buf,10,64);
        ret = getkey();
        fillscreen(0);
        return(ret);
     }

    /*
     * check to see if there is enough memory for multiple pages
     */

    numbanks = (long)(maxx + 1) * (long)(maxy + 1);
    banksperpage = numbanks / (long)65536;
    if(numbanks % 65536l)
        banksperpage++; /* round up if there is extra */
    numbanks = (long)whichmem() / (long)64;
    numpages = (numbanks / banksperpage) - 1;

    /*
     * limit total number of pages to 3 (0-2) for this demo
     */

    if (numpages >= 3)
        numpages = 2;

    if (numpages == 0) {
        fillscreen(0);
        drwstring(SET,7,0,title,10,0);
        sprintf(buf,"Sorry, this video card does not have enough video memory to");
        drwstring(SET,7,0,buf,10,16);
        sprintf(buf,"support multiple video pages in this video mode.");
        drwstring(SET,7,0,buf,10,32);
        sprintf(buf,"Press a key...");
        drwstring(SET,7,0,buf,10,48);
        ret = getkey();
        fillscreen(0);
        return(ret);
     }


    totnum = maxx / 6;
    fillscreen(0);
    for(i=0;i<=numpages;i++) {
        setview(0,0,maxx,maxy);
        pageactive(i);
        pagedisplay(0,0,i);
        fillpage(0);
        drwstring(SET,7,0,title,10,0);
        sprintf(buf,"pageactive(page)");
        drwstring(SET,7,0,buf,10,16);
        sprintf(buf,"pagedisplay(startx,starty,page)");
        drwstring(SET,7,0,buf,10,32);
        sprintf(buf,"This Is Page %d",i);
        for(j=0;j<20;j++)
            drwstring(SET,12+i,0,buf,10,50+j*16);
        setview(150,58,maxx-10,maxy-10);
        for(j=0;j<totnum;j++) {
            x1 = randnum(maxx);
            y1 = randnum(maxy);
            x2 = randnum(100);
            y2 = randnum(100);
            colr += 1;
            if (colr > 16)
                colr = 1;
            switch (i) {
                case 0:
                    drwfillcircle(SET,colr,x1,y1,x2);
                    break;
                case 1:
                    drwline(SET,colr,x1,y1,x1+x2,y1+y2);
                    drwellipse(SET,colr,x1,y1,x2/4,y2/4);
                    break;
                case 2:
                    drwfillbox(SET,colr,x1,y1,x1+x2,y1+y2);
                    break;
            }
        }
        drwbox(SET,15,150,58,maxx-10,maxy-10);
        sdelay(35);
    }
    pageactive(0);
    pagedisplay(0,0,0);
    ret = getkey();
    if ((ret=='s') || (ret=='q'))
        return(ret);

    for(j=0;j<2;j++) {
        for(i=0;i<=numpages;i++) {
            pagedisplay(0,0,i);
            sdelay(35);
        }
    }
    for(j=0;j<20;j++) {
        for(i=0;i<=numpages;i++) {
            pagedisplay(0,0,i);
            sdelay(1);
        }
    }
    pagedisplay(0,0,0);
    setview(0,0,maxx,maxy);
    ret = getkey();
    return(ret);

}


/**********
 * DOTEXT *
 **********/

char dotext(void)
{
    int i, colr;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    char buf2[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 6: Text functions");
    palset(pal,0,255);

    /*
     * Show alternate print directions
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"drwstring(mode,foregnd,bkgnd,string,x,y);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    sprintf(buf2,"The Quick Brown Fox Jumped Over The Lazy Dog's Back! 0123456789");
    colr = 16;
    for(i=32;i<=maxy;i+=20) {
        drwstring(SET,colr,0,buf2,0,i);
        colr+=5;
        if (colr>255)
            colr = 16;
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        setview(0,0,maxx,maxy);
        fillscreen(0);
        return(ret);
    }

    fillview(0);
    setview(0,16,maxx,32);
    sprintf(buf,"drwstringlt(mode,foregnd,bkgnd,string,x,y);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 16;
    for(i=0;i<=maxx;i+=20) {
        drwstringlt(SET,colr,0,buf2,i,maxy);
        colr+=5;
        if (colr>255)
            colr = 16;
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        setview(0,0,maxx,maxy);
        fillscreen(0);
        return(ret);
    }

    fillview(0);
    setview(0,16,maxx,32);
    sprintf(buf,"drwstringdn(mode,foregnd,bkgnd,string,x,y);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 16;
    for(i=maxy;i>=32;i-=20) {
        drwstringdn(SET,colr,0,buf2,maxx,i);
        colr+=5;
        if (colr>255)
            colr = 16;
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        setview(0,0,maxx,maxy);
        fillscreen(0);
        return(ret);
    }

    fillview(0);
    setview(0,16,maxx,32);
    sprintf(buf,"drwstringrt(mode,foregnd,bkgnd,string,x,y);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    colr = 16;
    for(i=maxx;i>=0;i-=20) {
        drwstringrt(SET,colr,0,buf2,i,32);
        colr+=5;
        if (colr>255)
            colr = 16;
    }
    ret = getkey();
    setview(0,0,maxx,maxy);
    fillscreen(0);

    return(ret);

}

 