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
#include <malloc.h>
#include <string.h>
#include <dos.h>
#include <math.h>

#include "svgacc.h"

#include "svgademo.h"

char showpcx(char fname[]);
void showhouse(D2Point *plotarray, D2Point *oplotarray);
void showstar(D2Point *plotarray, D2Point *oplotarray);


/********
 * DO2D *
 ********/

char do2d(void)
{
    int i, trans;
    int spcing, cntx, cnty;
    D2Point pointarray[9];
    D2Point plotarray[9];
    D2Point oplotarray[9];
    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    char buf2[TITLEN];

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 11: 2D functions");
    palset(pal,0,255);

    /*
     * Set up the star patter of points
     */
    cntx = maxx / 2;
    cnty = (maxy - 32) / 2 + 32;
    spcing = maxx / 15;
    pointarray[0].x = 0;
    pointarray[0].y = -spcing * 3;
    pointarray[1].x = spcing;
    pointarray[1].y = -spcing;
    pointarray[2].x = spcing * 3;
    pointarray[2].y = 0;
    pointarray[3].x = spcing;
    pointarray[3].y = spcing;
    pointarray[4].x = 0;
    pointarray[4].y = spcing * 3;
    pointarray[5].x = -spcing;
    pointarray[5].y = spcing;
    pointarray[6].x = -spcing * 3;
    pointarray[6].y = 0;
    pointarray[7].x = -spcing;
    pointarray[7].y = -spcing;
    pointarray[8].x = 0;
    pointarray[8].y = -spcing * 3;

    /*
     * Show d2translate
     */
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"d2translate(point,xtrans,ytrans,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    d2translate(9,cntx,cnty,pointarray,plotarray);
    showstar(plotarray,oplotarray);
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }
    trans = 0;
    for(i=0;i<spcing;i++) {
        trans+=2;
        d2translate(9,cntx+trans,cnty+trans,pointarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=0;i<spcing;i++) {
        trans-=2;
        d2translate(9,cntx+trans,cnty+trans,pointarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show d2scale
     */
    setview(0,16,maxx,31);
    fillview(0);
    setview(0,16,maxx,maxy);
    sprintf(buf,"d2scale(points,xscale,yscale,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    d2translate(9,cntx,cnty,pointarray,plotarray);
    showstar(plotarray,oplotarray);
    for(i=256;i<=380;i+=4) {
        d2scale(9,i,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=384;i>=128;i-=4) {
        d2scale(9,i,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=124;i<=256;i+=4) {
        d2scale(9,i,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show d2rotate
     */
    setview(0,16,maxx,31);
    fillview(0);
    setview(0,16,maxx,maxy);
    sprintf(buf,"d2rotate(points,xorigin,yorigin,angle,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    sprintf(buf2,"Let's do it about the center of the object.");
    drwstring(SET,7,0,buf2,10,32);
    setview(0,48,maxx,maxy);
    d2translate(9,cntx,cnty,pointarray,plotarray);
    showstar(plotarray,oplotarray);
    for(i=0;i<=180;i++) {
        d2rotate(9,0,0,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=180;i>=0;i-=2) {
        d2rotate(9,0,0,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show d2rotate (about an arbitrary point)
     */
    setview(0,16,maxx,48);
    fillview(0);
    setview(0,16,maxx,maxy);
    sprintf(buf,"d2rotate(points,xorigin,yorigin,angle,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    sprintf(buf2,"Let's do it about an arbitrary point.");
    drwstring(SET,7,0,buf2,10,32);
    setview(0,48,maxx,maxy);
    d2translate(9,cntx,cnty,pointarray,plotarray);
    showstar(plotarray,oplotarray);
    for(i=0;i<=360;i+=2) {
        d2rotate(9,0,spcing*3,i,pointarray,plotarray);
        d2translate(9,cntx,cnty,plotarray,plotarray);
        showstar(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    
    fillscreen(0);
    setview(0,0,maxx,maxy);
    
    return(ret);

}

/********
 * DO3D *
 ********/

char do3d(void)
{
    float pi;
    int i;
    float height, radius;
    int spcing;
    D3Point pointarray[14];
    D3Point playarray[14];
    D2Point plotarray[14];
    D2Point oplotarray[14];
    ProjParameters proj;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];
    

    /*
     * Set up the Title
     */
    sprintf(title,"DEMO 12: 3D functions");
    palset(pal,0,255);

    /*
     * Set up the house pattern of points
     */
    spcing = maxx / 6;
    pointarray[0].x = -spcing;
    pointarray[0].y = -spcing * 2;
    pointarray[0].z = 0;
    pointarray[1].x = spcing;
    pointarray[1].y = -spcing * 2;
    pointarray[1].z = 0;
    pointarray[2].x = spcing;
    pointarray[2].y = -spcing * 2;
    pointarray[2].z = spcing * 2;
    pointarray[3].x = -spcing;
    pointarray[3].y = -spcing * 2;
    pointarray[3].z = spcing * 2;
    pointarray[4].x = -spcing;
    pointarray[4].y = spcing * 2;
    pointarray[4].z = 0;
    pointarray[5].x = spcing;
    pointarray[5].y = spcing * 2;
    pointarray[5].z = 0;
    pointarray[6].x = spcing;
    pointarray[6].y = spcing * 2;
    pointarray[6].z = spcing * 2;
    pointarray[7].x = -spcing;
    pointarray[7].y = spcing * 2;
    pointarray[7].z = spcing * 2;
    pointarray[8].x = 0;
    pointarray[8].y = -spcing * 2;
    pointarray[8].z = spcing * 3;
    pointarray[9].x = 0;
    pointarray[9].y = spcing * 2;
    pointarray[9].z = spcing * 3;
    pointarray[10].x = 0;
    pointarray[10].y = 0;
    pointarray[10].z = 0;
    pointarray[11].x = spcing * 4;
    pointarray[11].y = 0;
    pointarray[11].z = 0;
    pointarray[12].x = 0;
    pointarray[12].y = 0;
    pointarray[12].z = spcing * 4;
    pointarray[13].x = 0;
    pointarray[13].y = spcing * 4;
    pointarray[13].z = 0;
    bytecopy(pointarray,playarray,sizeof(pointarray));

    /*
     * Show d3project
     */
    setview(0,0,maxx,maxy);
    pi = (float)(4. * atan(1) / 180.);
    fillscreen(0);
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"d3project(points,projparams,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    height = (float)(maxy * 8);
    radius = (float)(maxx * 30);
    proj.scrd = (int)(sqrt(radius * radius + height * height) / 2.);
    proj.theta = 110;
    proj.phi = (int)(atan(height / -radius) / pi);
    proj.eyex = (int)(-radius * cos(proj.theta * pi));
    proj.eyey = (int)(-radius * sin(proj.theta * pi));
    proj.eyez = (int)height;
    d3project(14,&proj,playarray,plotarray);
    for(i=0;i<14;i++) {
        oplotarray[i].x = plotarray[i].x;
        oplotarray[i].y = plotarray[i].y;
    }
    showhouse(plotarray,oplotarray);
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }
    for(i=112;i<=470;i+=3) {
        proj.theta = i;
        proj.eyex = (int)(-radius * cos(proj.theta * pi));
        proj.eyey = (int)(-radius * sin(proj.theta * pi));
        d3project(14,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show d3translate
     */
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"d3translate(points,xtrans,ytrans,ztrans,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    for(i=2;i<=300;i+=6) {
        d3translate(10,i,i,0,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=302;i>=2;i-=6) {
        d3translate(10,i,i,0,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show d3scale
     */
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"d3scale(points,xscale,yscale,zscale,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    for(i=256;i<=380;i+=4) {
        d3scale(10,i,i,i,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=384;i>=128;i-=4) {
        d3scale(10,i,i,i,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    for(i=124;i<=256;i+=4) {
        d3scale(10,i,i,i,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * show d3rotate
     */
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"d3rotate(points,xorigin,yorigin,zorigin,zangle,yangle,xangle,inarray,outarray);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    for(i=0;i<=360;i+=3) {
        d3rotate(10,0,0,0,0,i,i,pointarray,playarray);
        d3project(10,&proj,playarray,plotarray);
        showhouse(plotarray,oplotarray);
        sdelay(2);
    }
    
    ret = getkey();

    fillscreen(0);
    setview(0,0,maxx,maxy);

    return(ret);

}

/***********
 * DOMOUSE *
 ***********/

char domouse(void)
{
    int i, mouse;
    int colr, x1, x2, y1, y2;
    int lb, cb, rb, x, y, mbuts;
    int spcing;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];

    /*
     * Set up the title
     */
    sprintf(title,"DEMO 9: Mouse functions");
    fillscreen(0);
    palset(pal,0,255);
    setview(0,0,maxx,maxy);

    /*
     * Check to see if we have a mouse so we can do the mouse demo
     */
    mouse = whichmouse();
    if (mouse < 1) {
        drwstring(SET,7,0,title,10,0);
        sprintf(buf,"Sorry, no mouse detected... Can not do the mouse demo.");
        drwstring(SET,7,0,buf,10,16);
        ret = getkey();
        fillscreen(0);
        return(ret);
    }
    colr = 16;
    for(i=0;i<=maxx/2;i++) {
        drwcircle(SET,colr,maxx/4 + i, maxy/2, maxy/5);
        colr+=2;
        if (colr>255)
            colr = 16;
    }

    /*
     * Show mouseshow
     */
    setview(0,0,maxx,31);
    fillview(0);   
    drwstring(SET,7,0,title,10,0);
    sprintf(buf,"mouseshow();");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    mouseenter(); /* MUST BE CALLED FIRST TO ENABLE MOUSE FUNCTIONS */
    mouseshow();
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousestatus
     */
    mousehide();
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"mousestatus(xloc,yloc,mbuts);");
    drwstring(SET,7,0,buf,10,16);
    mouseshow();
    setview(0,32,maxx,maxy);
    beep();
    while(!kbhit()) {
        lb = cb = rb = 0;
        mousestatus(&x,&y,&mbuts);
        if (mbuts & 1)
            lb = 1;
        if (mbuts & 2)
            rb = 1;
        if (mbuts & 4)
            cb = 1;
        sprintf(buf,"X= %4d  Y= %4d  LB= %1d  CB= %1d  RB= %1d",x,y,lb,cb,rb);
        drwstring(SET,15,8,buf,10,32);
    }
    ret = (char)getch();
    if ( (ret == 'Q') || (ret == 'q') )
        endit = 1;
    if (ret == 'Q')
        ret = 'q';
    if (ret == 'S')
        ret = 's';
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousehide
     */
    mousehide();
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"mousehide(xloc,yloc,mbuts);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    beep();
    while(!kbhit()) {
        lb = cb = rb = 0;
        mousestatus(&x,&y,&mbuts);
        if (mbuts & 1)
            lb = 1;
        if (mbuts & 2)
            rb = 1;
        if (mbuts & 4)
            cb = 1;
        sprintf(buf,"X= %4d  Y= %4d  LB= %1d  CB= %1d  RB= %1d",x,y,lb,cb,rb);
        drwstring(SET,15,8,buf,10,32);
    }
    ret = (char)getch();
    if ( (ret == 'Q') || (ret == 'q') )
        endit = 1;
    if (ret == 'Q')
        ret = 'q';
    if (ret == 'S')
        ret = 's';
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mouserangeset
     */
    mousehide();
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"mouserangeset(x1,y1,x2,y2);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    spcing = (maxy - 32) / 3;
    x1 = spcing;
    y1 = 32 + spcing;
    x2 = maxx - spcing;
    y2 = maxy - spcing;
    drwbox(SET,15,x1,y1,x2,y2);
    mouseshow();
    mouserangeset(x1,y1,x2,y2);
    ret = getkey();
    mouserangeset(0,0,maxx,maxy);
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousecursorset - use the magnifier
     */
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"mousecursorset(mousecursor);");
    drwstring(SET,7,0,buf,10,16);
    setview(0,32,maxx,maxy);
    mousecursorset(&magmousecursor);
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousecursorset - use the big arrow
     */
    setview(0,32,maxx,maxy);
    mousecursorset(&bigmousecursor);
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousecursorset - use the stopwatch
     */
    setview(0,32,maxx,maxy);
    mousecursorset(&stwmousecursor);
    ret = getkey();
    if ((ret=='s') || (ret=='q')) {
        mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
        fillscreen(0);
        setview(0,0,maxx,maxy);
        return(ret);
    }

    /*
     * Show mousecursordefault
     */
    mousehide();
    setview(0,16,maxx,31);
    fillview(0);
    sprintf(buf,"mousecursordefault();");
    drwstring(SET,7,0,buf,10,16);
    mouseshow();
    setview(0,32,maxx,maxy);
    mousecursordefault();
    ret = getkey();
    mouseexit(); /* MUST BE CALLED TO DISABLE MOUSE FUNCTIONS */
    fillscreen(0);
    setview(0,0,maxx,maxy);

    return(ret);

}


/*********
 * DOPCX *
 *********/

char dopcx(void)
{
    
    int endthis;
    int ext, length;
    char c, ret;
    char title[TITLEN];
    char buf[TITLEN];
    char *fname;

    fname=malloc(128);

    /*
     * Setup the title
     */
    sprintf(title,"DEMO 8: PCX functions");

    /*
     * Show pcxgetinfo
     */
    setview(0,0,maxx,maxy);
    fillscreen(0);
    drwstring(SET,7,0,title,10,0);
    endthis = 0;
    ret = '\0';

    while (!endthis) {
        sprintf(buf,"Please provide the name (and full path if not in the current drive/directory)");
        drwstring(SET,7,0,buf,10,64);
        sprintf(buf,"of a PCX file you would like to see...");
        drwstring(SET,7,0,buf,10,80);
        sprintf(buf,"Filename:");
        drwstring(SET,7,0,buf,10,96);

        sprintf(fname,"_");
        length = 0;
        ext = 0;
        c = '\0';

        while(!ext) {
            drwstring(SET,7,0,fname,82,96);
            c = (char)getch();
            if(c>=' ' && c<='~') {
                fname[length] = c;
                fname[length+1] = '_';
                fname[length+2] = '\0';
                length++;
            }
            else
                if (c==8 && length>0) {
                    drwstring(SET,15,0,"   ",82+length*8,96);
                    length--;
                    fname[length] = '_';
                    fname[length+1] = '\0';
                }
                else
                    if (c==13)
                        ext = 1;
        }
        if (length==0) {
            free(fname);
            return(ret);
        }

        fname[length] = '\0';

        ret = showpcx(fname);

        if ((ret=='s') || (ret=='q')) {
            fillscreen(0);
            free(fname);
            return(ret);
        }

        drwstring(SET,7,0,title,10,0);
        sprintf(buf,"Would you like to see another (Y/N) ?");
        drwstring(SET,7,0,buf,10,64);
        ext = 0;
        while(!ext) {
            c=(char)getch();
            if ((c=='n') || (c=='N')) {
                ext = 1;
                endthis = 1;
            }
            else
                if ((c=='y') || (c=='Y'))
                    ext = 1;
        }
    }
    fillscreen(0);

    free(fname);
    
    return(ret);

}

/**************
 * DOJOYSTICK *
 **************/

char dojoystick(void)
{
    int maxxa, maxya, minxa, minya;
    int maxxb, maxyb, minxb, minyb;
    int jax, jay, jabuts, jbx, jby, jbbuts;
    int joystick, spcing, dist;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int cntax, cntay, cntbx, cntby;
    int rangexa, rangeya, rangexb, rangeyb;
    int jabax, jabay, jabbx, jabby;
    int jbbax, jbbay, jbbbx, jbbby;
    int oax, oay, obx, oby;
    char ret;
    char title[TITLEN];
    char buf[TITLEN];

    oax = oay = obx = oby = 0;

    /*
     * Set up the title
     */
    sprintf(title,"DEMO 10: Joystick functions");
    palset(pal,0,255);
    fillscreen(0);
    setview(0,0,maxx,maxy);
    drwstring(SET,7,0,title,10,0);

    /*
     * Check to see if we have a joystick so we can do the joystick demo
     */
    joystick = whichjoystick();
    if (joystick < 1) {
        sprintf(buf,"Sorry, no joystick detected... Can not do the joystick demo.");
        drwstring(SET,7,0,buf,10,16);
        ret = getkey();
        fillscreen(0);
        return(ret);
    }

    /*
     * Show joystickinfo (here we do some joystick calibration
     */
    sprintf(buf,"joystickinfo(jax,jay,jabuts,jbx,jby,jbbuts);");
    drwstring(SET,7,0,buf,10,16);
    switch(joystick) {
        case 1:
            sprintf(buf,"Please move Joystick A as far as it will go in all directions.");
            break;
        case 2:
            sprintf(buf,"Please move Joystick B as far as it will go in all directions.");
            break;
        case 3:
            sprintf(buf,"Please move Joystick A and B as far as they will go in all directions.");
            break;
    }
    drwstring(SET,7,0,buf,10,32);
    drwstring(SET,7,0,"And then press a key...",10,48);

    maxxa = -1;
    maxya = -1;
    minxa = 10000;
    minya = 10000;
    maxxb = -1;
    maxyb = -1;
    minxb = 10000;
    minyb = 10000;
    do {
        while(!kbhit()) {
            joystickinfo(&jax,&jay,&jabuts,&jbx,&jby,&jbbuts);
            if (joystick & 1) {
                if (jax>maxxa)
                    maxxa = jax;
                if (jax<minxa)
                    minxa = jax;
                if (jay>maxya)
                    maxya = jay;
                if (jay<minya)
                    minya = jay;
            }
            if (joystick & 2) {
                if (jbx>maxxb)
                    maxxb = jbx;
                if (jbx<minxb)
                    minxb = jbx;
                if (jby>maxyb)
                    maxyb = jby;
                if (jby<minyb)
                    minyb = jby;
            }
        }
        ret = getkey();
    } while ( ((joystick & 1) && ((maxxa==minxa) || (maxya==minya))) || 
        ((joystick & 2) && ((maxxb==minxb) || (maxyb==minyb))) );

    if ((ret=='s') || (ret=='q')) {
        setview(0,0,maxx,maxy);
        fillscreen(0);
        return(ret);
    }

    /*
     * Calculate the center and stuff
     */
    spcing = maxx / 7;
    dist = spcing * 2;
    x1 = spcing / 2;
    y1 = spcing / 2 + 32;
    x2 = x1 + dist;
    y2 = y1 + dist;
    x4 = maxx - spcing;
    y4 = y2;
    x3 = x4 - dist;
    y3 = y1;
    cntax = (x2 - x1) / 2 + x1;
    cntay = (y2 - y1) / 2 + y1;
    cntbx = (x4 - x3) / 2 + x3;
    cntby = (y4 - y3) / 2 + y3;
    rangexa = maxxa - minxa;
    rangeya = maxya - minya;
    rangexb = maxxb - minxb;
    rangeyb = maxyb - minyb;
    jabax = (x2 - x1) / 4 + x1 - 16;
    jabay = spcing / 4 + y2 - 6;
    jabbx = x2 - (x2 - x1) / 4 - 16;
    jabby = spcing / 4 + y2 - 6;
    jbbax = (x4 - x3) / 4 + x3 - 16;
    jbbay = spcing / 4 + y4 - 6;
    jbbbx = x4 - (x4 - x3) / 4 - 16;
    jbbby = spcing / 4 + y4 - 6;

    /*
     * Let's move it (or them) around
     */
    setview(0,32,maxx,maxy);
    fillview(0);
    drwstring(SET,7,0,"Joysticks are nonlinear devices and may not appear centered.",10,32);

    if (joystick & 1) {
        drwbox(SET,15,x1-1,y1-1,x2+1,y2+1);
        drwbox(SET,15,x1-1,y2+1,x2+1,y2+spcing/2);
        drwline(SET,15,(x2-x1)/2+x1,y2+1,(x2-x1)/2+x1,y2+spcing/2);
        oax = cntax;
        oay = cntay;
        drwline(SET,10,cntax,cntay,oax,oay);
    }
    else {
        drwbox(SET,8,x1-1,y1-1,x2+1,y2+1);
        drwbox(SET,8,x1-1,y2+1,x2+1,y2+spcing/2);
        drwline(SET,8,(x2-x1)/2+x1,y2+1,(x2-x1)/2+x1,y2+spcing/2);
    }
    if (joystick & 2) {
        drwbox(SET,15,x3-1,y3-1,x4+1,y4+1);
        drwbox(SET,15,x3-1,y4+1,x4+1,y4+spcing/2);
        drwline(SET,15,(x4-x3)/2+x3,y4+1,(x4-x3)/2+x3,y4+spcing/2);
        obx = cntbx;
        oby = cntby;
        drwline(SET,10,cntbx,cntby,obx,oby);
    }
    else {
        drwbox(SET,8,x3-1,y3-1,x4+1,y4+1);
        drwbox(SET,8,x3-1,y4+1,x4+1,y4+spcing/2);
        drwline(SET,8,(x4-x3)/2+x3,y4+1,(x4-x3)/2+x3,y4+spcing/2);
    }
    while(!kbhit()) {
        joystickinfo(&jax,&jay,&jabuts,&jbx,&jby,&jbbuts);
        if (joystick & 1) {
            setview(x1,y1,x2,y2);
            jax = jax - minxa;
            jax = jax * dist / rangexa + x1;
            jay = jay - minya;
            jay = jay * dist / rangeya + y1;
            drwline(SET,0,cntax,cntay,oax,oay);
            oax = jax;
            oay = jay;
            drwline(SET,10,cntax,cntay,oax,oay);
            setview(0,0,maxx,maxy);
            sprintf(buf,"ButA");
            if (jabuts & 1)
                drwstring(SET,10,0,buf,jabax,jabay);
            else
                drwstring(SET,8,0,buf,jabax,jabay);
            sprintf(buf,"ButB");
            if (jabuts & 2)
                drwstring(SET,10,0,buf,jabbx,jabby);
            else
                drwstring(SET,8,0,buf,jabbx,jabby);
        }
        if (joystick & 2) {
            setview(x3,y3,x4,y4);
            jbx = jbx - minxb;
            jbx = jbx * dist / rangexb + x3;
            jby = jby - minyb;
            jby = jby * dist / rangeyb + y3;
            drwline(SET,0,cntbx,cntby,obx,oby);
            obx = jbx;
            oby = jby;
            drwline(SET,10,cntbx,cntby,obx,oby);
            setview(0,0,maxx,maxy);
            sprintf(buf,"ButA");
            if (jbbuts & 1)
                drwstring(SET,10,0,buf,jbbax,jbbay);
            else
                drwstring(SET,8,0,buf,jbbax,jbbay);
            sprintf(buf,"ButB");
            if (jbbuts & 2)
                drwstring(SET,10,0,buf,jbbbx,jbbby);
            else
                drwstring(SET,8,0,buf,jbbbx,jbbby);
        }
    }
    ret = getkey();
    fillscreen(0);
    setview(0,0,maxx,maxy);
    return(ret);
}


/***********
 * SHOWPCX *
 ***********/

char showpcx(char fname[])
{
    int i, ok;
    int mincolor, maxcolor;
    int xsize, ysize, numcol;
    int xloc, yloc;
    int fixit;
    long t,min,max;
    PaletteData pcxpal;
    char ret;
    char *buf;

    buf = malloc(TITLEN);

    mincolor = maxcolor = 0;

    /*
     * Show pcxgetinfo
     */
    palset(orgpal,0,255);
    setview(0,0,maxx,maxy);
    fillscreen(0);
    drwstring(SET,7,0,"DEMO 8: PCX functions",10,0);
    sprintf(buf,"pcxgetinfo(filename,pcxxsize,pcxysize,numcolors,palette);");
    drwstring(SET,7,0,buf,10,16);
    ok = pcxgetinfo(fname,&xsize,&ysize,&numcol,pcxpal);
    min = pow(255,2) * 3;
    max = 0;
    if (ok == 1) {
        /*
         * We need to check the PCX color palette entries to see if any colors
         * are greater than six bits in length as the VGA color palette
         * registers are only six bits wide.  We also look for the brightest
         * and darkest colors to use as our text and background colors.
         */
        fixit = 0;
        for(i=0;i<numcol;i++) {
            if((pcxpal[i].r>63) || (pcxpal[i].g>63) || (pcxpal[i].b>63))
                fixit = 1;
            t = pow(pcxpal[i].r,2) + pow(pcxpal[i].g,2) + pow(pcxpal[i].b,2);
            if(t<min) {
                min = t;
                mincolor = i;
            }
            if(t>max) {
                max = t;
                maxcolor = i;
            }
        }
        /*
         * If the PCX uses more than 6 bit color, then we shift each color entry
         * right by 2 bits.  (This reduces it to 6 bits of color.)
         */
        if (fixit)
            for(i=0;i<numcol;i++) {
                pcxpal[i].r>>=2;
                pcxpal[i].g>>=2;
                pcxpal[i].b>>=2;
            }
        /*
         * If the PCX has a palette of 128 colors or less, then we can use
         * our own colors for the text and background.
         */
        if (numcol<=128) {
            pcxpal[254].r = pcxpal[254].g = pcxpal[254].b = 0;
            mincolor = 254;
            pcxpal[255].r = pcxpal[255].g = pcxpal[255].b = 32;
            maxcolor = 255;
        }

        sprintf(buf,"'%s' is identified as a v3.0 PCX image.",fname);
        drwstring(SET,15,0,buf,10,64);
        sprintf(buf,"Dimensions are: %d pixels wide and %d pixels high.",xsize,ysize);
        drwstring(SET,15,0,buf,10,80);
        sprintf(buf,"Number of colors: %d.",numcol);
        drwstring(SET,15,0,buf,10,96);

        ret = getkey();
        if ((ret=='s') || (ret=='q')) {
            fillscreen(0);
            setview(0,0,maxx,maxy);
            palset(orgpal,0,255);
            free(buf);
            return(ret);
        }

        /*
         * Show pcxput
         */
        palset(pcxpal,0,255);
        overscanset(mincolor);
        fillscreen(mincolor);
        drwstring(SET,maxcolor,mincolor,"DEMO 8: PCX functions",10,0);
        sprintf(buf,"pcxput(mode,x,y,filename);");
        drwstring(SET,maxcolor,mincolor,buf,10,16);
        setview(0,32,maxx,maxy);
        xloc = maxx / 2 - xsize / 2;
        yloc = (maxy - 32) / 2 - ysize / 2 + 32;
        ok = pcxput(SET,xloc,yloc,fname);
        if (ok!=1) {
            palset(orgpal,0,255);
            sprintf(buf,"The file '%s'",fname);
            switch (ok) {
                case 0:
                    strcat(buf," does not exist in the specified directory.");
                    break;
                case -1:
                    strcat(buf," is not a v3.0 PCX file.");
                    break;
                case -2:
                    strcat(buf," is not run length encoded.");
                    break;
                default: /* should have a value of -3 */
                    strcat(buf," has some general error.");
            }
            drwstring(SET,15,0,buf,10,64);
        }
    }
    else {
        palset(orgpal,0,255);
        sprintf(buf,"The file '%s'",fname);
        switch (ok) {
            case 0:
                strcat(buf," does not exist in the specified directory.");
                break;
            case -1:
                strcat(buf," is not a v3.0 PCX file.");
                break;
            case -2:
                strcat(buf," is not run length encoded.");
                break;
            default: /* should have a value of -3 */
                strcat(buf," has some general error.");
        }
        drwstring(SET,15,0,buf,10,64);
    }

    ret = getkey();

    palset(orgpal,0,255);
    overscanset(0);
    fillscreen(0);
    setview(0,0,maxx,maxy);
    free(buf);
    return(ret);
}


/*************
 * SHOWHOUSE *
 *************/

void showhouse(D2Point *plotarray, D2Point *oplotarray)
{
    int i;

    /* Erase old axes */
    drwline(SET,0,(oplotarray+10)->x,(oplotarray+10)->y,(oplotarray+11)->x,(oplotarray+11)->y);
    drwline(SET,0,(oplotarray+10)->x,(oplotarray+10)->y,(oplotarray+12)->x,(oplotarray+12)->y);
    drwline(SET,0,(oplotarray+10)->x,(oplotarray+10)->y,(oplotarray+13)->x,(oplotarray+13)->y);
    
    /* Erase old house */
    for(i=0;i<3;i++) {
        drwline(SET,0,(oplotarray+i)->x,(oplotarray+i)->y,(oplotarray+i+1)->x,(oplotarray+i+1)->y);
        drwline(SET,0,(oplotarray+i+4)->x,(oplotarray+i+4)->y,(oplotarray+i+4+1)->x,(oplotarray+i+4+1)->y);
        drwline(SET,0,(oplotarray+i)->x,(oplotarray+i)->y,(oplotarray+i+4)->x,(oplotarray+i+4)->y);
    }
    drwline(SET,0,(oplotarray+3)->x,(oplotarray+3)->y,(oplotarray+7)->x,(oplotarray+7)->y);
    drwline(SET,0,(oplotarray+0)->x,(oplotarray+0)->y,(oplotarray+3)->x,(oplotarray+3)->y);
    drwline(SET,0,(oplotarray+4)->x,(oplotarray+4)->y,(oplotarray+7)->x,(oplotarray+7)->y);
    drwline(SET,0,(oplotarray+3)->x,(oplotarray+3)->y,(oplotarray+8)->x,(oplotarray+8)->y);
    drwline(SET,0,(oplotarray+8)->x,(oplotarray+8)->y,(oplotarray+2)->x,(oplotarray+2)->y);
    drwline(SET,0,(oplotarray+9)->x,(oplotarray+9)->y,(oplotarray+7)->x,(oplotarray+7)->y);
    drwline(SET,0,(oplotarray+9)->x,(oplotarray+9)->y,(oplotarray+6)->x,(oplotarray+6)->y);
    drwline(SET,0,(oplotarray+8)->x,(oplotarray+8)->y,(oplotarray+9)->x,(oplotarray+9)->y);

    /* Draw new axes */
    drwline(SET,8,(plotarray+10)->x,(plotarray+10)->y,(plotarray+11)->x,(plotarray+11)->y);
    drwline(SET,8,(plotarray+10)->x,(plotarray+10)->y,(plotarray+12)->x,(plotarray+12)->y);
    drwline(SET,8,(plotarray+10)->x,(plotarray+10)->y,(plotarray+13)->x,(plotarray+13)->y);
    
    /* Draw new house */
    for(i=0;i<3;i++) {
        drwline(SET,10,(plotarray+i)->x,(plotarray+i)->y,(plotarray+i+1)->x,(plotarray+i+1)->y);
        drwline(SET,10,(plotarray+i+4)->x,(plotarray+i+4)->y,(plotarray+i+4+1)->x,(plotarray+i+4+1)->y);
        drwline(SET,10,(plotarray+i)->x,(plotarray+i)->y,(plotarray+i+4)->x,(plotarray+i+4)->y);
    }
    drwline(SET,10,(plotarray+3)->x,(plotarray+3)->y,(plotarray+7)->x,(plotarray+7)->y);
    drwline(SET,10,(plotarray+0)->x,(plotarray+0)->y,(plotarray+3)->x,(plotarray+3)->y);
    drwline(SET,10,(plotarray+4)->x,(plotarray+4)->y,(plotarray+7)->x,(plotarray+7)->y);
    drwline(SET,10,(plotarray+3)->x,(plotarray+3)->y,(plotarray+8)->x,(plotarray+8)->y);
    drwline(SET,10,(plotarray+8)->x,(plotarray+8)->y,(plotarray+2)->x,(plotarray+2)->y);
    drwline(SET,10,(plotarray+9)->x,(plotarray+9)->y,(plotarray+7)->x,(plotarray+7)->y);
    drwline(SET,10,(plotarray+9)->x,(plotarray+9)->y,(plotarray+6)->x,(plotarray+6)->y);
    drwline(SET,10,(plotarray+8)->x,(plotarray+8)->y,(plotarray+9)->x,(plotarray+9)->y);

    /* Save old points */
    bytecopy(plotarray,oplotarray,14*sizeof(*plotarray));

    return;
}

/************
 * SHOWSTAR *
 ************/

void showstar(D2Point *plotarray, D2Point *oplotarray)
{
    int i;

    for(i=0;i<8;i++)
        drwline(SET,0,(oplotarray+i)->x,(oplotarray+i)->y,((oplotarray+i)+1)->x,((oplotarray+i)+1)->y);
    for(i=0;i<8;i++)
        drwline(SET,10,(plotarray+i)->x,(plotarray+i)->y,((plotarray+i)+1)->x,((plotarray+i)+1)->y);
    bytecopy(plotarray,oplotarray,9*sizeof(*plotarray));
    return;
}
 