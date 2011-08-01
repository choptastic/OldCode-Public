/*      SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */

/* л smix.c v1.30 ллллллллллллллллллллллллллллллллллллллллллллллллллллллллл */

#define TRUE  1
#define FALSE 0

#define ON  1
#define OFF 0

#define BLOCK_LENGTH    256   /* Length of digitized sound output block     */
#define LOAD_CHUNK_SIZE 2048  /* Chunk size used to load sounds from disk   */
#define VOICES          8     /* Number of available simultaneous voices    */
#define SAMPLING_RATE   22050 /* Sampling rate for output                   */

typedef struct
  {
    int xmshandle;
    long startofs;
    long soundsize;
  } SOUND;

int  init_sb(int baseio, int irq, int dma, int dma16);
void shutdown_sb(void);

void set_sampling_rate(unsigned short rate);

void init_mixing(void);
void shutdown_mixing(void);

int  init_xms(void);
unsigned short getfreexms(void);
void init_sharing(void);
void shutdown_sharing(void);

int  open_sound_resource_file(char *filename);
void close_sound_resource_file(void);

int  load_sound(SOUND **sound, char *key);
void free_sound(SOUND **sound);

int  start_sound(SOUND *sound, int index, int loop);
void stop_sound(int index);
int  sound_playing(int index);

volatile long  intcount;       /* Current count of sound interrupts         */
volatile int   voicecount;     /* Number of voices currently in use         */

short dspversion;
int autoinit;
int sixteenbit;
int smix_sound;

/* лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл */

/* Disable 386 code generation - The Borland C compiler generates 386 code, */
/* but doesn't preserve the 32-bit registers for interrupt handlers.  This  */
/* results in corruption of 32-bit registers and can cause problems with    */
/* programs using SMIX or certain TSRs.  By disabling 386 code generation   */
/* for SMIX, this problem is eliminated.                                    */
#pragma option -2

/* Disable stack overflow checking.  The code for detecting stack overflows */
/* assumes that it is working with the program's stack.  SMIX has a number  */
/* of routines called from interrupts, when the system may be using another */
/* stack.  For this reason, the overflow checking will detect an overflow   */
/* when there is none. Disabling checking for SMIX modules eliminates this. */
#pragma option -N-

#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xms.h"

#define BUFFER_LENGTH BLOCK_LENGTH*2

#define BYTE unsigned char

#define lo(value) (unsigned char)((value) & 0x00FF)
#define hi(value) (unsigned char)((value) >> 8)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

static int resetport;
static int readport;
static int writeport;
static int pollport;
static int ackport;

static int pic_rotateport;
static int pic_maskport;

static int dma_maskport;
static int dma_clrptrport;
static int dma_modeport;
static int dma_addrport;
static int dma_countport;
static int dma_pageport;

static int irq_startmask;
static int irq_stopmask;
static int irq_intvector;

static int dma_startmask;
static int dma_stopmask;
static int dma_mode;
static int dma_length;

static int  shared_emb     = FALSE;
static int  shared_handle  = 0;
static long shared_size    = 0;

static void (interrupt far *oldintvector)(void);

static int smix_initialized  = FALSE;
static int handler_installed = FALSE;

static unsigned short sampling_rate = SAMPLING_RATE;


static void write_dsp(BYTE value)
  {
    while ((inp(writeport) & 0x80));
    outp(writeport, value);
  }

static BYTE read_dsp(void)
  {
    while (!(inp(pollport) & 0x80));
    return(inp(readport));
  }

static int reset_dsp(void)
  {
    int i;

    outp(resetport, 1);
    delay(1);                            /* 1 millisecond */
    outp(resetport, 0);

    i = 100;
    while ((i-- > 0) && (read_dsp() != 0xAA));

    return(i > 0);
  }

void install_handler(void);
void uninstall_handler(void);
void smix_exitproc(void);

int init_sb(int baseio, int irq, int dma, int dma16)
  {
   /* Sound card IO ports */
    resetport  = baseio + 0x006;
    readport   = baseio + 0x00A;
    writeport  = baseio + 0x00C;
    pollport   = baseio + 0x00E;

   /* Reset DSP, get version, choose output mode */
    if (!reset_dsp())
      return(FALSE);
    write_dsp(0xE1);  /* Get DSP version number */
    dspversion = read_dsp() << 8;  dspversion += read_dsp();
    autoinit   = (dspversion >= 0x0200);
    sixteenbit = (dspversion >= 0x0400) && (dma16 != 0) && (dma16 > 3);

   /* Compute interrupt controller ports and parameters */
    if (irq < 8)
      { /* PIC1 */
        irq_intvector  = 0x08 + irq;
        pic_rotateport = 0x20;
        pic_maskport   = 0x21;
      }
    else
      { /* PIC2 */
        irq_intvector  = 0x70 + irq-8;
        pic_rotateport = 0xA0;
        pic_maskport   = 0xA1;
      }
    irq_stopmask  = 1 << (irq % 8);
    irq_startmask = ~irq_stopmask;

   /* Compute DMA controller ports and parameters */
    if (sixteenbit)
      { /* Sixteen bit */
        dma_maskport   = 0xD4;
        dma_clrptrport = 0xD8;
        dma_modeport   = 0xD6;
        dma_addrport   = 0xC0 + 4*(dma16-4);
        dma_countport  = 0xC2 + 4*(dma16-4);
        switch (dma16)
          {
            case 5:
              dma_pageport = 0x8B;
              break;
            case 6:
              dma_pageport = 0x89;
              break;
            case 7:
              dma_pageport = 0x8A;
              break;
          }
        dma_stopmask  = dma16-4 + 0x04;  /* 000001xx */
        dma_startmask = dma16-4 + 0x00;  /* 000000xx */
        if (autoinit)
          dma_mode = dma16-4 + 0x58;     /* 010110xx */
        else
          dma_mode = dma16-4 + 0x48;     /* 010010xx */
        ackport = baseio + 0x00F;
      }
    else
      { /* Eight bit */
        dma_maskport   = 0x0A;
        dma_clrptrport = 0x0C;
        dma_modeport   = 0x0B;
        dma_addrport   = 0x00 + 2*dma;
        dma_countport  = 0x01 + 2*dma;
        switch (dma)
          {
            case 0:
              dma_pageport = 0x87;
              break;
            case 1:
              dma_pageport = 0x83;
              break;
            case 2:
              dma_pageport = 0x81;
              break;
            case 3:
              dma_pageport = 0x82;
              break;
          }
        dma_stopmask  = dma + 0x04;      /* 000001xx */
        dma_startmask = dma + 0x00;      /* 000000xx */
        if (autoinit)
          dma_mode    = dma + 0x58;      /* 010110xx */
        else
          dma_mode    = dma + 0x48;      /* 010010xx */
        ackport = baseio + 0x00E;
      }

    if (autoinit)
      dma_length = BUFFER_LENGTH;
    else
      dma_length = BLOCK_LENGTH;

    install_handler();

    smix_initialized = TRUE;
    smix_sound       = FALSE;

    atexit(smix_exitproc);

    return(TRUE);
  }

void shutdown_sb(void)
  {
    if (handler_installed) uninstall_handler();
    reset_dsp();
  }

int init_xms(void)
  {
    xms_init();
    return(xms_installed());
  }

unsigned short getfreexms(void)
  {
    return(xms_getfreemem());
  }

/* Voice control */
typedef struct
  {
    SOUND *sound;
    int   index;
    long  curpos;
    int   loop;
  } VOICE;

static int   inuse[VOICES];
static VOICE voice[VOICES];

/* Sound buffer */

static signed char soundblock[BLOCK_LENGTH+1];   /* Signed 8 bit */
  /* The length of XMS copies using HIMEM.SYS must be a mutiple  */
  /* of two.  If the sound data ends in mid-block, it may not be */
  /* possible to round up without corrupting memory.  Therefore, */
  /* the copy buffer has been extended by one byte to eliminate  */
  /* this problem.                                               */

/* Mixing buffer */

static short int mixingblock[BLOCK_LENGTH];     /* Signed 16 bit */

/* Output buffers */

static void          *outmemarea                  = NULL;
static unsigned char (*out8buf)[2][BLOCK_LENGTH]  = NULL;
static short int     (*out16buf)[2][BLOCK_LENGTH] = NULL;

static int curblock;
static void far *blockptr[2];
static void far *curblockptr;

/* Addressing for auto-initialized transfers (Whole buffer) */
static unsigned long buffer_addr;
static unsigned char buffer_page;
static unsigned int  buffer_ofs;

/* Addressing for single-cycle transfers (One block at a time */
static unsigned long block_addr[2];
static unsigned char block_page[2];
static unsigned int  block_ofs[2];

/* 8-bit clipping */

static unsigned char clip_8_buf[256*VOICES];              /* Clipping array */
static unsigned char far *clip_8 = clip_8_buf + 128*VOICES;
  /* Pointer to center of clipping table */

static char time_constant(int rate)
  {
    return (256 - (1000000L / rate));
  }

static void init_sampling_rate(unsigned short rate)
  {
    if (sixteenbit)
      {
        write_dsp(0x41);        /* Set digitized sound output sampling rate */
        write_dsp(hi(rate));
        write_dsp(lo(rate));
      }
    else
      {
        write_dsp(0x40);        /* Set digitized sound time constant        */
        write_dsp(time_constant(rate));
      }
  }

void set_sampling_rate(unsigned short rate)
  {
    sampling_rate = rate;

    if (smix_sound)
      {
        if (sixteenbit)
          {
            init_sampling_rate(sampling_rate);
            write_dsp(0xD6);    /* Continue 16-bit DMA mode digitized sound */
          }
        else
          {
            write_dsp(0xD0);    /* Pause 8-bit DMA mode digitized sound     */
            init_sampling_rate(sampling_rate);
            write_dsp(0xD4);    /* Continue 8-bit DMA mode digitized sound  */
          }
      }
  }

static void start_dac(void)
  {
    outp(dma_maskport,   dma_stopmask);
    outp(dma_clrptrport, 0x00);
    outp(dma_modeport,   dma_mode);
    outp(dma_addrport,   lo(buffer_ofs));
    outp(dma_addrport,   hi(buffer_ofs));
    outp(dma_countport,  lo(dma_length-1));
    outp(dma_countport,  hi(dma_length-1));
    outp(dma_pageport,   buffer_page);
    outp(dma_maskport,   dma_startmask);

    init_sampling_rate(sampling_rate);

    if (sixteenbit)
      { /* Sixteen bit auto-initialized: SB16 and up (DSP 4.xx)             */
        write_dsp(0xB6);                /* 16-bit cmd  - D/A - A/I - FIFO   */
        write_dsp(0x10);                /* 16-bit mode - signed mono        */
        write_dsp(lo(BLOCK_LENGTH-1));
        write_dsp(hi(BLOCK_LENGTH-1));
      }
    else
      { /* Eight bit */
        write_dsp(0xD1);                /* Turn on speaker                  */

        if (autoinit)
          { /* Eight bit auto-initialized:  SBPro and up (DSP 2.00+)        */
            write_dsp(0x48);            /* Set DSP block transfer size      */
            write_dsp(lo(BLOCK_LENGTH-1));
            write_dsp(hi(BLOCK_LENGTH-1));
            write_dsp(0x1C);            /* 8-bit auto-init DMA mono output  */
          }
        else
          { /* Eight bit single-cycle:  Sound Blaster (DSP 1.xx+)           */
            write_dsp(0x14);            /* 8-bit single-cycle DMA output    */
            write_dsp(lo(BLOCK_LENGTH-1));
            write_dsp(hi(BLOCK_LENGTH-1));
          }
      }

    smix_sound = TRUE;
  }

static void stop_dac(void)
  {
    smix_sound = FALSE;

    if (sixteenbit)
      {
        write_dsp(0xD5);                /* Pause 16-bit DMA sound I/O       */
      }
    else
      {
        write_dsp(0xD0);                /* Pause 8-bit DMA sound I/O        */
        write_dsp(0xD3);                /* Turn off speaker                 */
      }

    outp(dma_maskport, dma_stopmask);
  }


/* Setup for storinng all sounds in one EMB (Saves handles) */

void init_sharing(void)
  {
    shared_emb  = TRUE;
    shared_size = 0;
    xms_allocate(&shared_handle, (unsigned int)shared_size);
  }

void shutdown_sharing(void)
  {
    if (shared_emb) xms_free(&shared_handle);
    shared_emb    = FALSE;
    shared_handle = 0;
    shared_size   = 0;
  }

/* Setup for sound resource files */

static int  resource_file = FALSE;
static char resource_filename[64] = "";

int fexist(char *filename)
  {
    FILE *f;

    f = fopen(filename, "r");

    fclose(f);

    return (f != NULL);
  }

int open_sound_resource_file(char *filename)
  {
    resource_file = TRUE;
    strcpy(resource_filename, filename);

    return fexist(filename);
  }

void close_sound_resource_file(void)
  {
    resource_file = FALSE;
    strcpy(resource_filename, "");
  }


/* Loading and freeing sounds */

static FILE *sound_file;
static long sound_size;

typedef struct
  {
    char key[8];
    long start;
    long size;
  } RESOURCE_HEADER;

void get_sound_file(char *key)
  {
    short numsounds;
    int   found;
    int   i;
    RESOURCE_HEADER res_header;

    found = FALSE;
    sound_size = 0;

    if (resource_file)
      {
        sound_file = fopen(resource_filename, "rb");
        fread(&numsounds, sizeof(numsounds), 1, sound_file);

        for (i = 0; i < numsounds; i++)
          {
            fread(&res_header, sizeof(res_header), 1, sound_file);
            if (!strnicmp(key, res_header.key, 8))
              {
                found = TRUE;
                break;
              }
          }

        if (found)
          {
            fseek(sound_file, res_header.start, SEEK_SET);
            sound_size = res_header.size;
          }
      }
    else
      {
        sound_file = fopen(key, "rb");
        fseek(sound_file, 0, SEEK_END);
        sound_size = ftell(sound_file);
        fseek(sound_file, 0, SEEK_SET);
      }
  }

int load_sound(SOUND **sound, char *key)
  {
    char inbuf[LOAD_CHUNK_SIZE];
    MOVEPARAMS moveparams;
    long remaining;

    get_sound_file(key);

    if (sound_size == 0)
      return FALSE;

    *sound = (SOUND *)malloc(sizeof(SOUND));

    (*sound)->soundsize = sound_size;

    if (!shared_emb)
      {
        (*sound)->startofs = 0;
        if (!xms_allocate(&((*sound)->xmshandle), (unsigned int)((sound_size + 1023) / 1024)))
          return FALSE;
      }
    else
      {
        (*sound)->startofs  = shared_size;
        (*sound)->xmshandle = shared_handle;
        shared_size += sound_size;
        if (!xms_reallocate(shared_handle, (unsigned int)((shared_size + 1023) / 1024)))
          return FALSE;
      }

    remaining = (*sound)->soundsize;

    moveparams.sourcehandle = 0;
    moveparams.sourceoffset = (long)(&inbuf);
    moveparams.desthandle   = (*sound)->xmshandle;
    moveparams.destoffset   = (*sound)->startofs;

    do
      {
        moveparams.length = fread(&inbuf, 1, (size_t)MIN(remaining, sizeof(inbuf)), sound_file);
        moveparams.length = ((moveparams.length+1) / 2) * 2;
          /* XMS copy lengths must be a multiple of two */
        if (!xms_move(&moveparams))
          return FALSE;
        moveparams.destoffset += moveparams.length;
        remaining             -= moveparams.length;
      }
    while (remaining > 0);

    fclose(sound_file);

    return TRUE;
  }

void free_sound(SOUND **sound)
  {
    if (!shared_emb) xms_free(&((*sound)->xmshandle));
    free(*sound);
    *sound = NULL;
  }

/* Voice maintainance */

static void deallocate_voice(int voicenum)
  {
    inuse[voicenum] = FALSE;
    voice[voicenum].sound  = NULL;
    voice[voicenum].index  = -1;
    voice[voicenum].curpos = 0;
    voice[voicenum].loop   = 0;
  }

int start_sound(SOUND *sound, int index, int loop)
  {
    int i, slot;
    slot = -1; i = 0;
    do
      {
        if (!inuse[i])
          slot = i;
        i++;
      }
    while ((slot == -1) && (i < VOICES));
    if (slot != -1)
      {
        voice[slot].sound  = sound;
        voice[slot].index  = index;
        voice[slot].curpos = 0;
        voice[slot].loop   = loop;

        ++voicecount;
        inuse[slot] = TRUE;

      }

    return (slot != -1);
  }

void stop_sound(int index)
  {
    int i;
    for (i=0; i < VOICES; i++)
      if (voice[i].index == index)
        {
          deallocate_voice(i);
          --voicecount;
        }
  }

int  sound_playing(int index)
  {
    int i;

   /* Search for a sound with the specified index */
    for (i=0; i < VOICES; i++)
      if (voice[i].index == index)
        return(TRUE);

   /* Sound not found */
    return(FALSE);
  }

static void update_voices(void)
  {
    int voicenum;

    for (voicenum=0; voicenum < VOICES; voicenum++)
      {
        if (inuse[voicenum])
          {
            if (voice[voicenum].curpos >= voice[voicenum].sound->soundsize)
              {
                deallocate_voice(voicenum);
                --voicecount;
              }
          }
      }
  }

/* Utility functions */

static void setcurblock(int blocknum)
  {
    curblockptr = blockptr[(curblock = blocknum)];
  }

static void silenceblock(void)
  {
    _fmemset(&mixingblock, 0x00, BLOCK_LENGTH * sizeof(short int));
  }

static long getlinearaddr(void far *ptr)
  {
    return((long)FP_SEG(ptr)*16 + (long)FP_OFF(ptr));
  }

/* Mixing initialization */

static void init_clip8(void)
  {
    int i;
    int value;

    for (i = -128*VOICES; i < 128*VOICES; i++)
      {
        value = i;
        value = MAX(value, -128);
        value = MIN(value, 127);

        clip_8[i] = value + 128;
      }
  }

void init_mixing(void)
  {
    int i;

    for (i=0; i < VOICES; i++)
      deallocate_voice(i);
    voicecount = 0;

    if (sixteenbit)
      {
       /* Find a block of memory that does not cross a page boundary */
        out16buf = outmemarea = malloc(4*BUFFER_LENGTH);

        if ((((getlinearaddr(outmemarea) >> 1) % 65536L) + BUFFER_LENGTH) > 65536L)
          out16buf += 1;  /* Choose second half of memory area */
        for (i=0; i<2; i++) blockptr[i] = &((*out16buf)[i]);

       /* DMA parameters */
        buffer_addr = getlinearaddr(out16buf);
        buffer_page = buffer_addr >> 16;
        buffer_ofs  = (unsigned int)((buffer_addr >> 1) % 65536L);

        _fmemset((void *)out16buf, 0x00, BUFFER_LENGTH*2);
      }
    else
      {
       /* Find a block of memory that does not cross a page boundary */
        out8buf = outmemarea = malloc(2*BUFFER_LENGTH);
        if (((getlinearaddr(outmemarea) % 65536L) + BUFFER_LENGTH) > 65536L)
          out8buf += 1;  /* Choose second half of memory area */
        for (i=0; i<2; i++) blockptr[i] = &((*out8buf)[i]);

       /* DMA parameters */
        buffer_addr = getlinearaddr(out8buf);
        buffer_page = buffer_addr / 65536L;
        buffer_ofs  = (unsigned int)(buffer_addr % 65536L);
        for (i=0; i<2; i++)
          {
            block_addr[i] = getlinearaddr(blockptr[i]);
            block_page[i] = block_addr[i] / 65536L;
            block_ofs[i]  = (unsigned int)(block_addr[i] % 65536L);
          }
        _fmemset((void *)out8buf, 0x80, BUFFER_LENGTH);

        init_clip8();
      }

    silenceblock();
    setcurblock(0);
    intcount = 0;
    start_dac();
  }

void shutdown_mixing(void)
  {
    stop_dac();

    free((void *)outmemarea);
  }

static void copy_sound(SOUND *sound, long *curpos, int copylength, int loop)
  {
    long soundsize;
    char far *destptr;
    MOVEPARAMS moveparams;

    soundsize = sound->soundsize;
    destptr   = (char far *)(&soundblock);
    moveparams.sourcehandle = sound->xmshandle;
    moveparams.desthandle   = 0;

    do
      {
       /* Compute transfer size */
        moveparams.length = MIN(copylength, soundsize - (*curpos));

       /* Compute starting source offset and update offset for next block */
        moveparams.sourceoffset = sound->startofs + (*curpos);
        (*curpos) += moveparams.length;
        if (loop)
          (*curpos) %= soundsize;

       /* Compute starting dest offset and update offset for next block */
        moveparams.destoffset = (long)destptr;
        destptr += (int)moveparams.length;

       /* Update remaining count for next iteration (If any) */
        copylength -= (int)moveparams.length;

       /* Copy block down from extended memory */
        moveparams.length = ((moveparams.length + 1) / 2) * 2;
          /* XMS copy lengths must be a multiple of two */
        xms_move(&moveparams);  /* Luckily, the XMS driver is re-entrant */
      }
    while (copylength > 0);
  }

static void mix_voice(VOICE *voice)
  {
    int mixlength;

    if (voice->loop)
      mixlength = BLOCK_LENGTH;
    else
      mixlength = (int)MIN(BLOCK_LENGTH, voice->sound->soundsize - voice->curpos);
    copy_sound(voice->sound, &(voice->curpos), mixlength, voice->loop);

    asm  lea  si, soundblock          /* DS:SI -> Sound data (source)       */
    asm  mov  ax, ds                  /* ES:DI -> Mixing block (dest)       */
    asm  mov  es, ax
    asm  lea  di, mixingblock
    asm  mov  cx, mixlength           /* CX = Number of samples to copy     */
   mix_sample:
    asm  mov  al, [si]                /* Load a sample from the sound block */
    asm  inc  si                      /* Increment source pointer (+1)      */
    asm  cbw                          /* Convert to a 16-bit signed sample  */
    asm  add  es:[di], ax             /* Add it into the mixing buffer      */
    asm  add  di, 2                   /* Increment destination pointer (+2) */
    asm  dec  cx                      /* Loop for next sample               */
    asm  jnz  mix_sample
  }

static void mix_voices(void)
  {
    int i;

    silenceblock();
    for (i=0; i < VOICES; i++)
      if (inuse[i]) mix_voice(&(voice[i]));
  }

static void copy_sound16(void)
  {
    asm  lea  si, mixingblock         /* DS:SI -> 16-bit input block        */
    asm  les  di, [curblockptr]       /* ES:DI -> 16-bit output block       */
    asm  mov  cx, BLOCK_LENGTH        /* CX = Number of samples to copy     */
   copy_sample:
    asm  mov  ax, [si]                /* Load sample from the mixing block  */
    asm  add  di, 2                   /* Increment destination pointer      */
    asm  sal  ax, 5                   /* Shift samples to fill 16-bit range */
    asm  add  si, 2                   /* Increment source pointer           */
    asm  mov  es:[di-2], ax           /* Store sample in output block       */
    asm  dec  cx                      /* Loop for next sample               */
    asm  jnz  copy_sample
  }

static void copy_sound8(void)
  {
    asm  push bp
    asm  mov  dx, ss                  /* Preserve SS in DX                  */
    asm  pushf
    asm  cli                          /* Disable interrupts                 */
    asm  mov  ax,  ds                 /* Using stack register for data      */
    asm  mov  ss,  ax

    asm  lds  si, [clip_8]            /* DS:SI -> 8-bit clipping buffer     */

    asm  lea  bp, mixingblock         /* SS:BP -> 16-bit input block        */
    asm  les  di, [curblockptr]       /* ES:DI -> 8-bit output block        */
    asm  mov  cx, BLOCK_LENGTH        /* CX = Number of samples to copy     */

   copy_sample:
    asm  mov  bx, [bp]                /* BX = Sample from mixing block      */
    asm  inc  di                      /* Increment destination pointer (+1) */
    asm  add  bp, 2                   /* Increment source pointer (+2)      */
    asm  mov  al, [si+bx]             /* AL = Clipped sample                */
    asm  mov  es:[di-1], al           /* Store sample in output block       */
    asm  dec  cx                      /* Loop for next sample               */
    asm  jnz  copy_sample

    asm  mov  ss, dx
    asm  popf
    asm  pop  bp
  }

static void copydata(void)
  {
    if (sixteenbit)
      copy_sound16();
    else
      copy_sound8();
  }

static void startblock_sc(void) /* Starts a single-cycle DMA transfer */
  {
    outp(dma_maskport,   dma_stopmask);
    outp(dma_clrptrport, 0x00);
    outp(dma_modeport,   dma_mode);
    outp(dma_addrport,   lo(block_ofs[curblock]));
    outp(dma_addrport,   hi(block_ofs[curblock]));
    outp(dma_countport,  lo(BLOCK_LENGTH-1));
    outp(dma_countport,  hi(BLOCK_LENGTH-1));
    outp(dma_pageport,   block_page[curblock]);
    outp(dma_maskport,   dma_startmask);
    write_dsp(0x14);                /* 8-bit single-cycle DMA sound output  */
    write_dsp(lo(BLOCK_LENGTH-1));
    write_dsp(hi(BLOCK_LENGTH-1));
  }

static void interrupt inthandler(void)
  {
    intcount++;

    if (!autoinit)     /* Start next block first if not using auto-init DMA */
      {
        startblock_sc();
        copydata();
        setcurblock(!curblock);    /* Toggle block */
      }

    update_voices();
    mix_voices();

    if (autoinit)
      {
        copydata();
        setcurblock(!curblock);    /* Toggle block */
      }

    inp(ackport);                  /* Acknowledge interrupt with sound card */
    outp(0xA0, 0x20);              /* Acknowledge interrupt with PIC2       */
    outp(0x20, 0x20);              /* Acknowledge interrupt with PIC1       */
  }

static void install_handler(void)
  {
    disable();
    outp(pic_maskport, (inp(pic_maskport) | irq_stopmask));

    oldintvector = _dos_getvect(irq_intvector);
    _dos_setvect(irq_intvector, inthandler);

    outp(pic_maskport, (inp(pic_maskport) & irq_startmask));
    enable();

    handler_installed = TRUE;
  }

static void uninstall_handler(void)
  {
      disable();
      outp(pic_maskport, (inp(pic_maskport) | irq_stopmask));

      _dos_setvect(irq_intvector, oldintvector);

      enable();

      handler_installed = FALSE;
  }

static void smix_exitproc(void)
  {
    if (smix_initialized)
      {
        stop_dac();
        shutdown_sb();
      }
  }
