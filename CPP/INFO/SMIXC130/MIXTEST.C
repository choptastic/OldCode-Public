/*      SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */

/* лл MIXTEST.C ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "detect.h"
#include "smix.h"

#define ON  1
#define OFF 0

#define TRUE  1
#define FALSE 0

#define XMSREQUIRED 200 /* k */
#define SHAREDEMB    /* Undefine this to store all sounds in separate EMBs */
#define NUMSOUNDS 6  /* Change this if you want to add more sounds         */

char *resource_file = "mixtest.snd";

char *sound_key[NUMSOUNDS] =
  {
    "JET",
    "GUN",
    "CRASH",
    "CANNON",
    "LASER",
    "GLASS"
  };

int baseio, irq, dma, dma16;

SOUND *sound[NUMSOUNDS];

void ourexitproc(void)
  {
    int i;

    for (i=0; i < NUMSOUNDS; ++i)
      if (sound[i] != NULL)
        free_sound(sound+i);

#ifdef SHAREDEMB
    shutdown_sharing();
#endif
  }

void loadsounds(void)
  {
    int i;

    if (!init_xms())
      {
        printf("ERROR:  Can not initialize extended memory\n");
        printf("HIMEM.SYS must be installed\n");
        exit(EXIT_FAILURE);
      }

    printf("Extended memory successfully initialized\n");
    printf("Free XMS memory: %uk    ", getfreexms());
    if (getfreexms() < XMSREQUIRED)
      {
        printf("ERROR:  Insufficient free XMS\n");
        exit(EXIT_FAILURE);
      }

    printf("Loading sounds\n");
#ifdef SHAREDEMB
    init_sharing();
#endif
    if (!open_sound_resource_file(resource_file))
      {
        printf("ERROR:  Can't load sound resource file\n");
        exit(EXIT_FAILURE);
      }

    for (i=0; i < NUMSOUNDS; i++)
      load_sound(&(sound[i]), sound_key[i]);

    close_sound_resource_file();

    atexit(ourexitproc);
  }

void freesounds(void)
  {
    int i;

    for (i=0; i < NUMSOUNDS; i++)
      free_sound(sound+i);
#ifdef SHAREDEMB
    shutdown_sharing();
#endif
  }

void init(void)
  {
    printf("-------------------------------------------\n");
    printf("Sound Mixing Library v1.30 by Ethan Brodsky\n");
    if (!detect_settings(&baseio, &irq, &dma, &dma16))
      {
        printf("ERROR:  Invalid or non-existant BLASTER environment variable!\n");
        exit(EXIT_FAILURE);
      }
    else
      {
        if (!init_sb(baseio, irq, dma, dma16))
          {
            printf("ERROR:  Error initializing sound card!\n");
            exit(EXIT_FAILURE);
          }
      }

    printf("BaseIO=%Xh     IRQ%u     DMA8=%u     DMA16=%u\n", baseio, irq, dma, dma16);

    printf("DSP version %.1u.%.2u:  ", dspversion>>8, dspversion&0xFF);
    if (sixteenbit)
      printf("16-bit, ");
    else
      printf("8-bit, ");
    if (autoinit)
      printf("Auto-initialized\n");
    else
      printf("Single-cycle\n");

    init_mixing();
    printf("\n");
  }

void shutdown(void)
  {
    shutdown_mixing();
    shutdown_sb();

    printf("\n");
  }

int main(void)
  {
    int  jet            = 0;
    int  randsound      = 1;
    unsigned short rate = 22000;

    long counter;
    char inkey;
    int  num;
    int  stop;

    randomize();

   /* Initialize SMIX */
    init();

    loadsounds();

    printf("Press:\n");
    printf("  J  Toggle jet engine\n");
    printf("  R  Toggle random sounds\n");
    printf("  1  Machine Gun\n");
    printf("  2  Crash\n");
    printf("  3  Cannon\n");
    printf("  4  Laser\n");
    printf("  5  Breaking glass\n");
    printf("  <  Reduce sampling rate\n");
    printf("  >  Increase sampling rate\n");
    printf("  Q  Quit\n");

    stop = FALSE;
    counter = 0;

    do
      {
       /* Increment and display counters */
        counter++;
        cprintf("%8lu %8lu %4u %8u", counter, intcount, voicecount, rate);
        gotoxy(1, wherey());

       /* Maybe start a random sound */
        if (randsound && (random(10000) == 0))
          {
           num = (random(NUMSOUNDS-1))+1;
           start_sound(sound[num], num, OFF);
          }

       /* Start a sound if a key is pressed */
        if (kbhit())
          {
            inkey = getch();

            if ((inkey == 'J') || (inkey == 'j'))
             /* Jet engine */
              {
                jet = !jet;
                if (jet)
                  start_sound(sound[0], 0, ON);
                else
                  stop_sound(0);
              }
            else if ((inkey == 'R') || (inkey == 'r'))
             /* Toggle random sounds */
              randsound = !randsound;
            else if ((inkey >= '0') && (inkey <= '9'))
             /* Start a sound */
              {
                num = inkey - '0'; /* Convert to integer */
                if (num < NUMSOUNDS)
                  start_sound(sound[num], num, FALSE);
              }
            else if ((inkey == '<') || (inkey == ','))
             /* Reduce sampling rate */
              {
                rate -= 250;
                if (rate < 5000)
                  rate = 5000;
                set_sampling_rate(rate);
              }
            else if ((inkey == '>') || (inkey == '.'))
             /* Increase sampling rate */
              {
                rate += 250;
                if (rate > 48000U)
                  rate = 48000U;
                set_sampling_rate(rate);
              }
            else
             /* Terminate */
              stop = TRUE;
          }
      }
    while (!stop);

    printf("\n");

   /* Stop the jet engine */
    if (jet)
      stop_sound(0);

   /* Shut down SMIX */
    shutdown();

   /* Deallocate sounds */
    freesounds();

    return(EXIT_SUCCESS);
   }
