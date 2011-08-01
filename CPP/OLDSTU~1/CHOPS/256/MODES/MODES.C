/**************************************************************************
 * modes.c                                                                *
 * written by David Brackeen                                              *
 * brackeen@silo.csci.unt.edu                                             *
 * http://silo.csci.unt.edu/home/brackeen/vga/                            *
 *                                                                        *
 * This is a 16-bit program.                                              *
 * Tab stops are set to 2.                                                *
 * Remember to compile in the LARGE memory model!                         *
 *                                                                        *
 * This DOS program will only work on DOS- or Windows-based systems with  *
 * a VGA, SuperVGA, or compatible video adapter.                          *
 *                                                                        *
 * Please feel free to copy this source code.                             *
 *                                                                        *
 * DESCRIPTION: This program demonstrates various unchained modes         *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */


#define MISC_OUTPUT         0x03c2    /* VGA misc. output register */
#define SC_INDEX            0x03c4    /* VGA sequence controller */
#define SC_DATA             0x03c5
#define PALETTE_INDEX       0x03c8    /* VGA digital-to-analog converter */
#define PALETTE_DATA        0x03c9
#define CRTC_INDEX          0x03d4    /* VGA CRT controller */

#define MAP_MASK            0x02      /* Sequence controller registers */
#define MEMORY_MODE         0x04

#define H_TOTAL             0x00      /* CRT controller registers */
#define H_DISPLAY_END       0x01
#define H_BLANK_START       0x02
#define H_BLANK_END         0x03
#define H_RETRACE_START     0x04
#define H_RETRACE_END       0x05
#define V_TOTAL             0x06
#define OVERFLOW            0x07
#define MAX_SCAN_LINE       0x09
#define V_RETRACE_START     0x10
#define V_RETRACE_END       0x11
#define V_DISPLAY_END       0x12
#define OFFSET              0x13
#define UNDERLINE_LOCATION  0x14
#define V_BLANK_START       0x15
#define V_BLANK_END         0x16
#define MODE_CONTROL        0x17

#define NUM_COLORS          256       /* number of colors in mode 0x13 */

/* macro to skip bytes in a file */
#define fskip(fp,n)   \
{                     \
   int i;             \
                      \
   for (i=0;i<n;i++)  \
      fgetc(fp);      \
}

/* macro to return the sign of a number */
#define sgn(x) \
  ((x<0)?-1:((x>0)?1:0))

/* macro to write a word to a port */
#define word_out(port,register,value) \
  outpw(port,(((word)value<<8) + register))

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

/* the structure for a planar bitmap. */
typedef struct tagPLANAR_BITMAP
{
  word width;
  word height;
  byte palette[256*3];
  byte *data[4];
} PLANAR_BITMAP;

byte *VGA=(byte *)0xA0000000L;        /* this points to video memory. */
word screen_width, screen_height;

/**************************************************************************
 *  set_mode                                                              *
 *     Sets the video mode.                                               *
 **************************************************************************/

void set_mode(byte mode)
{
  union REGS regs;

  regs.h.ah = SET_MODE;
  regs.h.al = mode;
  int86(VIDEO_INT, &regs, &regs);
}

/**************************************************************************
 *  set_unchained_mode                                                    *
 *    Resets VGA mode 0x13 to unchained mode to access all 256K of        *
 *    memory.  width may be 320 or 360, height may be 200, 400, 240 or    *
 *    480.  If an invalid width or height is specified, it defaults to    *
 *    320x200                                                             *
 **************************************************************************/

void set_unchained_mode(int width, int height)
{
  word i;
  dword *ptr=(dword *)VGA;

  /* set mode 13 */
  set_mode(VGA_256_COLOR_MODE);

  /* turn off chain-4 mode */
  word_out(SC_INDEX, MEMORY_MODE,0x06);

  /* set map mask to all 4 planes for screen clearing */
  word_out(SC_INDEX, MAP_MASK, 0xff);

  /* clear all 256K of memory */
  for(i=0;i<0x4000;i++)
    *ptr++ = 0;

  /* turn off long mode */
  word_out(CRTC_INDEX, UNDERLINE_LOCATION, 0x00);

  /* turn on byte mode */
  word_out(CRTC_INDEX, MODE_CONTROL, 0xe3);


  screen_width=320;
  screen_height=200;

  if (width==360)
  {
    /* turn off write protect */
    word_out(CRTC_INDEX, V_RETRACE_END, 0x2c);

    outp(MISC_OUTPUT, 0xe7);
    word_out(CRTC_INDEX, H_TOTAL, 0x6b);
    word_out(CRTC_INDEX, H_DISPLAY_END, 0x59);
    word_out(CRTC_INDEX, H_BLANK_START, 0x5a);
    word_out(CRTC_INDEX, H_BLANK_END, 0x8e);
    word_out(CRTC_INDEX, H_RETRACE_START, 0x5e);
    word_out(CRTC_INDEX, H_RETRACE_END, 0x8a);
    word_out(CRTC_INDEX, OFFSET, 0x2d);

    /* set vertical retrace back to normal */
    word_out(CRTC_INDEX, V_RETRACE_END, 0x8e);

    screen_width=360;
  }
  else
  {
    outp(MISC_OUTPUT, 0xe3);
  }

  if (height==240 || height==480)
  {
    /* turn off write protect */
    word_out(CRTC_INDEX, V_RETRACE_END, 0x2c);

    word_out(CRTC_INDEX, V_TOTAL, 0x0d);
    word_out(CRTC_INDEX, OVERFLOW, 0x3e);
    word_out(CRTC_INDEX, V_RETRACE_START, 0xea);
    word_out(CRTC_INDEX, V_RETRACE_END, 0xac);
    word_out(CRTC_INDEX, V_DISPLAY_END, 0xdf);
    word_out(CRTC_INDEX, V_BLANK_START, 0xe7);
    word_out(CRTC_INDEX, V_BLANK_END, 0x06);
    screen_height=height;
  }

  if (height==400 || height==480)
  {
    word_out(CRTC_INDEX, MAX_SCAN_LINE, 0x40);
    screen_height=height;
  }



}

/**************************************************************************
 *  draw_bitmap                                                           *
 *    Draws a bitmap. Bitmaps are stored in a four-plane format to ease   *
 *    the drawing process (the plane is changed only four times)          *
 **************************************************************************/

void draw_bitmap(PLANAR_BITMAP *bmp,int x,int y)
{
  int j,plane;
  word screen_offset;
  word bitmap_offset;

  for(plane=0; plane<4; plane++)
  {
    outp(SC_INDEX, MAP_MASK);          /* select plane */
    outp(SC_DATA,  1 << ((plane+x)&3) );
    bitmap_offset=0;
    screen_offset = ((dword)y*screen_width+x+plane) >> 2;
    for(j=0; j<bmp->height; j++)
    {
      memcpy(&VGA[screen_offset], &bmp->data[plane][bitmap_offset], (bmp->width >> 2));

      bitmap_offset+=bmp->width>>2;
      screen_offset+=screen_width>>2;
    }
  }
}

/**************************************************************************
 *  load_bmp                                                              *
 *    Loads a bitmap file into memory. Only works for bitmaps whose width *
 *    is divible by 4!                                                    *
 **************************************************************************/

void load_bmp(char *file,PLANAR_BITMAP *b)
{
  FILE *fp;
  long index,size;
  int x,num_colors,plane;

  /* open the file */
  if ((fp = fopen(file,"rb")) == NULL)
  {
    printf("Error opening file %s.\n",file);
    exit(1);
  }

  /* check to see if it is a valid bitmap file */
  if (fgetc(fp)!='B' || fgetc(fp)!='M')
  {
    fclose(fp);
    printf("%s is not a bitmap file.\n",file);
    exit(1);
  }

  /* read in the width and height of the image, and the
     number of colors used; ignore the rest */
  fskip(fp,16);
  fread(&b->width, sizeof(word), 1, fp);
  fskip(fp,2);
  fread(&b->height,sizeof(word), 1, fp);
  fskip(fp,22);
  fread(&num_colors,sizeof(word), 1, fp);
  fskip(fp,6);

  /* assume we are working with an 8-bit file */
  if (num_colors==0) num_colors=256;

  size=b->width*b->height;

  /* try to allocate memory */
  for(plane=0;plane<4;plane++)
  {
    if ((b->data[plane] = (byte *) malloc((word)(size>>2))) == NULL)
    {
      fclose(fp);
      printf("Error allocating memory for file %s.\n",file);
      exit(1);
    }
  }

  /* read the palette information */
  for(index=0;index<num_colors;index++)
  {
    b->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
    b->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
    b->palette[(int)(index*3+0)] = fgetc(fp) >> 2;
    x=fgetc(fp);
  }

  /* read the bitmap */
  for(index = (b->height-1)*b->width; index >= 0;index-=b->width)
    for(x = 0; x < b->width; x++)
      b->data[x&3][(int)((index+x)>>2)]=(byte)fgetc(fp);

  fclose(fp);
}

/**************************************************************************
 *  set_palette                                                           *
 *    Sets all 256 colors of the palette.                                 *
 **************************************************************************/

void set_palette(byte *palette)
{
  int i;

  outp(PALETTE_INDEX,0);              /* tell the VGA that palette data
                                         is coming. */
  for(i=0;i<256*3;i++)
    outp(PALETTE_DATA,palette[i]);    /* write the data */
}

/**************************************************************************
 *  plot_pixel                                                            *
 *    Plots a pixel in unchained mode                                     *
 **************************************************************************/

void plot_pixel(int x,int y,byte color)
{
  dword offset;

  outp(SC_INDEX, MAP_MASK);          /* select plane */
  outp(SC_DATA,  1 << (x&3) );

  offset=((dword)y*screen_width+x) >> 2;

  VGA[(word)offset]=color;
}

/**************************************************************************
 *  Main                                                                  *
 **************************************************************************/

void main(void)
{
  int x,y,plane,choice=1;
  int x_size[2]={320,360};
  int y_size[4]={200,240,400,480};
  PLANAR_BITMAP bmp;

  /* load the images */
  load_bmp("ghosts.bmp",&bmp);

  while (choice!=8)
  {
    /* present menu */
    printf("Select a mode to test\n\n");
    printf("0. 320x200\n");
    printf("1. 320x240\n");
    printf("2. 320x400\n");
    printf("3. 320x480\n");
    printf("4. 360x200\n");
    printf("5. 360x240\n");
    printf("6. 360x400\n");
    printf("7. 360x480\n");
    printf("8. Quit\n\n");
    printf("Your choice? ");

    /* get input */
    scanf("%i",&choice);
    fflush(stdin);

    if (choice!=8)
    {
      set_unchained_mode(x_size[(choice&4)>>2],y_size[choice&3]);
      set_palette(bmp.palette);

      /* tile the images */
      for(x=0;x<=screen_width-bmp.width;x+=bmp.width)
        for(y=0;y<=screen_height-bmp.height;y+=bmp.height)
          draw_bitmap(&bmp,x,y);

      /* use getchar(); here if your compiler doesn't have getch(); */
      getch();

      set_mode(TEXT_MODE);
    }
  }

  for(plane=0;plane<4;plane++)
    free(bmp.data[plane]);


  return;
}

