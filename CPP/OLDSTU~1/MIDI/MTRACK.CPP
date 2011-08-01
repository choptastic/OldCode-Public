#include "mtrack.hpp"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "progname.h"

Trackinfo::Trackinfo()
{
  name_ = 0;
  channel_ = NOCHANNEL;
  for (int ch = 0; ch < 16; ch++)
  {
    program_[ch] = volume_[ch] = balance_[ch] = chorus_[ch] = reverb_[ch] = -1;
    hbank_[ch] = lbank_[ch] = -1;
    used_[ch] = 0;
  }
}

Trackinfo::~Trackinfo()
{
  settrackname(NULL);
}

const char* Trackinfo::trackname()
{
  if (!name_)
    return "";
  else
    return (const char*)name_;
}

void Trackinfo::settrackname(char* name, int namelen)
{
  if (name_)
  {
    free(name_); name_ = 0;
  }
  if (namelen < 0)
    namelen = name ? strlen(name) : 0;
  if (name && namelen > 0 && *name)
  {
    name_ = (char*)malloc(namelen+1);
    assert(name_ != 0);
    strncpy(name_, name, namelen);
    name_[namelen] = '\0';
  }
}

MidiTrackinfo::MidiTrackinfo(char* name) : MidiRead(name)
{
  mode_ = MODE_GM;
  track_ = 0;
  tempo_ = 0;
  tactnom_ = tactdenom_ = 0;
  if (getf())
  {
    run();
    if (!tactnom_ || !tactdenom_)
    {
      tactnom_ = 4;
      tactdenom_ = 4;
    }
    if (!tempo_)
      tempo_ = 500000L;
  }
}

MidiTrackinfo::~MidiTrackinfo()
{
  for (int i = 0; i < tracks_; i++)
    delete track_[i];
  if (track_)
  {
    free(track_); track_ = 0;
  }
}

void MidiTrackinfo::head(unsigned /*version*/, unsigned tracks, unsigned /*unitsperbeat*/)
{
  if (tracks > 0)
  {
    track_ = (Trackinfo**) malloc(sizeof(Trackinfo*) * tracks);
    if (!track_)
    {
      error("out of memory");
      tracks_ = 0;
    }
    for (int i = 0; i < tracks_; i++)
      track_[i] = 0;
  }
}

void MidiTrackinfo::track(int trackno, long length, int channel)
{
  ready_ = 0;
  track_[trackno_-1] = new Trackinfo;
  if (!track_[trackno-1])
  {
    error("out of memory");
    return;
  }
  track_[trackno_-1]->pos_ = getpos();
  track_[trackno_-1]->len_ = length;
  track_[trackno_-1]->channel_ = channel;

  if (channel >= 0 && channel < 16)
    track_[trackno_-1]->used_[channel] = 1;
}

void MidiTrackinfo::endtrack(int /*trackno*/)
{
}

void MidiTrackinfo::text(int what, unsigned len, char* /*whattext*/, unsigned char* txt)
{
  if (what == meta_trackname && track_[trackno_-1] && strlen(track_[trackno_-1]->trackname()) == 0)
    track_[trackno_-1]->settrackname((char*)txt, len);
}

void MidiTrackinfo::end()
{
}


void MidiTrackinfo::tact(int nom, int denom, int /*unitsperbeat*/, int /*notes32perbeat*/)
{
  tactnom_ = nom;
  tactdenom_ = denom;
}

void MidiTrackinfo::tempo(unsigned long ticks)
{
  tempo_ = ticks;
}

void MidiTrackinfo::key(int /*signature*/, int /*isminor*/)
{
}

void MidiTrackinfo::noteon(int channel, int /*note*/, int /*vel*/)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    track_[trackno_-1]->used_[channel] = 1;

    if( track_[trackno_-1]->channel_ != MULTICHANNEL ) ready_ = 1;
  }
}

void MidiTrackinfo::noteoff(int channel, int /*note*/, int /*vel*/)
{
  if (!ready_ && track_ && track_[trackno_-1])
    track_[trackno_-1]->used_[channel] = 1;
}

void MidiTrackinfo::program(int channel, int prg)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->program_[channel] < 0)
      track_[trackno_-1]->program_[channel] = prg;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::balance(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->balance_[channel] < 0)
      track_[trackno_-1]->balance_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::volume(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->volume_[channel] < 0)
      track_[trackno_-1]->volume_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::reverb(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->reverb_[channel] < 0)
      track_[trackno_-1]->reverb_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::chorus(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->chorus_[channel] < 0)
      track_[trackno_-1]->chorus_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::highbank(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->hbank_[channel] < 0)
      track_[trackno_-1]->hbank_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::lowbank(int channel, int val)
{
  if (!ready_ && track_ && track_[trackno_-1])
  {
    if (track_[trackno_-1]->lbank_[channel] < 0)
      track_[trackno_-1]->lbank_[channel] = val;
    track_[trackno_-1]->used_[channel] = 1;
  }
}

void MidiTrackinfo::gmreset()
{
  if (!ready_)
    mode_ = MODE_GM;
}

void MidiTrackinfo::gsreset()
{
  if (!ready_)
    mode_ = MODE_GS;
}

void MidiTrackinfo::xgreset()
{
  if (!ready_)
    mode_ = MODE_XG;
}

void MidiTrackinfo::endmidi()
{
}

void MidiTrackinfo::error(const char* msg)
{
  printf("error: %s\n", msg);
}

const char* channelstr(int channel)
{
  if (channel == MULTICHANNEL)
    return "MULTICHANNEL";
  else if (channel == NOCHANNEL)
    return "NOCHANNEL";
  else if (channel >= 0 && channel <= 15)
  {
  static char chnum[3];

    sprintf(chnum, "%d", channel+1);
    return (const char*)chnum;
  }
  assert((channel >= 0 && channel <= 15) || channel == MULTICHANNEL || channel == NOCHANNEL);
  return 0;
}

void MidiTrackinfo::printchannelparams(int trackno, int channel, FILE* output, int verbose)
{
Trackinfo* info = trackinfo(trackno);
const char* name;

  if (channel >= 0 && !info->used_[channel])
    return;

  if (!output)
    output = stdout;
  if (verbose)
  {
     if (channel >= 0 && channel <= 15)
       name = patch(channel, info->hbank_[channel], info->lbank_[channel], info->program_[channel], mode_);
     else
       name = 0;
     if (channel != NOCHANNEL)
       fprintf(output, "  program: %s\n", name ? name : "???");

     if (info->volume_[channel] >= 0)
       fprintf(output, "  volume: %d  (0=mute,127=full)\n", info->volume_[channel]);
     if (info->balance_[channel] >= 0)
       fprintf(output, "  balance: %d (0=left, 64=mid, 127=right)\n", info->balance_[channel]);
     if (info->chorus_[channel] >= 0)
       fprintf(output, "  chorus: %d (0-127)\n", info->chorus_[channel]);
     if (info->reverb_[channel] >= 0)
       fprintf(output, "  reverb: %d (0-127)\n", info->reverb_[channel]);
  }
  else
  {
    if (channel >= 0 && channel <= 15)
      name = patch(channel, info->hbank_[channel], info->lbank_[channel], info->program_[channel], mode_);
    else
      name = 0;
    if (channel != NOCHANNEL)
      fprintf(output, "(%s)", name ? name : "???");
  }
}

void MidiTrackinfo::print(int trackno, FILE* output, int verbose)
{
Trackinfo* info = trackinfo(trackno);

  if (!info)
    return;

  if (!output)
    output = stdout;
  fprintf(output, "Track %d", trackno);
  if (verbose)
  {
    fprintf(output, ":\n");
    fprintf(output, "  channel: %s\n", channelstr(info->channel_));
    if (strlen(info->trackname()) > 0)
      fprintf(output, "  name: \"%s\"\n", info->trackname());
    else if (trackno == 1 && version_ == 1)
      fprintf(output, "  tempo track\n");

    if (info->channel_ == MULTICHANNEL)
    {
      for (int ch = 0; ch < 16; ch++)
      if (info->used_[ch])
      {
	fprintf(output, "channel %s\n", channelstr(ch));
	printchannelparams(trackno, ch, output, verbose);
      }
    }
    else
    {
       printchannelparams(trackno, info->channel_, output, verbose);
    }
  }
  else
  {
    if (info->channel_ == MULTICHANNEL)
    {
      fprintf(output, ": %s\n", channelstr(info->channel_));
      for (int ch = 0; ch < 16; ch++)
      if (info->used_[ch])
      {
	fprintf(output, " [%s]: ", channelstr(ch));
	printchannelparams(trackno, ch, output, verbose);
	fprintf(output, "\n");
      }
    }
    else
    {
      fprintf(output, " [%s]: ", channelstr(info->channel_));
      if (version_ == 1 && trackno == 1 && strlen(info->trackname()) == 0)
	fprintf(output, "tempo track ");
      else
	fprintf(output, "\"%s\" ",  info->trackname());

      printchannelparams(trackno, info->channel_, output, verbose);
      fprintf(output, "\n");
    }
  }
}

void MidiTrackinfo::print(FILE* output, int verbose)
{
  if (!getf() || !tracks_)
    return;
  if (!output)
    output = stdout;

  if (verbose)
  {
    printf("Midi format %d ", version_);
    switch(version_)
    {
    case 0: printf("(single multichannel track)\n"); break;
    case 1: printf("(tempo track and channel separated tracks)\n"); break;
    case 2: printf("(each track is a song)\n"); break;
    default: printf("(unknown)\n"); break;
    }
    if (tempo_ != 0)
    {
#ifdef USE_FLOAT
      fprintf(output, "Tempo: %2.2f beats/min\n", (float)(60000000.0 / (float)tempo_));
#else
      int beats_div = (int)(60000000L / tempo_);
      long beats_mod = 60000000L % tempo_;
      int beats_frac = (int)((beats_mod * 100) / tempo_);
      fprintf(output, "Tempo: %2d.%02d beats/min\n", beats_div, beats_frac);
#endif
    }
    if (tactnom_ != 0 && tactdenom_ != 0)
      fprintf(output, "Tact: %d/%d\n", tactnom_, tactdenom_);
    if (unitsperbeat_)
      fprintf(output, "Resolution: 1/%d\n", unitsperbeat_ * 4);
  }

  for (int i = 1; i <= trackcount(); i++)
    print(i, output, verbose);
}

Trackinfo* MidiTrackinfo::trackinfo(int trackno)
{
  if (trackno >= 1 && trackno <= trackcount())
    return track_[trackno-1];
  return 0;
}

void MidiTrackinfo::control(int channel, int /*what*/, int /*value*/)
{
  if (track_ && track_[trackno_-1])
  {
    track_[trackno_-1]->used_[channel] = 1;
  }
}
