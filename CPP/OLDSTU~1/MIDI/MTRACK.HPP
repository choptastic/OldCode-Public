#ifndef __MIDI_TRACKS__
#define __MIDI_TRACKS__

#include "midiio.hpp"
#include "progname.h"

class Trackinfo
{
public:
  Trackinfo();
  ~Trackinfo();

  int channel_; // 0-15 or NOCHANNEL or MULTICHANNEL

  const char* trackname();
  void settrackname(char* name, int namelen = -1);  // if namelen < 0 then calculated by strlen(name)

  int program_[16];
  int volume_[16];
  int balance_[16];
  int chorus_[16];
  int reverb_[16];
  int hbank_[16];
  int lbank_[16];
  int used_[16];

  long pos_, len_;

protected:
  char* name_;
};

class MidiTrackinfo : public MidiRead
{
public:
  MidiTrackinfo(char* filename);
  virtual ~MidiTrackinfo();

  virtual void print(int trackno, FILE* output = 0, int verbose = 0);
  virtual void print(FILE* output = 0, int verbose = 0);
  virtual void printchannelparams(int trackno, int channel, FILE* output = 0, int verbose = 0);

  int trackcount() { return tracks_; }
  Trackinfo* trackinfo(int trackno); // 1..trackcount()

  long tempo_;   // tempo
  int tactnom_, tactdenom_;  // tact
  MidiMode mode_;

protected:
  Trackinfo **track_; // track_[0..tracks_-1]
  int ready_;

  virtual void head(unsigned version, unsigned tracks, unsigned unitsperbeat);
  virtual void track(int trackno, long length, int channel);
  virtual void endtrack(int trackno);

  virtual void text(int what, unsigned len, char* whattext, unsigned char* txt);
  virtual void end();
  virtual void tact(int nom, int denom, int unitsperbeat, int notes32perbeat);
  virtual void tempo(unsigned long ticks);
  virtual void key(int signature, int isminor);

  virtual void noteon(int channel, int note, int vel);
  virtual void noteoff(int channel, int note, int vel);
  virtual void program(int prg, int channel);

  virtual void control(int channel, int what, int value);
  virtual void volume(int channel, int val);
  virtual void balance(int channel, int val);
  virtual void reverb(int channel, int val);
  virtual void chorus(int channel, int val);
  virtual void highbank(int channel, int val);
  virtual void lowbank(int channel, int val);

  virtual void gmreset();
  virtual void gsreset();
  virtual void xgreset();

  virtual void endmidi();
  virtual void error(const char* msg);
};

#endif
