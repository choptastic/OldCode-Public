/**************************************************************************
 * palette.c                                                              *
 * written by David Brackeen                                              *
 * brackeen@silo.csci.unt.edu                                             *
 * http://silo.csci.unt.edu/home/brackeen/vga/                            *
 *                                                                        *
 * This is a 16-bit program.                                              *
 * Tab stops are set to 2.                                                *
 * Remember to compile in the LARGE memory model!                         *
 *                                                                        *
 * This program will only work on DOS- or Windows-based systems with a    *
 * VGA, SuperVGA or compatible video adapter.                             *
 *                                                                        *
 * Please feel free to copy this source code.                             *
 *                                                                        *
 * DESCRIPTION: This program demostrates palette manipulation and         *
 * vertical retrace sychronization.                                       *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */

#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9
#define INPUT_STATUS        0x03da
#define VRETRACE            0x08

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */

/* macro to skip bytes in a file */
#define fskip(fp,n)   \
{                     \
   int i;             \
                      \
   for (i=0;i<n;i++)  \
      fgetc(fp);      \
}

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

byte *VGA=(byte *)0xA0000000L;        /* this points to video memory. */
word *my_clock=(word *)0x0000046C;    /* this points to the 18.2hz system
                                         clock. */

typedef struct tagBITMAP              /* the structure for a bitmap. */
{
  word width;
  word height;
  byte palette[256*3];
  byte *data;
} BITMAP;


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
 *  load_bmp                                                              *
 *    Loads a bitmap file into memory.                                    *
 **************************************************************************/

void load_bmp(char *file,BITMAP *b)
{
  FILE *fp;
  long index;
  int x,num_colors;

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


  /* try to allocate memory */
  if ((b->data = (byte *) malloc((word)(b->width*b->height))) == NULL)
  {
    fclose(fp);
    printf("Error allocating memory for file %s.\n",file);
    exit(1);
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
  for(index=(b->height-1)*b->width;index>=0;index-=b->width)
    for(x=0;x<b->width;x++)
      b->data[(word)(index+x)]=(byte)fgetc(fp);

  fclose(fp);
}

/**************************************************************************
 *  draw_bitmap                                                           *
 *    Draws a bitmap.                                                     *
 **************************************************************************/

void draw_bitmap(BITMAP *bmp,int x,int y)
{
  int j;
  word screen_offset = (y<<8)+(y<<6)+x;
  word bitmap_offset = 0;

  for(j=0;j<bmp->height;j++)
  {
    memcpy(&VGA[screen_offset],&bmp->data[bitmap_offset],bmp->width);

    bitmap_offset+=bmp->width;
    screen_offset+=SCREEN_WIDTH;
  }
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
 *  rotate_palette                                                        *
 *    Rotates the colors of the palette.                                  *
 **************************************************************************/

void rotate_palette(byte *palette)
{
  int i,red,green,blue;

  red  = palette[3];
  green= palette[4];
  blue = palette[5];

  for(i=3;i<256*3-3;i++)
    palette[i]=palette[i+3];

  palette[256*3-3]=red;
  palette[256*3-2]=green;
  palette[256*3-1]=blue;

  set_palette(palette);
}

/**************************************************************************
 *  wait_for_retrace                                                      *
 *    Wait until the *beginning* of a vertical retrace cycle (60hz).      *
 **************************************************************************/

void wait_for_retrace(void)
{
    /* wait until done with vertical retrace */
    while  ((inp(INPUT_STATUS) & VRETRACE)) {};
    /* wait until done refreshing */
    while (!(inp(INPUT_STATUS) & VRETRACE)) {};
}

/**************************************************************************
 *  wait                                                                  *
 *    Wait for a specified number of clock ticks (18hz).                  *
 **************************************************************************/

void wait(int ticks)
{
  word start;

  start=*my_clock;

  while (*my_clock-start<ticks)
  {
    *my_clock=*my_clock;              /* this line is for some compilers
                                         that would otherwise ignore this
                                         loop */
  }
}

/**************************************************************************
 *  Main                                                                  *
 *    Draws a bitmap and then rotates the palette.                        *
 **************************************************************************/

void main()
{
  BITMAP bmp;
  int i;

  load_bmp("mset.bmp",&bmp);          /* open the file */

  set_mode(VGA_256_COLOR_MODE);       /* set the video mode. */

  set_palette(bmp.palette);           /* set the palette */

  draw_bitmap(&bmp,                   /* draw the bitmap centered */
    (SCREEN_WIDTH-bmp.width) >>1,
    (SCREEN_HEIGHT-bmp.height) >>1);

  wait(25);

  for(i=0;i<510;i++)                  /* rotate the palette at 30hz */
  {
    wait_for_retrace();
    wait_for_retrace();
    rotate_palette(bmp.palette);
  }

  wait(25);

  free(bmp.data);                     /* free up memory used */

  set_mode(TEXT_MODE);                /* set the video mode back to
                                         text mode. */

  return;
}

