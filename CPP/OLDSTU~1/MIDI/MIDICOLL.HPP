#ifndef __MIDICOLLECT_HPP
#define __MIDICOLLECT_HPP

#include "midiio.hpp"

class EventInfo
{
public:
  EventInfo();
  virtual ~EventInfo();

  virtual const int EventType() { return 0; }
  virtual const char* EventName() { return 0; }
  virtual int ready() { return 1; }

  int track_;
  unsigned char channel_;
  unsigned long startunit_;
  unsigned long startms_;
};

class NoteInfo : public EventInfo
{
public:
  NoteInfo();

  virtual const int EventType() { return 'N'; }
  virtual const char* EventName() { return "Note"; }
  virtual int ready() { return ready_; }

  unsigned long endunit_;
  unsigned long endms_;
  unsigned char note_;
  unsigned char vel_;
  char ready_;
};

class ProgramInfo : public EventInfo
{
public:
  ProgramInfo();

  virtual const int EventType() { return 'P'; }
  virtual const char* EventName() { return "Program"; }

  unsigned char program_;
};

class ControlInfo : public EventInfo
{
public:
  ControlInfo();

  virtual const int EventType() { return 'C'; }
  virtual const char* EventName() { return "Control"; }

  unsigned char controlnr_;
  unsigned char controlvalue_;
};

class HeaderInfo : public EventInfo
{
public:
  HeaderInfo(int unitsperbeat, int version, int trackcount);
  HeaderInfo(MidiRead*);

  virtual const int EventType() { return 'H'; }
  virtual const char* EventName() { return "Header"; }

  int unitsperbeat_, version_, trackcount_;
};

class TempoInfo : public EventInfo
{
public:
  TempoInfo(float beatspermin);

  virtual const int EventType() { return 'T'; }
  virtual const char* EventName() { return "Tempo"; }

  float beatspermin_;
};

class TactInfo : public EventInfo
{
public:
  TactInfo(int nomin, int denom);

  virtual const int EventType() { return 'B'; }
  virtual const char* EventName() { return "Bar"; }

  int nomin_, denom_; // e.g. 3/4
};

class TextInfo : public EventInfo
{
public:
  TextInfo(const char* text, unsigned textlen, int texttype);
 ~TextInfo();

  virtual const int EventType() { return 't'; }
  virtual const char* EventName() { return "Text"; }

  const char* gettext();
  int texttype_; // meta values

protected:
  char* text_;
};

class MidiCollect : public MidiSerial
{
public:
  MidiCollect(const char* filename, const char* eventmask = NULL);
  ~MidiCollect();

  char option_delete_events_; // default=1  MidiCollect removes all events after use

  int addevent(EventInfo* event);
  void killevent(EventInfo* event);

  virtual void StartEvents();
  virtual void Event(EventInfo* event);
  virtual void EndEvents();

protected:
  virtual void head(unsigned version, unsigned tracks, unsigned unitperbeat);

  virtual void noteon(int channel, int note, int vel);
  virtual void noteoff(int channel, int note, int vel);
  virtual void program(int channel, int prg);
  virtual void control(int channel, int what, int val);

  virtual void tempo(unsigned long microsecperbeat);
  virtual void tact(int nom, int denom, int unitsperbeat, int notes32perbeat);

  virtual void text(int what, unsigned len, char* whattext, unsigned char* txt);

  int startevent(EventInfo* event);
  void stopnote(NoteInfo* note);

  virtual void endmidi();

protected:
  const char* eventlist_;
  unsigned long collectunit_;
  long recordcnt_;

  EventInfo** list_;
  int maxcount_, count_;

  int curtact_nomin_, curtact_denom_, curtact_units_;
  long lasttact_unit_;

  int curtactunits();

  int findnote(NoteInfo* note);

  void collect();
  void fireevent(EventInfo* event);

  virtual void outofmemory();

private:
  int removeevent(int i);
};

#endif
