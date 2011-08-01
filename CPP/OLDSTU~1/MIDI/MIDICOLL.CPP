#include "midicoll.hpp"
#include <stdlib.h>
#include <string.h>

static char* version = "midicoll v1.4 by Gnter Nagler (" __DATE__ ")";

EventInfo::EventInfo()
{
  channel_ = 0;
  track_ = 0;
  startunit_ = 0;
  startms_ = 0;
}

EventInfo::~EventInfo()
{
}

HeaderInfo::HeaderInfo(int unitsperbeat, int version, int trackcount)
{
  unitsperbeat_ = unitsperbeat;
  version_ = version;
  trackcount_ = trackcount;
}

HeaderInfo::HeaderInfo(MidiRead* midi)
{
  unitsperbeat_ = midi->unitsperbeat_;
  version_ = midi->version_;
  trackcount_ = midi->tracks_;
}

TempoInfo::TempoInfo(float beatspermin)
{
  beatspermin_ = beatspermin;
}

TactInfo::TactInfo(int nomin, int denom)
{
  nomin_ = nomin;
  denom_ = denom;
}

NoteInfo::NoteInfo()
{
  endunit_ = 0;
  endms_ = 0;
  note_ = 0;
  vel_ = 0;
  ready_ = 0;
}

ProgramInfo::ProgramInfo()
{
  program_ = 0;
}

ControlInfo::ControlInfo()
{
  controlnr_ = 0;
  controlvalue_ = 0;
}

TextInfo::TextInfo(const char* text, unsigned textlen, int texttype)
{
  text_ = 0;
  texttype_ = texttype;
  if (text)
  {
    text_ = (char*)malloc(textlen + 1);
    if (text_)
    {
      strncpy(text_, text, textlen);
      text_[textlen] = '\0';
    }
  }
}

TextInfo::~TextInfo()
{
  if (text_)
    free(text_);
  text_ = 0;
}

const char* TextInfo::gettext()
{
  return text_;
}

MidiCollect::MidiCollect(const char* filename, const char* eventlist) : MidiSerial(filename)
{
  eventlist_ = eventlist;
  option_delete_events_ = 1;
  list_ = 0;
  maxcount_ = count_ = 0;
  collectunit_ = 0;
  recordcnt_ = 0;
  curtact_nomin_ = curtact_denom_ = 4;
  curtact_units_ = curtactunits();
  lasttact_unit_ = -1;
}

int MidiCollect::curtactunits()
{
  return curtact_nomin_ * unitsperbeat_ * 4 / curtact_denom_;
}

MidiCollect::~MidiCollect()
{
  // these events are not fired yet, user hasn't used them => delete automatically
    for (int i = 0; i < count_; i++)
      delete list_[i];
  maxcount_ = count_ = 0;
  if (list_)
     free(list_);
}

void MidiCollect::head(unsigned version, unsigned tracks, unsigned unitperbeat)
{
  if (eventlist_ && strchr(eventlist_, 'H') == 0)
    return;
  addevent(new HeaderInfo(unitperbeat, version, tracks));
}

void MidiCollect::endmidi()
{
  collect();
  if (count_ > 0)
    fprintf(stderr, "Warning: %d notes were not stopped\n", count_);
  for (int i = 0; i < count_; i++)
  {
    if (list_[i]->EventType() != 'N')
      continue;
    NoteInfo* note = (NoteInfo*)list_[i];
    note->endunit_ = getcurunit();
    note->endms_ = getcurmillisec();
    note->ready_ = 1;
  }
  collect();
  EndEvents();
}

int MidiCollect::startevent(EventInfo* note)
{
  if (!note)
    return 0;
  return addevent(note);
}

int MidiCollect::addevent(EventInfo* note)
{
  if (!note)
    return 0;
  if (count_ == maxcount_)
  {
    if (maxcount_ >= 16000)
      list_ = 0;
    else
    {
      maxcount_ += 100;
      list_ = (EventInfo**)realloc(list_, maxcount_ * sizeof(EventInfo*));
    }
    if (!list_)
    {
      outofmemory();
      return 0;
    }
  }
  list_[count_++] = note;
  return 1;
}

void MidiCollect::killevent(EventInfo* event)
{
  for (int i = 0; i < count_; i++)
  if (list_[i] == event)
  {
    removeevent(i);
    break;
  }
}

int MidiCollect::findnote(NoteInfo* note)
{
int besti = -1;

  for (int i = 0; i < count_; i++)
  if (list_[i]->EventType() == 'N')
  {
    NoteInfo* n = (NoteInfo*)list_[i];
    if (!n->ready() && n->note_ == note->note_ &&
      n->channel_ == note->channel_)
    {
      if (n->track_ == note->track_)
	return i;
      besti = i; // track not matching
    }
  }
  return besti;
}

int MidiCollect::removeevent(int i)
{
  if (i  < 0 || i >= count_)
    return 0;
  if (option_delete_events_)
    delete list_[i];
  else
    ; // user of class cares of deleting

  list_[i] = NULL;
  if (i != count_-1)
    list_[i] = list_[count_-1];
  list_[count_-1] = NULL;
  count_ --;

  if (maxcount_ - 100 > count_)
  {
    maxcount_ = count_+100;
    list_ = (EventInfo**)realloc(list_, maxcount_ * sizeof(EventInfo*));
    if (!list_)
    {
      outofmemory();
      return 0;
    }
  }
  return 1;
}

void MidiCollect::stopnote(NoteInfo* note)
{
  int i = findnote(note);
  if (i < 0)
    return;

  NoteInfo* n = (NoteInfo*)list_[i];

  n->endunit_ = note->endunit_;
  n->endms_ = note->endms_;
  n->ready_ = 1;

  collect();
}

void MidiCollect::collect()
{
unsigned long nextunit = 0;
int besti = -1;
int printcnt;

  do
  {
    printcnt = 0;
    besti = -1;
    for (int i = 0; i < count_; i++)
    {
      EventInfo* listi = list_[i];
      if (listi->ready() && listi->startunit_ == collectunit_)
      {
	    fireevent(listi); printcnt++;
	    killevent(listi);
        if (exit_)
          return;
        i--; // process current note again
        continue;
      }
      if (besti < 0 || (i <count_ && listi->startunit_ < nextunit))
      {
	    nextunit = listi->startunit_;
	    besti = i;
      }
    }
    if (besti < 0)  // no next unit found (maybe no notes available)
      break;
    if (collectunit_ == nextunit)
      break;
    collectunit_ = nextunit;
  } while (exit_ == 0);
}

void MidiCollect::noteon(int channel, int note, int vel)
{
  if (eventlist_ && strchr(eventlist_, 'N') == 0)
    return;

  NoteInfo* ninfo = new NoteInfo;
  if (!ninfo)
  {
    outofmemory();
    exit_ = 1;
    return;
  }

  // see if note is currently playing
  ninfo->track_ = trackno_;
  ninfo->endunit_ = getcurunit();
  ninfo->endms_ = getcurmillisec();
  ninfo->channel_ = channel+1;
  ninfo->note_ = note;
  ninfo->vel_ = vel;
  if (findnote(ninfo) >= 0)
    stopnote(ninfo);

  ninfo->track_ = trackno_;
  ninfo->startunit_ = getcurunit();
  ninfo->startms_ = getcurmillisec();
  ninfo->channel_ = channel+1;
  ninfo->note_ = note;
  ninfo->vel_ = vel;

//  printf("%ld ON[%d] %d\n", ninfo->startunit_, ninfo->channel_, ninfo->note_);
  startevent(ninfo);
}

void MidiCollect::noteoff(int channel, int note, int vel)
{
  if (eventlist_ && strchr(eventlist_, 'N') == 0)
    return;
  NoteInfo* ninfo = new NoteInfo;
  if (!ninfo)
  {
    outofmemory();
    exit_ = 1;
    return;
  }
  ninfo->track_ = trackno_;
  ninfo->endunit_ = getcurunit();
  ninfo->endms_ = getcurmillisec();
  ninfo->channel_ = channel+1;
  ninfo->note_ = note;
  ninfo->vel_ = vel;

//  printf("%ld OFF[%d] %d\n", ninfo->endunit_, ninfo->channel_, ninfo->note_);
  stopnote(ninfo);

  delete ninfo;
}

void MidiCollect::program(int channel, int prg)
{
  if (eventlist_ && strchr(eventlist_, 'P') == 0)
    return;
  ProgramInfo* t = new ProgramInfo;
  if (!t)
  {
    outofmemory();
    exit_ = 1;
    return;
  }
  t->channel_ = channel+1;
  t->program_ = prg;
  t->startunit_ = getcurunit();
  t->startms_ = getcurmillisec();
  t->track_ = trackno_;
  if (!startevent(t))
    exit_ = 1;
}

void MidiCollect::control(int channel, int what, int val)
{
  if (eventlist_ && strchr(eventlist_, 'C') == 0)
    return;
  ControlInfo* t = new ControlInfo;
  if (!t)
  {
    outofmemory();
    exit_ = 1;
    return;
  }
  t->channel_ = channel+1;
  t->controlnr_ = what;
  t->controlvalue_ = val;
  t->startunit_ = getcurunit();
  t->startms_ = getcurmillisec();
  t->track_ = trackno_;
  if (!startevent(t))
    exit_ = 1;
}

void MidiCollect::tempo(unsigned long ticks)
{
  if (eventlist_ && strchr(eventlist_, 'T') == 0)
    return;
  TempoInfo* t = new TempoInfo(bpm(ticks));
  if (!t)
  {
    outofmemory();
    exit_ = 1;
    return;
  }

  t->startunit_ = getcurunit();
  t->startms_ = getcurmillisec();
  t->track_ = trackno_;
  if (!startevent(t))
    exit_ = 1;
}

void MidiCollect::tact(int nom, int denom, int , int )
{
  if (eventlist_ && strchr(eventlist_, 'B') == 0)
    return;
  curtact_nomin_ = nom;
  curtact_denom_ = denom;
  curtact_units_ = curtactunits();
  TactInfo* tact = new TactInfo(nom, denom);
  if (!tact)
  {
      outofmemory();
      exit_ = 1;
      return;
  }
  tact->startunit_ = getcurunit();
  tact->startms_ = getcurmillisec();
  tact->track_ = trackno_;
  if (!startevent(tact))
    exit_ = 1;
}

void MidiCollect::text(int what, unsigned len, char* /*whattext*/, unsigned char* txt)
{
  if (eventlist_ && strchr(eventlist_, 't') == 0)
    return;
  TextInfo* t = new TextInfo((const char*)txt, len, what);
  if (!t || !t->gettext())
  {
    outofmemory();
    exit_ = 1;
    return;
  }

  t->startunit_ = getcurunit();
  t->startms_ = getcurmillisec();
  t->track_ = trackno_;
  if (!startevent(t))
    exit_ = 1;
}

void MidiCollect::outofmemory()
{
  exit_ = 1;
}

void MidiCollect::fireevent(EventInfo* event)
{
  if (recordcnt_ == 0)
    StartEvents();

  if (event)
    Event(event);
  recordcnt_++;
//  collect();
}

void MidiCollect::StartEvents()
{
}

void MidiCollect::Event(EventInfo*)
{
}

void MidiCollect::EndEvents()
{
}