#ifndef __MIDIPROG__
#define __MIDIPROG__

enum MidiMode { MODE_GM, MODE_GS, MODE_XG };

typedef struct
{
  char program;
  char bank;
  const char* patchname;
} MIDIPATCH; 

#define GMPROGRAMS 128
extern const char* gmprogname[GMPROGRAMS];

extern const char* gmdrumname;

#define XGPROGRAMS  455
extern MIDIPATCH xgprogname[XGPROGRAMS]; // bank is lbank, hbank=0!

#define XGDRUMS 61
extern MIDIPATCH xgdrumname[XGDRUMS]; // bank is hbank, lbank=0!

#define GSPROGRAMS 448
extern MIDIPATCH gsprogname[GSPROGRAMS];  // bank is lbank, hbank=0!

#define GSDRUMS 10
extern MIDIPATCH gsdrumname[GSDRUMS]; // channel = 10

#define MT32PROGRAMS 128
extern const char* mt32progname[MT32PROGRAMS];

const char* findpatch(MIDIPATCH* table, int count, int bank, int prog);

const char* gmpatch(int channel, int hbank, int lbank, int prog);
const char* gspatch(int channel, int hbank, int lbank, int prog);
const char* xgpatch(int channel, int hbank, int lbank, int prog);

const char* patch(int channel, int hbank, int lbank, int prog, MidiMode = MODE_GM);

#endif

