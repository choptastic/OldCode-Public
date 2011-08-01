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
    

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dos.h>

#include "svgacc.h"

#include "svgademo.h"


void main(void) {

    int startvideomode;
    int i, max, ky;
    int mjv, mnv, tp;
    int cpu, videomemory;
    int mouse, joystick;
    int res;
    int offset, colr;
    float mypi;
    char dummy;
    char buf[TITLEN];
    char *dumptr;
    
    
    /*
     * Save the starting videomode and set it to mode 3.
     */
    startvideomode = videomodeget();
    restext();
    screenclear();
    
    /*
     * Move the DOS cursor to the top left to start the program and say hello
     */
    screengoto(11,0);
    printf("/*SVGACC.LIB/* A SuperVGA Graphics Library for use with\n");
    screengoto(23,1);
    printf("Microsoft compatible C/C++ compilers\n");
    screengoto(9,2);
    printf("Copyright 1993-1997 by Stephen L. Balkum and Daniel A. Sill\n");
    screengoto(23,11);
    printf("Demonstration/Example Program\n");
    screengoto(0,22);
    printf("press a key to begin the demo...\n");
    getkey();

    screenclear();
   
    /*
     * Let's id the processor first as the library requires a 386 or better.
     */
    screengoto(0,0);
    cpu = whichcpu();
    if (cpu < 386) {
        printf("Sorry, this library requires an 80386 or better processor.\n");
        printf("Processor is identified as an 80%d.\n", cpu);
        printf("Demo program will be terminated.\n\n");
        printf("press a key...\n");
        getkey();
        videomodeset(startvideomode);
        exit(0);
    }


    /*
     * Let's id the video card/chip as the library requires a SuperVGA adapter.
     */
    switch(whichvga()) {
        case ACUMOS:
            sprintf(buf,"Acumos AVGA2/3 SuperVGA");
            break;
        case ATI:
            sprintf(buf,"ATI Technologies 18/28/38/68800 SuperVGA");
            break;
        case AHEADA:
            sprintf(buf,"Ahead V5000 Ver A SuperVGA");
            break;
        case AHEADB:
            sprintf(buf,"Ahead V5000 Ver B SuperVGA");
            break;
        case CHIPSTECH:
            sprintf(buf,"Chips and Technologies 82C450/1/2/3/5/6/7 SuperVGA");
            break;
        case CIRRUS:
            sprintf(buf,"Cirrus Logic CL-GD 5xx,6xx,28xx,54xx,62xx SuperVGA");
            break;
        case EVEREX:
            sprintf(buf,"Everex EV236/6xx Micro Enhancer SuperVGA");
            break;
        case GENOA:
            sprintf(buf,"Genoa 61/62/63/64/6600 SuperVGA");
            break;
        case NCR:
            sprintf(buf,"NCR 77C21/22/22E/22E+ SuperVGA");
            break;
        case OAKTECH:
            sprintf(buf,"Oak Technologies OTI-037/67/77/87C SuperVGA");
            break;
        case PARADISE:
            sprintf(buf,"Paradise/Western Digital PVGA1A,WD90C00/1x/2x/3x SuperVGA");
            break;
        case REALTEK:
            sprintf(buf,"Realtek RT3106 SuperVGA");
            break;
        case TRIDENT:
            sprintf(buf,"Trident 8800CS,8900B/C/CL/CX,90x0 SuperVGA");
            break;
        case TSENG3:
            sprintf(buf,"Tseng Labs ET3000-AX/BX/BP SuperVGA");
            break;
        case TSENG4:
            sprintf(buf,"Tseng Labs ET4000/W32/W32I SuperVGA");
            break;
        case VESA:
            sprintf(buf,"VESA compatible SuperVGA");
            break;
        case VIDEO7:
            sprintf(buf,"Video 7 HT-208/16 SuperVGA");
            break;
        case AVANCE:
            sprintf(buf,"Avance Logic AL2101 SuperVGA");
            break;
        case MXIC:
            sprintf(buf,"MXIC MX68000/10 SuperVGA");
            break;
        case PRIMUS:
            sprintf(buf,"Primus P2000 SuperVGA");
            break;
        default:
            printf("Microprocessor is identified as an 80%d.\n", cpu);
            printf("Sorry, unable to identify video card or it is not a SuperVGA video adapter.\n");
            printf("Demo program will be terminated.\n\n");
            printf("press a key...\n");
            getkey();
            videomodeset(startvideomode);
            exit(0);
    }
    printf("Microprocessor is identified as an 80%d.\n", cpu);
    
    fontsystem();
    printf("Video card/chip is identified as %s.\n",&buf);
   
    /*
     * Let's see the how much memory is installed on the super vga adapter.
     */
    videomemory = whichmem();
    if (videomemory < 1) {
        printf("Sorry, unable to identify the amount of installed video memory.\n");
        printf("Demo program will be terminated.\n\n");
        printf("press a key...\n");
        getkey();
        videomodeset(startvideomode);
        exit(0);
    } else
        printf("Installed video memory identified as %dkb.\n", videomemory);
       
    /*
     * Let's tell the user what the highest resolution that the video card
     * and its installed memory card is capable of. The monitor must be able
     * to support those modes too !
     */
    printf("Video card and installed memory is capable of the following resolutions:\n");
    if (videomemory > 2047) {
        printf("    320x200 in 256 colors\n");
        printf("    640x400 in 256 colors\n");
        printf("    640x480 in 256 colors\n");
        printf("    800x600 in 256 colors\n");
        printf("    1024x768 in 256 colors\n");
        printf("    1280x1024 in 256 colors\n");
        max = 5;
    } else if (videomemory > 1023) {
        printf("    320x200 in 256 colors\n");
        printf("    640x400 in 256 colors\n");
        printf("    640x480 in 256 colors\n");
        printf("    800x600 in 256 colors\n");
        printf("    1024x768 in 256 colors\n");
        max = 4;
    } else if (videomemory > 511) {
        printf("    320x200 in 256 colors\n");
        printf("    640x400 in 256 colors\n");
        printf("    640x480 in 256 colors\n");
        printf("    800x600 in 256 colors\n");
        max = 3;
    } else {
        printf("    320x200 in 256 colors\n");
        printf("    640x400 in 256 colors\n");
        max = 1;
    }
    printf("\nPlease keep in mind that not all monitors support all resolutions. If You\n");
    printf("know your monitor will not work properly at very high resolution(ie 1024x768\n");
    printf("or 1280x1024) then do NOT attempt to run the demo in that resolution.\n\n");

    /*
     * Let's look for a mouse. if we find one, tell all about it
     */
    mouse = whichmouse();
    if (mouse > 0) {
        mouseinfo(&mjv, &mnv, &tp, &i);
        switch (tp) {
            case 1:
                sprintf(buf,"bus mouse");
                break;
            case 2:
                sprintf(buf,"serial mouse");
                break;
            case 3:
                sprintf(buf,"Inport mouse");
                break;
            case 4:
                sprintf(buf,"PS/2 mouuse");
                break;
            case 5:
                sprintf(buf,"HP mouse");
                break;
            default:
                sprintf(buf,"unknown type");
        }
        printf("Microsoft compatible %s detected with %d buttons on IRQ %d.\n", &buf, mouse, i);
        printf("Software driver version is %d.%d (Microsoft equivalent version).\n\n", mjv, mnv);

    } else
        printf("No Microsoft compatible mouse detected.\n\n");

    /*
     * Let's look for joysticks
     */
    joystick = whichjoystick();
    switch (joystick) {
        case -1:
            printf("No joystick port detected or no joystick BIOS support present.\n\n");
            break;
        case 0:
            printf("No joystick detected\n\n");
            break;
        case 1:
            printf("Joystick A is present and available.\n\n");
            break;
        case 2:
            printf("Joystick B is present and available.\n\n");
            break;
        case 3:
            printf("Both Joystick A and Joystick B are present and available.\n\n");
            break;
    }
    printf("press a key...\n");
    getkey();


    /*
     * Let's get down to business
     */
    res = 1;
    endit = 0;
    ky=0;
    
    /*
     * Init alternate color palettes
     */

    res320();
    palget(orgpal, 0, 255);
    palcopy(orgpal,pal,0,255);
    palcopy(orgpal,pal2,0,255);
    mypi=(float)(8 * atan(1) / 240);
    offset = 16;
    for (colr=0;colr<240;colr++,offset++) {
        pal[offset].r = (char)(32.0 + sin((colr + 0) * mypi) * 31.0);
        pal[offset].g = (char)(32.0 + sin((colr + 80) * mypi) * 31.0);
        pal[offset].b = (char)(32.0 + sin((colr + 160) * mypi) * 31.0);
        pal2[offset].r = (char)(32.0 + sin((colr + 10) * mypi) * 31.0);
        pal2[offset].g = (char)(32.0 + sin((colr + 30) * mypi) * 31.0);
        pal2[offset].b = (char)(32.0 + sin((colr + 50) * mypi) * 31.0);
    }
    restext();

    /*
     * Here is the main selector loop
     */
    while (endit == 0) {
        screenclear();
        switch (res) {
            case 1: 
                sprintf(buf,"320x200x256");
                break;
            case 2:
                sprintf(buf,"640x400x256");
                break;
            case 3:
                sprintf(buf,"640x480x256");
                break;
            case 4:
                sprintf(buf,"800x600x256");
                break;
            case 5:
                sprintf(buf,"1024x768x256");
                break;
            case 6:
                sprintf(buf,"1280x1024x256");
        }
        printf("Please select the demo you would like to see in the %s resolution:\n\n",&buf);
        printf("(0)  Exit This Program\n\n");
        printf("(1)  Demo #1  The Primitive Drawing Routines\n");
        printf("(2)  Demo #2  The Clipping Capabilities\n");
        printf("(3)  Demo #3  The Fill Routines\n");
        printf("(4)  Demo #4  The Palette Routines\n");
        printf("(5)  Demo #5  The Block Routines\n");
        printf("(6)  Demo #6  The Text Routines\n");
        printf("(7)  Demo #7  The Scrolling and Paging Routines\n");
        printf("(8)  Demo #8  The PCX Routines\n");
        printf("(9)  Demo #9  The Mouse Routines\n");
        printf("(10) Demo #10 The Joystick Routines\n");
        printf("(11) Demo #11 The Two Dimensional Routines\n");
        printf("(12) Demo #12 The Three Dimensional Routines\n");
        printf("(13) The Grand Tour of All Demos\n");
        printf("(14) Use 320x200 in 256 colors\n");
        printf("(15) Use 640x400 in 256 colors\n");
        max = 15;
        if (videomemory > 511) {
            printf("(16) Use 640x480 in 256 colors\n");
            printf("(17) Use 800x600 in 256 colors\n");
            max = 17;
        } 
        if (videomemory > 1023) {
            printf("(18) Use 1024x768 in 256 colors\n");
            max = 18;
        }
        if (videomemory > 2047) {
            printf("(19) Use 1280x1024 in 256 colors\n");
            max = 19;
        }

        printf("\nYour Choice: ");
        for (i=0;i<3;i++) {
            dummy = (char)getch();
            switch (dummy) {
                case 13:
                    if (i == 0)
                        i--;
                    else {
                        buf[i]='\0';
                        i=2;
                    }
                    break;
                case 8:
                    i--;
                    if (i > (-1)) {
                        printf("\b \b");
                        i--;
                    }
                    break;
                default:
                    if ((dummy < '0') || (dummy > '9'))
                        i--;
                    else if (i < 2) {
                        printf("%c",dummy);
                        buf[i] = dummy;
                    } else
                        buf[i] = '\0';

            }
        }
        ky=(int)strtol(buf,&dumptr,10);

        if (ky > max)
            ky = 99;
    
        if((ky > 0) && (ky < 14))
            switch (res) {
                case 1:
                    res320();
                    break;
                case 2:
                    res640l();
                    break;
                case 3:
                    res640();
                    break;
                case 4:
                    res800();
                    break;
                case 5:
                    res1024();
                    break;
                case 6:
                    res1280();
                    break;
            }
        
        switch (ky) {
            case 0:
                endit = 1;
                break;
            case 1:
                doprims();
                break;
            case 2:
                doclip();
                break;
            case 3:
                dofill();
                break;
            case 4:
                dopal();
                break;
            case 5:
                doblock();
                break;
            case 6:
                dotext();
                break;
            case 7:
                doscroll();
                break;
            case 8:
                dopcx();
                break;
            case 9:
                domouse();
                break;
            case 10:
                dojoystick();
                break;
            case 11:
                do2d();
                break;
            case 12:
                do3d();
                break;
            case 13:
                doall();
                break;
            case 14:
                res = 1;
                break;
            case 15:
                res = 2;
                break;
            case 16:
                res = 3;
                break;
            case 17:
                res = 4;
                break;
            case 18:
                res = 5;
                break;
            case 19:
                res = 6;
                break;

            default:
                ;

        }
        
        restext();
        
    }

    videomodeset(startvideomode);

}

/**********               
 * GETKEY *
 **********/

char getkey(void)
{
    char ret;
    beep();
    ret = (char)getch();
    if ( (ret == 'Q') || (ret == 'q') )
        endit = 1;
    if (ret == 'Q')
        ret = 'q';
    if (ret == 'S')
        ret = 's';
    
    return(ret);
}


/*********
 * DOALL *
 *********/

void doall(void)
{
    if(doprims()=='q')
        return;
    if(doclip()=='q')
        return;
    if(dofill()=='q')
        return;
    if(dopal()=='q')
        return;
    if(doblock()=='q')
        return;
    if(dotext()=='q')
        return;
    if(doscroll()=='q')
        return;
    if(dopcx()=='q')
        return;
    if(domouse()=='q')
        return;
    if(dojoystick()=='q')
        return;
    if(do2d()=='q')
        return;
    if(do3d()=='q')
        return;

    return;

}


/***************
 * SCREENCLEAR *
 ***************/

void screenclear(void)
{
    union REGS regs;

    regs.h.ah = 0x07;
    regs.h.al = 0x00;
    regs.h.ch = 0;
    regs.h.cl = 0;
    regs.h.dh = 24;
    regs.h.dl = 79;
    regs.h.bh = 7;
    int86(0x10, &regs, &regs);
    screengoto(1,1);
}


/**************
 * SCREENGOTO *
 **************/

void screengoto(int x, int y)
{
    union REGS regs;

    regs.h.ah = 0x02;
    regs.h.bh = 0;
    regs.h.dh = (unsigned char)y;
    regs.h.dl = (unsigned char)x;
    int86(0x10, &regs, &regs);
}

/********
 * BEEP *
 ********/

void beep(void)
{

    int cont;

    outp(0x43,0xB6);
    outp(0x42,0xA9);
    outp(0x42,0x06);
    cont = inp(0x61);
    outp(0x61,cont | 0x03);
    sdelay(4);
    outp(0x61,cont);

}
  
