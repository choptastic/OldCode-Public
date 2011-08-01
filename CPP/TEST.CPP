#include <stdlib.h>
            #include <conio.h>
            #include <math.h>
            #include "svgacc.h"

            void main(void)
            {
               int i,y,ya,yb,ofst,coloroffset,intsbits,numlevels,dummy;
               PaletteData pal;
               if ( !whichvga() )
                    exit(1);
                if ( whichmem() < 512)
                 exit(1);
                if ( !res640() )
                 exit(1);
               /* set up the palette */
               intsbits=2;
               numlevels=pow(2,intsbits);
               coloroffset=16;
               palget(pal,0,255);
               for (i=0;i<numlevels;i++) {
                 pal[i+coloroffset].r = (char)(63-35*i/(numlevels-1));
                 pal[i+coloroffset].g = (char)(63-35*i/(numlevels-1));
                 pal[i+coloroffset].b = (char)(63-35*i/(numlevels-1));
               }
               palset(pal,0,255);
               ofst=maxy/2;
               ya=maxy/3;
               yb=2*maxy/3;
               for(y=0;y<ofst;y=y+12) {
                 drwline(SET,15,0,ya,maxx,y);
                 drwaline(intsbits,16,0,yb,maxx,ofst+y);
               }
               getch();
               dummy=restext();
               exit(0);
            }
