// midiio.cpp written by GÅnter Nagler 1995 (gnagler@ihm.tu-graz.ac.at)
#ifdef _MFC
#include <stdafx.h>
#endif
#include "midiio.hpp"
#include <assert.h>
#ifdef __MSDOS__
#include <mem.h>
#endif
#include <string.h>
#include <stdlib.h>

static char* copyright = "midiio v1.11 (c) 1995 by GÅnter Nagler (" __DATE__ ")";

int compress = 1;

// common sysex events
unsigned char sysex_gmreset[] = { 0x7E, 0x7F, 0x09, 0x01, 0xF7 };
unsigned char sysex_gsreset[] = { 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7F, 0x00, 0x41, 0xF7 };
unsigned char sysex_gsexit[] =  { 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7F, 0x7F, 0x42, 0xF7 };
unsigned char sysex_xgreset[] = { 0x43, 0x10, 0x4C, 0x00, 0x00, 0x7E, 0x00, 0xF7 };

static int issysex(unsigned char* sysex, unsigned char* sysdata, unsigned syslen)
{
  if (*sysex == 0xF0)
    sysex++;
  unsigned i = 0;
  while (syslen > 0)
  {
    if (i == 1 && (sysex[0] & 0xF0) == 0x10)
    {
      if ((*sysex & 0xF0) != (*sysdata & 0xF0))
	return 0;
    }
    else if (*sysex != *sysdata)
	return 0;
    syslen--;
    if (*sysex == 0xF7)
      break;
    sysex++;
    sysdata++;
    i++;
  }
  return (syslen != 0) ? 0 : 1;
}

// syslen contains f7 then syslen will be calculated
static int sysexlen(int syslen, unsigned char* sysex)
{
int len = 0;

  len = 0;
  if (*sysex == 0xF0)
  {
    sysex++;
    syslen--;
  }
  while (*sysex != 0xF7 && (syslen == 0 || len < syslen))
  {
    sysex++;
    len++;
  }
  if (*sysex == 0xF7)
    return len+1; // incl. F7
  return syslen;
}

// syslen contains f7 then syslen will be calculated
static long sysexlen(FILE* f, long sysdatapos, long sysdatalen)
{
long oldpos = ftell(f);
long len = 0;
int c;

  fseek(f, sysdatapos, SEEK_SET);
  c = fgetc(f);
  if (c == 0xF0)
  {
    sysdatapos++;
    sysdatalen--;
    c = fgetc(f);
  }
  while (c != EOF && c != 0xF7 && len < sysdatalen)
  {
    sysdatapos++;
    len++;
    c = fgetc(f);
  }
  if (c == 0xF7)
    sysdatalen = len+1; // incl. F7

  fseek(f, oldpos, SEEK_SET);
  return sysdatalen;
}

// class MidiRead

const char* MidiRead::copyright()
{
  return (const char*)::copyright;
}

MidiBuffer::MidiBuffer(const char* filename, FILE* f, char preload)
{
  shouldfreemidibuf_ = 1;
  midiname_ = filename;
  midibuf_ = 0;
  midibufsize_ = 0;
  midibuflen_ = 0;
  midibufpos_ = 0;
  write_ = 0;
  if (f)
  {
    f_ = f;
    shouldclose_ = 0;
  }
  else
  {
    shouldclose_ = 1;
    if (!filename)
      f_ = 0;
    else if (preload == MIDI_CREATE)
    {
      f_ = fopen(midiname_, WRITE_BINARY);
      write_ = 1;
    }
    else
      f_ = fopen(filename, READ_BINARY);
  }
  if (f_)
  {
    if (preload == MIDI_CREATE)
      filesize_ = 0;
    else
    {
      fseek(f_, 0L, SEEK_END);
      filesize_ = ftell(f_);
      fseek(f_, 0L, SEEK_SET);
    }
  }
  else
    filesize_ = 0;

  if (filesize_ > 0 && preload == MIDI_PRELOAD
#ifdef __MSDOS__
    && filesize_ <= 0x7fff
#endif
  )
  {
    midibufsize_ = (unsigned)filesize_;
    midibuf_ = (unsigned char*)malloc(midibufsize_);
    if (midibuf_)
      need(0, midibufsize_);
  }
  if (f_ && !midibuf_
#ifdef __MSDOS__
    && MIDI_BUFSIZE <= 0x7fff
#endif
  )
  {
    midibufsize_ = (unsigned)MIDI_BUFSIZE;
    midibuf_ = (unsigned char*)malloc(midibufsize_);
  }
  if (!midibuf_)
  {
    midibufsize_ = sizeof(minibuf_);
    midibuf_ = minibuf_;
    shouldfreemidibuf_ = 0;
  }
}

MidiBuffer::MidiBuffer(unsigned char* mididata, long mididatalen, char shouldfree)
{
  midiname_ = 0;
  f_ = 0;
  shouldclose_ = 0;
  midibuf_ = mididata;
  if (midibuf_)
    filesize_ = mididatalen;
  else
    filesize_ = 0;
  midibuflen_ = midibufsize_ = (unsigned)filesize_;
  shouldfreemidibuf_ = shouldfree;
}

const char *MidiBuffer::midiname()
{
  return midiname_;
}

long MidiBuffer::midilength()
{
  return filesize_;
}

unsigned MidiBuffer::bufsize()
{
  return midibufsize_;
}

unsigned MidiBuffer::bufavail(long pos)
{
  if (pos < 0)
    return 0;
  if (write_)
  {
    if (pos > filesize_)
      return 0;
    return midibufsize_;
  }
  else
  {
    if (pos >= filesize_)
       return 0;
  }
  unsigned n = midibufsize_;
  if (filesize_-pos < n)
    n = (unsigned)(filesize_-pos);
  return n;
}

MidiBuffer::~MidiBuffer()
{
  flush();
  if (f_ && shouldclose_)
  {
    fclose(f_);
    f_ = 0;
  }
  if (midibuf_)
  {
    if (shouldfreemidibuf_)
      free(midibuf_);
    midibuf_ = 0;
  }
}

unsigned char* MidiBuffer::need(long pos, unsigned len)
{
  if (pos < 0 || !midibuf_ || midibufsize_ < len)
    return 0;

  if (write_)
  {
    if (pos > filesize_)
      return 0;
    if (f_ && (pos < midibufpos_ || pos > midibufpos_ + midibuflen_ || pos + len > midibufpos_ + midibufsize_))
    {
      flush();
      midibufpos_ = pos;
      midibuflen_ = len;
    }
    else if (pos + len > midibufpos_ + midibuflen_)
      midibuflen_ = (unsigned)(pos + len - midibufpos_);
    if (pos + len > filesize_)
      filesize_ = pos + len;
    if (pos >= midibufpos_ && pos + len <= midibufpos_ + midibuflen_)
      return midibuf_ + (unsigned)(pos - midibufpos_);
  }
  else
  {
    if (pos + len > filesize_)
      return 0;
    if (f_ && (pos < midibufpos_ || pos + len > midibufpos_ + midibuflen_))
    {
      fseek(f_, pos, SEEK_SET);
      midibufpos_ = pos;
      midibuflen_ = bufavail(pos);
      if (fread(midibuf_, midibuflen_, 1, f_) != 1)
      {
	midibuflen_ = 0;
	return 0;
      }
      return midibuf_;
    }
    if (pos >= midibufpos_ && pos + len <= midibufpos_ + midibuflen_)
      return midibuf_ + (unsigned)(pos - midibufpos_);
  }
  return 0;
}

void MidiBuffer::flush()
{
  if (!write_ || !f_ || midibuflen_ == 0)
    return;
  fseek(f_, midibufpos_, SEEK_SET);
  if (fwrite(midibuf_, midibuflen_, 1, f_) != 1)
  {
    error("write error (maybe disk full)");
    return;
  }
  midibuflen_ = 0;
}

void MidiBuffer::error(const char* msg)
{
  fprintf(stderr, "error: %s\n", msg);
}

void MidiBuffer::warning(const char* msg)
{
  fprintf(stderr, "warning: %s\n", msg);
}

MidiRead::MidiRead(const char* filename, FILE* f, char preload) : MidiBuffer(filename, f, preload)
{
  curpos_ = 0;
  pos_ = 0;
  curchannel_ = NOCHANNEL;
  curunit_ = 0;
  options_ = 0;
  curms_ = currest_ = 0;
  microsecperbeat_ = timediv_ = 0;

  version_ = tracks_ = unitsperbeat_ = trackno_ = 0;
  tracklen_ = 0;
  skiptrack_ = 0;
  exit_ = 0;
}

MidiRead::~MidiRead()
{
}

long MidiRead::seekmidihead()
{
long pos = 0;
unsigned char* data;
unsigned n;

  while (pos < midilength())
  {
    seek(pos);
    data = need(n = bufavail(pos));
    if (data)
    {
      unsigned len = n;
      unsigned char* c = data;
      while (len >= 4)
      {
	if (*c == 'M' && c[1] == 'T' && c[2] == 'h' && c[3] == 'd')
	{
	  seek(pos);
	  return pos;
	}
	len--;
	c++;
	pos++;
      }
      if (midilength() - pos < 4)
	break;
    }
    else
      break;
  }
  seek(0);
  return -1;
}

int MidiRead::runhead()
{
  exit_ = 0;
  if (!f_)
    return 0;
  if (seekmidihead() < 0 || getlong() != MThd)
  {
    error("missing midi header MThd");
    return 0;
  }

  if (getlong() == 6)
  {
    version_ = getword();
    if (version_ < 0 || version_ > 2)
    {
      error("invalid midi version");
      return 0;
    }
    tracks_ = getword();
    unitsperbeat_ = getword();
    timediv_ = (1000L * unitsperbeat_);
    microsecperbeat_ = 500000L;  // default tempo = 120 beats/min
    head(version_, tracks_, unitsperbeat_);
    if (exit_)
      return 0;
  }
  else
  {
    error("illegal midi header");
    return 0;
  }
  return 1;
}

int MidiRead::run()
{
  exit_ = 0;
  pos_ = curpos_;
  if (!runhead())
    return 0;
  pos_ = curpos_;
  for (trackno_ = 1; trackno_ <= tracks_; trackno_++)
  {
    if (!runtrack(trackno_))
      return 0;
  }
  if (curpos_ >= midilength())
    percent(percent_ = 100);
  endmidi();
  return 1;
}

int MidiRead::runevent(long trackend)
{
int midicode;

  if (exit_)
    return 0;
  pos_ = curpos_;

  unsigned char *c = need(1);
  if (!c || c[0] >= 0x80 || lastcode_ < 0)
    midicode = getbyte();
  else
    midicode = lastcode_;

  if (midicode < 0)
    return 0;

  switch(midicode)
  {
  case 0xf0: // sysex
  case 0xf7:
    {
      long syslen = readsyseventlength(trackend - curpos_);
      if (!syslen)
      {
	error("end of sysex not found");
	return 0;
      }
      long sysdatapos = curpos_;
      unsigned char* sysdata = 0;
      if (syslen < bufavail(sysdatapos))
      {
	sysdata = get((unsigned)syslen);
        if ((options_ & OPTION_NOSYSEVENTS) == 0)
        {
	  if (issysex(sysex_gmreset, sysdata, (unsigned)syslen))
	    gmreset();
	  else if (issysex(sysex_gsreset, sysdata, (unsigned)syslen))
	    gsreset();
	  else if (issysex(sysex_gsexit, sysdata, (unsigned)syslen))
	    gsexit();
	  else if (issysex(sysex_xgreset, sysdata, (unsigned)syslen))
	    xgreset();
	  else
          {
	    sysex((unsigned)syslen, sysdata);
          }
        }
        else if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
        {
	  sysex((unsigned)syslen, sysdata);
        }
        else
	  event(0xf0, (unsigned)syslen, sysdata);
      }
      else // large sysex
      {
        skip(syslen);
        if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
          sysex( getf(), sysdatapos, syslen ); // long sysex
        else
          event(0xf0, getf(), sysdatapos, syslen);
      }
    }
    break;
  case 0xf2:
  {
    c = get(2); if (!c) return 0;
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      songpos((unsigned(c[1]) << 7) + unsigned(c[0]));
    else
      event(0xf2, 2, c);
    break;
  }
  case 0xf3:
    c = get(1); if (!c) return 0;
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      songselect(*c);
    else
      event(0xf3, 1, c);
    break;
  case 0xf6:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      tunerequest();
    else
      event(0xf6);
    break;
  case 0xf8:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      timingclock();
    else
      event(0xf8);
    break;
  case 0xfa:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      start();
    else
      event(0xfa);
    break;
  case 0xfb:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      cont();
    else
      event(0xfb);
    break;
  case 0xfc:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      stop();
    else
      event(0xfc);
    break;
  case 0xfe:
    if ((options_ & OPTION_NOREALTIMEEVENTS) == 0)
      activesense();
    else
      event(0xfe);
    break;
  case 0xff:
    {
    int c;
    long metadatalen;

      c = getbyte();
      metadatalen = getdelta();
      long metadatapos = curpos_;
      if (options_ & OPTION_NOREALTIMEEVENTS)
      {
	metadatalen += curdeltalen_ + 1;
	metadatapos -= curdeltalen_ + 1;
	seek(metadatapos);

	if (metadatalen < bufavail(metadatapos))
	  event(0xff, (unsigned)metadatalen, get((unsigned)metadatalen));
        else
          event(0xff, getf(), curpos_, metadatalen);
      }
      else if ((options_ & OPTION_NOMETAEVENTS) && c != 0x2f)
      {
	if (metadatalen < bufavail(metadatapos))
	  meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
        else
          meta(c, getf(), metadatapos, metadatalen);
      }
      else
      {

	if (metadatalen > bufavail(metadatapos))
          meta(c, getf(), metadatapos, metadatalen);
	else
	switch(c)
	{
	case 0:
	  if (metadatalen == 2)
	    seqnumber(getword());
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	case meta_text:
	  text(c, (unsigned)metadatalen, "text", get((unsigned)metadatalen)); break;
	case meta_copyright:
	  text(c, (unsigned)metadatalen, "copyright", get((unsigned)metadatalen));  break;
	case meta_trackname:
	  text(c, (unsigned)metadatalen, "trackname", get((unsigned)metadatalen)); break;
	case meta_instrument:
	  text(c, (unsigned)metadatalen, "instrument", get((unsigned)metadatalen)); break;
	case meta_lyric:
	  text(c, (unsigned)metadatalen, "lyric", get((unsigned)metadatalen)); break;
	case meta_marker:
	  text(c, (unsigned)metadatalen, "marker", get((unsigned)metadatalen)); break;
	case meta_cuepoint:
	  text(c, (unsigned)metadatalen, "cuepoint", get((unsigned)metadatalen)); break;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	  text(c, (unsigned)metadatalen, 0, get((unsigned)metadatalen)); break;
	case 0x20:
	  if ((unsigned)metadatalen == 1)
	    prefixchannel(getbyte());
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	case 0x21:
	  if ((unsigned)metadatalen == 1)
	    prefixport(getbyte());
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	case 0x2F:
	  end();
	  break;
	case 0x51:
	  tempo(microsecperbeat_ = gettri());
	  break;
	case 0x54:
	  if ((unsigned)metadatalen == 5)
	  {
	  unsigned char *s = get((unsigned)metadatalen);

            smpteofs(s[0] >> 5, s[0] & 0x1F, s[1], s[2], s[3], s[4]);
	  }
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	case 0x58:
	  if ((unsigned)metadatalen == 4)
	  {
	  int nom, unitsperbeat, notes32perbeat, log2denom;

	    nom = getbyte();
	    log2denom = getbyte();

	    unitsperbeat = getbyte();
	    notes32perbeat = getbyte();
	    tact(nom, 1 << log2denom, unitsperbeat, notes32perbeat);
	  }
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	case 0x59:
	  if ((unsigned)metadatalen == 2)
	  {
	  signed char s[2];

	    s[0] = (signed char)getbyte(); // sf
	    s[1] = (signed char)getbyte(); // mi
	    if (s[0] >= -7 && s[0] <= +7 && s[1] >= 0 && s[1] <= 1)
	      key(s[0], s[1]);
	    else
	      meta(c, (unsigned)metadatalen, (unsigned char*)s);
	  }
	  else
	    meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	default:
	  meta(c, (unsigned)metadatalen, get((unsigned)metadatalen));
	  break;
	}
      }
      seek(metadatapos + metadatalen);
    }
    break;
  default:
    {
      if (midicode < 0)
	return 0;
      if (midicode < 0x80)
      {
      char msg[30];

	sprintf(msg, "illegal midi command %02X", midicode);
	error(msg);
	return 0;
      }
      int channel = midicode & 0x0F;
      int cmd = midicode & 0xF0;

      switch(cmd)
      {
      case 0x80:
      case 0x90:
	{
	unsigned char* c;

	  lastcode_ = midicode;
	  c = get(2); if (!c) return 0;
	  if (options_ & OPTION_NONOTEEVENTS)
	    event(midicode, 2, c);
	  else
	  {
	    if (cmd == 0x80 || c[1] == 0)
	      noteoff(channel, c[0], c[1]);
	    else
	      noteon(channel, c[0], c[1]);
	  }
	}
	break;
      case 0xA0:
	{
	unsigned char* p = get(2); if (!p) return 0;

	  lastcode_ = midicode;

	  if (options_ & OPTION_NOPOLYEVENTS)
	    event(midicode, 2, p);
	  else
	  {
	    polyaftertouch(channel, p[0], p[1]);
	  }
	}
	break;
      case 0xB0:
	{
	unsigned char* p = get(2); if (!p) return 0;

	  if (p[1] >= 0x80)
	    warning("invalid control value used");

	  lastcode_ = midicode;
	  if (options_ & OPTION_NOCONTROLEVENTS)
	    event(midicode, 2, p);
	  else if (options_ & OPTION_NOCONTROLS)
	    control(channel, p[0], p[1]);
	  else
	    switch(p[0])
	    {
	    case ctrl_highbank: highbank(channel, p[1]); break;
	    case ctrl_wheel: wheel(channel, p[1]); break;
	    case ctrl_breath: breath(channel, p[1]); break;
	    case ctrl_foot: foot(channel, p[1]); break;
	    case ctrl_portamentotime: portamentotime(channel, p[1]); break;
	    case ctrl_data: data(channel, p[1]); break;
	    case ctrl_volume: volume(channel, p[1]); break;
	    case ctrl_balance: balance(channel, p[1]); break;
	    case ctrl_expression: expression(channel, p[1]); break;
	    case ctrl_lowbank: lowbank(channel, p[1]); break;
	    case ctrl_hold: hold(channel, p[1]); break;
	    case ctrl_reverb: reverb(channel, p[1]); break;
	    case ctrl_chorus: chorus(channel, p[1]); break;
	    case ctrl_datainc: datainc(channel, p[1]); break;
	    case ctrl_datadec: datadec(channel, p[1]); break;
	    case ctrl_lowrpn: lowrpn(channel, p[1]); break;
	    case ctrl_highrpn:
	      {
	      unsigned char *c = need(8);

		if (c &&
		  c[0] == 0 && c[1] == midicode && c[2] == ctrl_lowrpn && c[3] == 0 &&
		  c[4] == 0 && c[5] == midicode && c[6] == ctrl_data)
		{
		  c = get(8);
		  pitchbendrange(channel, c[7]);
		}
		else
		  highrpn(channel, p[1]);
		break;
	      }
	    default:
	      control(channel, p[0], p[1]);
	      break;
	    }
	  break;
	}

      case 0xC0:
	{
	unsigned char* p = get(1); if (!p) return 0;

	  if (*p >= 0x80)
	    warning("invalid program used");
	  lastcode_ = midicode;
	  if (options_ & OPTION_NOPROGRAMEVENTS)
	    event(midicode, 1, p);
	  else
	    program(channel, p[0]);
	}
	break;
      case 0xD0:
	{
	unsigned char* p = get(1); if (!p) return 0;

	  lastcode_ = midicode;
	  if (options_ & OPTION_NOAFTERTOUCHEVENTS)
	    event(midicode, 1, p);
	  else
	    aftertouch(channel, p[0]);
	}
	break;
      case 0xE0:
	{
	unsigned char* p = get(2); if (!p) return 0;
	unsigned val = unsigned(p[0]) + (unsigned(p[1]) << 7);

	  lastcode_ = midicode;
	  if (options_ & OPTION_NOPITCHBENDEVENTS)
	    event(midicode, 2, p);
	  else
	    pitchbend(channel, val);
	}
	break;
      default:
	{
	char msg[30];

	  sprintf(msg, "unexpected command byte %02X", midicode);
	  error(msg);
	  return 0;
	}
      }
    }
    break;
  }
  return (int)(curpos_ - pos_);
}

int MidiRead::runtrack(int trackno)
{
unsigned long trackpos = curpos_, trackend;

  if (exit_)
    return 0;

  skiptrack_ = 0;
  curunit_ = 0;
  curms_ = currest_ = 0;
  lastcode_ = -1;
  pos_ = curpos_;

  if (getlong() != MTrk)
  {
    error("missing midi track MTrk");
    return 0;
  }
  tracklen_ = getlong();
  track(trackno, tracklen_, curchannel_ = scanchannel(tracklen_));
  trackpos = curpos_;
  trackend = trackpos + tracklen_;
  lastcode_ = -1;
  if ((options_ & OPTION_NOEVENTS) == 0)
  while (!skiptrack_ && curpos_ < trackpos + tracklen_)
  {
    int newpercent = (int)((curpos_ * 100) / midilength());
    if (newpercent != percent_)
      percent(percent_ = newpercent);

    unsigned long delta = getdelta();
    if ( delta >= NOTREALISTIC_PAUSE )
    {
      unrealisticpause(delta);
      skiptrack_ = 1;
      continue;
    }
    time(delta);
    if (exit_)
      return 0;
    curunit_ += delta;
    // warning: MidiRead time calculation is only valid for format 0 files
    // use MidiSerial to calculate time for any midi format
    calctime(delta, curms_, currest_);

    if (runevent(trackend) <= 0)
    {
      skiptrack_ = 0;
      return 0;
    }
    if (exit_)
      return 0;
  }
  skiptrack_ = 0;
  seek(trackend);
  pos_ = curpos_;
  endtrack(trackno);
  return 1;
}

void MidiRead::setchannel(int channel)
{
  assert(channel >= -1 && channel <= 15);
  curchannel_ = channel;
}

long MidiRead::readsyseventlength(unsigned long maxlen)
{
unsigned n = 0;
unsigned char* c;
long savepos = curpos_;
long datapos = curpos_;
long len;

  n = bufavail(curpos_);
  if (maxlen < n)
    n = (unsigned)maxlen;
  c = need(n);
  if (!c)
      return 0;

  if (c[0] < 0x80)
  {
    // short sysex 0..127 bytes
    len = c[0];
    if (n >= len+1)
    {
      if (c[(int)len] == 0xF7)
      {
	get(1);
	return len; // len exclusive length information, inclusive 0xf7
      }
    }
    datapos += 1;
  }
  else if (n >= 2 && c[1] < 0x80)
  {
    // 128..16383 bytes
    len = (int(c[0] & 0x7f) << 7) + c[1];
    if (n >= len + 2)
    {
      if (c[(int)len+1] == 0xF7)
      {
	get(2);
	return len;  // len exclusive length information, inclusive 0xf7
      }
    }
    datapos += 2;
  }
  else if (n >= 3 && c[2] < 0x80)
  {
    // 16384 bytes
    len = (long(c[0] & 0x7f) << 14) + (long(c[1] & 0x7f) << 7) + c[2];
    datapos += 3;
  }
  else if (n >= 4 && c[3] < 0x80)
  {
    // 16384 bytes
    len = (long(c[0] & 0x7f) << 21) + (long(c[1] & 0x7f) << 14) + (long(c[2] & 0x7f) << 7) + c[3];
    datapos += 4;
  }
  if (/*len > n && */len <= maxlen)
  {
    seek(datapos+len-1);
    c = need(1);
    if (c && *c == 0xF7)
    {
      seek(datapos);
      return len;
    }
  }

  // sysex events without length information?
  datapos = savepos;
  seek(datapos);
  len = 0;
  while (len < maxlen)
  {
    c = get(1);
    if (!c)
      break;
    len++;
    if (*c == 0xF7)
    {
      seek(datapos);
      return len;
    }
  }
  // eox not found
  seek(savepos);
  return 0;
}

int MidiRead::scanchannel(unsigned long maxlen)
{
  if (options_ & OPTION_NOEVENTS)
    return NOCHANNEL;
unsigned n = 0;
unsigned char* c;
int firstchannel = NOCHANNEL;
int channel, code;
long savepos = curpos_, endpos;
int lastcode = -1;

  n = bufavail(curpos_);
  if (maxlen < n)
    n = (unsigned)maxlen;
  c = need(n);
  if (!c)
    return -1;

  endpos = curpos_ + n;
  while (curpos_ < endpos)
  {
    channel = NOCHANNEL;
    getdelta();
    c = need(1);
    if (!c || *c >= 0x80 || lastcode < 0)
      code = getbyte();
    else
      code = lastcode;
    switch(code & 0xF0)
    {
    case 0xF0:
      switch(code)
      {
      case 0xFF:
	getbyte();
	skip(getdelta());
	break;
      case 0xf0: // sysex
	{
	  long len = readsyseventlength(endpos-curpos_);
          if (len <= 0)
            goto endscan;
	  if (!skip(len))
	    goto endscan;
	}
	break;
      case 0xf2: get(2); break;
      case 0xf3: getbyte(); break;
      case 0xf6:
      case 0xf8:
      case 0xfa:
      case 0xfb:
      case 0xfc:
      case 0xfe:
	break;
      default:
	goto endscan;
      }
      break;
    case 0x80:
    case 0x90:
    case 0xA0:
    case 0xB0:
    case 0xE0:
      channel = code & 15;
      get(2);
      break;
    case 0xC0:
    case 0xD0:
      channel = code & 15;
      getbyte();
      break;
    default:
      goto endscan;
    }
    if (code < 0xf0)
      lastcode = code;
    if (channel >= 0)
    {
      if (firstchannel < 0)
	firstchannel = channel;
      else if (channel != firstchannel)
      {
	firstchannel = MULTICHANNEL;
	break;
      }
    }
  }
endscan:
  seek(savepos);
  return firstchannel;
}

int MidiRead::getbyte()
{
unsigned char* c = get(1);

  if (c)
    return *c;
  return -1;
}

unsigned MidiRead::getword()
{
unsigned char* c = get(2);
unsigned n = 0;

  if (c)
  {
    n = *c++;
    n = (n << 8) + *c++;
  }
  return n;
}

unsigned long MidiRead::gettri()
{
unsigned char* c = get(3);
unsigned long n = 0;

  if (c)
  {
    n = *c++;
    n = (n << 8) + *c++;
    n = (n << 8) + *c++;
  }
  return n;
}

unsigned long MidiRead::getlong()
{
unsigned char* c = get(4);
unsigned long n = 0;

  if (c)
  {
    n = *c++;
    n = (n << 8) + *c++;
    n = (n << 8) + *c++;
    n = (n << 8) + *c++;
  }
  return n;
}

unsigned long MidiRead::getdelta()
{
unsigned long n = 0;
int i = 0, c;

  curdeltalen_ = 0;
  for (i = 0; i < 4; i++)
  {
    c = getbyte();
    if (c < 0)
    {
      error("unexpected end of file");
      return 0;
    }
    curdeltalen_++;
    n = (n << 7) + (c & 0x7f);
    if ((c & 0x80) == 0)
      break;
  }
  return n;
}

unsigned char* MidiRead::need(unsigned n)
{
  return MidiBuffer::need(curpos_, n);
}

unsigned char* MidiRead::get(unsigned n)
{
unsigned char* s;

  s = need(n);
  if (s)
    curpos_ += n;
  else if (bufsize() == 0)
    error("out of memory");
  else if (n > bufsize())
   warning("midi event larger than internal bufsize ignored");
  else if (n > 0)
  {
    error("unexpected end of file");
    skiptrack_ = 1;
  }
  return s;
}

int MidiRead::skip(long len)
{
  if (len < 0 || curpos_ + len > midilength())
    return 0;
  seek(curpos_ + len);
  return 1;
}

void MidiRead::seek(long pos)
{
  if (pos < 0)
    return;
  curpos_ = pos;
}

unsigned long MidiRead::microsec(unsigned long units, unsigned long msperbeat)
{
  assert(unitsperbeat_ != 0);   // call runhead() or run() first!

  if (units > msperbeat)
    return (units / unitsperbeat_) * msperbeat;
  else
    return units * (msperbeat / unitsperbeat_);
}


long MidiRead::units(unsigned long microsec, unsigned long msperbeat)
{
  assert(unitsperbeat_ != 0);   // call runhead() or run() first!
  assert(msperbeat > 0);  // invalid tempo!
  int unitsperbeat = unitsperbeat_;
  while ((msperbeat & 1) == 0)
  {
    if ((unitsperbeat & 1) == 0)
      unitsperbeat >>= 1;
    else if ((microsec & 1) == 0)
      microsec >>= 1;
    else
      break;
    msperbeat >>= 1;
  }
  if (microsec >= 0x10000L)
    return (microsec / msperbeat) * unitsperbeat;
  else
    return (microsec * unitsperbeat) / msperbeat;
}


static char* GMProg[128] =
{
  "Piano", "BritePiano", "HammerPiano", "HonkeyTonk", "NewTines", "DigiPiano", "Harpsicord", "Clav",
  "Celesta", "Glocken", "MusicBox", "Vibes", "Marimba", "Xylophon", "Tubular", "Santur",
  "FullOrgan", "PercOrgan", "BX-3Organ", "ChurchPipe", "Positive", "Musette", "Harmonica", "Tango",
  "ClassicGtr", "A.Guitar", "JazzGuitar", "CleanGtr", "MuteGuitar", "OverDrive", "DistGuitar", "RockMonics",
  "JazzBass", "DeepBass", "PickBass", "FretLess", "SlapBass1", "SlapBass2", "SynthBass1", "SynthBass2",
  "Violin", "Viola", "Cello", "ContraBass", "TremoloStr", "Pizzicato", "Harp", "Timpani",
  "Marcato", "SlowString", "AnalogPad", "StringPad", "Choir", "DooVoice", "Voices", "OrchHit",
  "Trumpet", "Trombone", "Tuba", "MutedTrumpet", "FrenchHorn", "Brass", "SynBrass1", "SynBrass2",
  "SopranoSax", "AltoSax", "TenorSax", "BariSax", "SweetOboe", "EnglishHorn", "BasoonOboe", "Clarinet",
  "Piccolo", "Flute", "Recorder", "PanFlute", "Bottle", "Shakuhachi","Whistle", "Ocarina",
  "SquareWave", "SawWave", "SynCalinope", "SynChiff", "Charang", "AirChorus", "Rezzo4ths", "Bass&Lead",
  "Fantasia", "WarmPad", "PolyPad", "GhostPad", "BowedGlas", "MetalPad", "HaloPad", "Sweep",
  "IceRain", "SoundTrack", "Crystal", "Atmosphere", "Brightness", "Goblin", "EchoDrop", "StarTheme",
  "Sitar", "Banjo", "Shamisen", "Koto", "Kalimba","Scotland","Fiddle", "Shanai",
  "MetalBell", "Agogo", "SteelDrums", "Woodblock", "Taiko", "Tom", "SynthTom", "RevCymbal",
  "FretNoise", "NoiseChiff", "Seashore", "Birds", "Telephone", "Helicopter", "Stadium!!", "GunShot"
};

const char* MidiRead::notename(unsigned char note)
{
static char name[5];
char* s = name;

  switch(note % 12)
  {
  case 0: *s++ = 'c'; break;
  case 1: *s++ = 'c'; *s++ = '#'; break;
  case 2: *s++ = 'd'; break;
  case 3: *s++ = 'd'; *s++ = '#'; break;
  case 4: *s++ = 'e'; break;
  case 5: *s++ = 'f'; break;
  case 6: *s++ = 'f'; *s++ = '#'; break;
  case 7: *s++ = 'g'; break;
  case 8: *s++ = 'g'; *s++ = '#'; break;
  case 9: *s++ = 'a'; break;
  case 10: *s++ = 'a'; *s++ = '#'; break;
  case 11: *s++ = 'b'; break; // former 'h': German language only
  }

  sprintf(s, "%d", (note / 12)-1);  // octave  (assuming Piano C4 is 60)
  return (const char*) name;
}


const char* MidiRead::progname(int n, int channel)
{
static char defname[10] = "";

  if (channel == 9) // drum programs
  {
    switch(n)
    {
    case 0:    return "Dr1";
    case 0x10: return "Dr2";
    case 0x19: return "Dr3";
    case 0x20: return "Dr4";
    case 0x28: return "Dr5";
    case 0x40: return "Dr6";
    case 0x18: return "Dr7";
    case 0x30: return "Dr8";
    }
  }
  else if (n >= 0 && n <= 127)
    return GMProg[n];
def:
  sprintf(defname, "%d", n);
  return (const char*)defname;
}

void MidiRead::head(unsigned /*version*/, unsigned /*tracks*/, unsigned /*unitperbeat*/)
{
}

void MidiRead::track(int /*trackno*/, long /*length*/, int /*channel*/)
{
}

void MidiRead::endtrack(int /*trackno*/)
{
}

void MidiRead::event(int /*what*/, unsigned /*len*/, unsigned char* /*data*/)
{
}

void MidiRead::event(int /*what*/, FILE* /*f*/, long /*datapos*/, long /*datalen*/)
{
}

void MidiRead::seqnumber(unsigned int /*seqno*/)
{
}

void MidiRead::smpteofs(int /*mode*/, int /*hour*/, int /*min*/, int /*sec*/, int /*frame*/, int /*fracframe*/)
{
}

void MidiRead::key(int /*signature*/, int /*isminor*/)
{
}

void MidiRead::prefixchannel(unsigned char /*channel*/)
{
}

void MidiRead::prefixport(unsigned char /*port*/)
{
}

void MidiRead::text(int /*what*/, unsigned /*len*/, char* /*whattext*/, unsigned char* /*txt*/)
{
}

void MidiRead::meta(int /*what*/, unsigned /*len*/, unsigned char* /*data*/)
{
}

void MidiRead::meta(int /*what*/, FILE* /*f*/, long /*metadatapos*/, long /*metadatalen*/)
{
}

void MidiRead::end()
{
}

void MidiRead::tact(int /*nom*/, int /*denom*/, int /*v1*/, int /*v2*/)
{
}

void MidiRead::tempo(unsigned long /*ticks*/)
{
}

void MidiRead::program(int /*channel*/, int /*program*/)
{
}

void MidiRead::control(int /*channel*/, int /*what*/, int /*value*/)
{
}

void MidiRead::highbank(int channel, int val)
{
  control(channel, ctrl_highbank, val);
}

void MidiRead::wheel(int channel, int val)
{
  control(channel, ctrl_wheel, val);
}

void MidiRead::breath(int channel, int val)
{
  control(channel, ctrl_breath, val);
}

void MidiRead::foot(int channel, int val)
{
  control(channel, ctrl_foot, val);
}

void MidiRead::portamentotime(int channel, int val)
{
  control(channel, ctrl_portamentotime, val);
}

void MidiRead::data(int channel, int val)
{
  control(channel, ctrl_data, val);
}

void MidiRead::volume(int channel, int val)
{
  control(channel, ctrl_volume, val);
}

void MidiRead::balance(int channel, int val)
{
  control(channel, ctrl_balance, val);
}

void MidiRead::expression(int channel, int val)
{
  control(channel, ctrl_expression, val);
}

void MidiRead::lowbank(int channel, int val)
{
  control(channel, ctrl_lowbank, val);
}

void MidiRead::hold(int channel, int val)
{
  control(channel, ctrl_hold, val);
}

void MidiRead::reverb(int channel, int val)
{
  control(channel, ctrl_reverb, val);
}

void MidiRead::chorus(int channel, int val)
{
  control(channel, ctrl_chorus, val);
}

void MidiRead::datainc(int channel, int val)
{
  control(channel, ctrl_datainc, val);
}

void MidiRead::datadec(int channel, int val)
{
  control(channel, ctrl_datadec, val);
}

void MidiRead::lowrpn(int channel, int val)
{
  control(channel, ctrl_lowrpn, val);
}

void MidiRead::highrpn(int channel, int val)
{
  control(channel, ctrl_highrpn, val);
}

void MidiRead::pitchbendrange(int channel, int halfnotes)
{
  highrpn(channel, 0);
  time(0);
  lowrpn(channel, 0);
  time(0);
  data(channel, halfnotes);
}

void MidiRead::noteon(int /*channel*/, int /*note*/, int /*vel*/)
{
}

void MidiRead::noteoff(int /*channel*/, int /*note*/, int /*vel*/)
{
}

void MidiRead::time(unsigned long /*ticks*/)
{
}

void MidiRead::pitchbend(int /*channel*/, int /*val*/)
{
}

void MidiRead::polyaftertouch(int /*channel*/, int /*note*/, int /*val*/)
{
}

void MidiRead::aftertouch(int /*channel*/, int /*val*/)
{
}

void MidiRead::songpos(unsigned /*pos*/)
{
}

void MidiRead::songselect(unsigned char /*song*/)
{
}

void MidiRead::tunerequest()
{
}

void MidiRead::timingclock()
{
}

void MidiRead::start()
{
}

void MidiRead::cont()
{
}

void MidiRead::stop()
{
}

void MidiRead::activesense()
{
}

void MidiRead::sysex(unsigned /*syslen*/, unsigned char* /*sysdata*/)
{
}

void MidiRead::sysex(FILE* /*f*/, long /*sysdatapos*/, long /*sysdatalen*/)
{
}

void MidiRead::gmreset()
{
}

void MidiRead::gsreset()
{
}

void MidiRead::gsexit()
{
}

void MidiRead::xgreset()
{
}

void MidiRead::endmidi()
{
}

void MidiRead::percent(int /*perc*/)
{
}

void MidiRead::unrealisticpause(unsigned long /*units*/)
{
  warning("Unrealistic large pause found");
}

// calculate time that is units after current time, assuming current speed and resolution
void MidiRead::calctime(unsigned long units, unsigned long& nextms, unsigned long& nextrest)
{
    nextms = curms_;
    nextrest = currest_;

    if (units == 0 || timediv_ == 0)  // cannot calc time (track head not parsed)
      return;
    unsigned long vms = microsecperbeat_ / timediv_;
    unsigned long vrest = microsecperbeat_ % timediv_;
    if (units >= NOTREALISTIC_PAUSE )
    {
      nextms = units * vms;
      nextrest = 0;
    }
    else
    {
      while (units-- > 0)
      {
	    nextms += vms;
	    nextrest += vrest;
	    while (nextrest >= timediv_)
	    {
	      nextms++;
	      nextrest -= timediv_;
	    }
      }
    }
}

// calc unit at ms msrest that is in same speed range as current unit
unsigned long MidiRead::calcunit(unsigned long ms, unsigned long msrest)
{
unsigned long diff, diffrest;
char ge;

  if (ms > curms_ || (ms == curms_ && msrest >= currest_))
  {
    diff = ms - curms_;
    if (msrest >= currest_)
      diffrest = msrest - currest_;
    else
    {
      diffrest = msrest + timediv_ - currest_;
      diff--;
    }
    ge = 1;
  }
  else
  {
    diff = curms_ - ms;
    if (currest_ >= msrest)
      diffrest = currest_ - msrest;
    else
    {
      diffrest = currest_ + timediv_ - msrest;
      diff--;
    }
    ge = 0;
  }
  unsigned long units = 0;
  while (diff > 0 || diffrest >= microsecperbeat_)
  {
    if (diff > 0)
    {
      diff--;
      diffrest += timediv_;
    }
    if (diffrest >= microsecperbeat_)
    {
      units++;
      diffrest -= microsecperbeat_;
    }
  }
  return ge ? curunit_ + units : curunit_ - units;
}

FILE* MidiBuffer::getf()
{
  return f_;
}

// class MidiWrite

const char* MidiWrite::copyright()
{
  return (const char*)::copyright;
}

MidiWrite::MidiWrite(const char* filename) : MidiBuffer(filename, 0, MIDI_CREATE)
{
  trackpos_ = -1;
  curpos_ = 0;
  trackchannel_ = -1;

  trackcount_ = 0;
  curunit_ = curdelta_ = 0;
  lastcode_ = -1;
  unitsperbeat_ = 0;
}

MidiWrite::~MidiWrite()
{
  if (trackcount_ > 0)
  {
    seek(10);
    putword(trackcount_);
  }
  if (trackpos_ > 0)
    endtrack();
}

void MidiWrite::head(int version, int tracks, unsigned unitperbeat)
{
  seek(0);
  putlong(MThd);
  putlong(6);
  putword(version);
  putword(tracks);  // unknown
  putword(unitsperbeat_ = unitperbeat);
}

void MidiWrite::track()
{
  if (trackpos_ > 0)
    endtrack();
  endtrack_ = 0;
  lastcode_ = -1;
  curunit_ = curdelta_ = 0;
  seek(trackpos_ = midilength());
  putlong(MTrk);
  putlong(0); // unknown yet
  trackcount_++;
}

int MidiWrite::trackcount()
{
  return trackcount_;
}

void MidiWrite::endtrack()
{
  seek(midilength());
  if (!endtrack_)
     end();
  if (trackpos_ <= 0)
    return;
  seek(trackpos_+4);
  putlong(midilength() - trackpos_ - 8);
  trackpos_ = 0;
}

void MidiWrite::event(int what, unsigned len, unsigned char* data)
{
  puttime();
  putcode(what);
  put(len, data);
}

void MidiWrite::event(int what, FILE* f, long datapos, long datalen)
{
  puttime();
  putcode(what);
  put(f, datapos, datalen);
}

void MidiWrite::prefixchannel(unsigned char channel)
{
  meta(0x20, 1, &channel);
}

void MidiWrite::prefixport(unsigned char port)
{
  meta(0x21, 1, &port);
}

void MidiWrite::text(int what, unsigned len, unsigned char* txt)
{
  if (len == 0)
    len = strlen((char*)txt);
  meta(what, len, txt);
}

void MidiWrite::meta(int what, unsigned len, unsigned char* data)
{
  puttime();
  putcode(0xff);
  putbyte(what);
  putdelta(len);
  put(len, data);
}

void MidiWrite::meta(int what, FILE* f, long metadatapos, long metadatalen)
{
  puttime();
  putcode(0xff);
  putbyte(what);
  putdelta(metadatalen);
  put(f, metadatapos, metadatalen);
}

void MidiWrite::end()
{
  if (endtrack_)  // don't need end of track event twice
    return;
  endtrack_ = 1;
  meta(0x2f, 0, 0);
}

void MidiWrite::tact(int nom, int denom, int v1, int v2)
{
int log2denom;

  switch(denom)
  {
  case 1:    log2denom = 0; break;
  case 2:    log2denom = 1; break;
  case 4:    log2denom = 2; break;
  case 8:    log2denom = 3; break;
  case 16:   log2denom = 4; break;
  case 32:   log2denom = 5; break;
  case 64:   log2denom = 6; break;
  case 128:  log2denom = 7; break;
  case 256:  log2denom = 8; break;
  default:
    log2denom = 2;
    assert((1 << log2denom) == denom);
  }
  puttime();
  putcode(0xff);
  putbyte(0x58);
  putbyte(4);
  putbyte(nom);
  putbyte(log2denom);
  putbyte(v1);
  putbyte(v2);
}

void MidiWrite::seqnumber(unsigned int seqno)
{
  puttime();
  putcode(0xff);
  putbyte(0x00);
  putbyte(2);
  putword(seqno);
}

void MidiWrite::smpteofs(int mode, int hour, int min, int sec, int frame, int fracframe)
{
  puttime();
  putcode(0xff);
  putbyte(0x54);
  putbyte(5);
  putbyte((mode << 5) + (hour & 0x1f));
  putbyte(min);
  putbyte(sec);
  putbyte(frame);
  putbyte(fracframe);
}

void MidiWrite::key(int signature, int isminor)
{
  puttime();
  putcode(0xff);
  putbyte(0x59);
  putbyte(2);
  putbyte((signed char)signature);
  putbyte((signed char)isminor);
}

void MidiWrite::tempo(unsigned long ticks)
{
  puttime();
  putcode(0xff);
  putbyte(0x51);
  putbyte(3);
  puttri(ticks);
}

void MidiWrite::program(int channel, int prg)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0xC0 + channel);
  putbyte(prg);
}

void MidiWrite::control(int channel, int what, int val)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0xB0 + channel);
  putbyte(what);
  putbyte(val);
}

void MidiWrite::highbank(int channel, int val)
{
  control(channel, ctrl_highbank, val);
}

void MidiWrite::wheel(int channel, int val)
{
  control(channel, ctrl_wheel, val);
}

void MidiWrite::breath(int channel, int val)
{
  control(channel, ctrl_breath, val);
}

void MidiWrite::foot(int channel, int val)
{
  control(channel, ctrl_foot, val);
}

void MidiWrite::portamentotime(int channel, int val)
{
  control(channel, ctrl_portamentotime, val);
}

void MidiWrite::data(int channel, int val)
{
  control(channel, ctrl_data, val);
}

void MidiWrite::volume(int channel, int val)
{
  control(channel, ctrl_volume, val);
}

void MidiWrite::balance(int channel, int val)
{
  control(channel, ctrl_balance, val);
}

void MidiWrite::expression(int channel, int val)
{
  control(channel, ctrl_expression, val);
}

void MidiWrite::lowbank(int channel, int val)
{
  control(channel, ctrl_lowbank, val);
}

void MidiWrite::hold(int channel, int val)
{
  control(channel, ctrl_hold, val);
}

void MidiWrite::reverb(int channel, int val)
{
  control(channel, ctrl_reverb, val);
}

void MidiWrite::chorus(int channel, int val)
{
  control(channel, ctrl_chorus, val);
}

void MidiWrite::datainc(int channel, int val)
{
  control(channel, ctrl_datainc, val);
}

void MidiWrite::datadec(int channel, int val)
{
  control(channel, ctrl_datadec, val);
}

void MidiWrite::lowrpn(int channel, int val)
{
  control(channel, ctrl_lowrpn, val);
}

void MidiWrite::highrpn(int channel, int val)
{
  control(channel, ctrl_highrpn, val);
}

void MidiWrite::noteon(int channel, int note, int vel)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0x90+channel);
  putbyte(note);
  putbyte(vel);
}

void MidiWrite::noteoff(int channel, int note, int vel)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  if (vel != 0 || lastcode_ < 0 || (lastcode_ & 0xF0) != 0x90)
    putcode(0x80+channel);
  else
    putcode(0x90+channel);  // vel == 0!
  putbyte(note);
  putbyte(vel);
}

void MidiWrite::time(unsigned long ticks)
{
  if ( ticks >= NOTREALISTIC_PAUSE )
    unrealisticpause(ticks);
  curdelta_ += ticks;
  curunit_ += ticks;
}

void MidiWrite::cleardelta()
{
  curunit_ -= curdelta_;
  curdelta_ = 0;
}

void MidiWrite::pitchbend(int channel, int val)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0xE0 + channel);
  putbyte(val & 0x7F);
  putbyte((val >> 7) & 0x7F);
}

void MidiWrite::polyaftertouch(int channel, int note, int val)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0xA0 + channel);
  putbyte(note);
  putbyte(val);
}

void MidiWrite::aftertouch(int channel, int val)
{
  assert(channel >= 0 && channel < 16);
  puttime();
  putcode(0xD0 + channel);
  putbyte(val);
}

void MidiWrite::songpos(unsigned pos)
{
  puttime();
  putcode(0xF2);
  putbyte(pos & 0x7F);
  putbyte((pos >> 7) & 0x7F);
}

void MidiWrite::songselect(unsigned char song)
{
  puttime();
  putcode(0xF3);
  putbyte(song);
}

void MidiWrite::tunerequest()
{
  puttime();
  putcode(0xf6);
}

void MidiWrite::timingclock()
{
  puttime();
  putcode(0xf8);
}

void MidiWrite::start()
{
  puttime();
  putcode(0xfa);
}

void MidiWrite::cont()
{
  puttime();
  putcode(0xfb);
}

void MidiWrite::stop()
{
  puttime();
  putcode(0xfc);
}

void MidiWrite::activesense()
{
  puttime();
  putcode(0xfe);
}

void MidiWrite::sysex(unsigned syslen, unsigned char* sysdata)
{
  puttime();
  if (sysdata[0] == 0xf0)
  {
    sysdata++; syslen--;
  }
  putcode(0xf0);
  syslen = sysexlen(syslen, sysdata);
  int needeox = (sysdata[syslen-1] != 0xf7);
  int deltalen = syslen;
  if (needeox)
    deltalen++;
  putdelta(deltalen);
  put(syslen, sysdata);
  if (needeox)
    putbyte(0xf7);
}

void MidiWrite::sysex(FILE* f, long sysdatapos, long sysdatalen)
{
  if (!f)
    return;
  puttime();

  long oldpos = ftell(f);
  fseek(f, sysdatapos, SEEK_SET);
  int c = fgetc(f);
  fseek(f, sysdatapos, SEEK_SET);
  if (c == EOF)
    return;
  if (c == 0xf0)
  {
    sysdatapos++; sysdatalen--;
  }
  putcode(0xf0);
  sysdatalen = sysexlen(f, sysdatapos, sysdatalen);
  fseek(f, sysdatapos + sysdatalen-1, SEEK_SET);
  c = fgetc(f);
  fseek(f, sysdatapos, SEEK_SET);
  int needeox = (c != 0xf7);
  long deltalen = sysdatalen;
  if (needeox)
    deltalen++;
  putdelta(deltalen);
  put(f, sysdatapos, sysdatalen);
  if (needeox)
    putbyte(0xf7);
  fseek(f, oldpos, SEEK_SET);
}

void MidiWrite::gmreset()
{
  sysex(0, sysex_gmreset);
}

void MidiWrite::xgreset()
{
  sysex(0, sysex_xgreset);
}

void MidiWrite::gsreset()
{
  sysex(0, sysex_gsreset);
}

void MidiWrite::gsexit()
{
  sysex(0, sysex_gsexit);
}

void MidiWrite::pitchbendrange(int channel, int halfnotes)
{
  highrpn(channel, 0);
  lowrpn(channel, 0);
  data(channel, halfnotes);
}

void MidiWrite::putbyte(unsigned char val)
{
  put(1, &val);
}

void MidiWrite::putcode(unsigned char code)
{
int put;

  assert(code >= 0x80);

  if (compress)
    put = !(code == lastcode_ && code <= 0x9f);
  else
    put = 1;
  if (put)
    putbyte(code);
  lastcode_ = code;
}

static unsigned char c[4];

void MidiWrite::putword(unsigned val)
{
  c[1] = (unsigned char)(val & 0xff); val >>= 8;
  c[0] = (unsigned char)(val & 0xff);
  put(2, c);
}

void MidiWrite::puttri(unsigned long val)
{
  c[2] = (unsigned char)(val & 0xff); val >>= 8;
  c[1] = (unsigned char)(val & 0xff); val >>= 8;
  c[0] = (unsigned char)(val & 0xff);
  put(3, c);
}

void MidiWrite::putlong(unsigned long val)
{
  c[3] = (unsigned char)(val & 0xff); val >>= 8;
  c[2] = (unsigned char)(val & 0xff); val >>= 8;
  c[1] = (unsigned char)(val & 0xff); val >>= 8;
  c[0] = (unsigned char)(val & 0xff);
  put(4, c);
}

void MidiWrite::putdelta(unsigned long val)
{
  int i = 0, j = 3;
  while (i < 4)
  {
    c[j] = val & 0x7F;
    if (j < 3)
      c[j] |= 0x80;
    val >>= 7;
    i++;
    if (!val)
      break;
    j--;
  }
  put(i, c+j);
}

void MidiWrite::puttime()
{
  putdelta(curdelta_);
  curdelta_ = 0;
}

void MidiWrite::put(unsigned len, unsigned char* c)
{
  if (len == 0 || !c)
    return;
  unsigned n = bufavail(curpos_);
  while (len > 0)
  {
    if (len < n)
      n = len;
    unsigned char* buf = need(curpos_, n);
    if (!buf)
      return;
    memcpy(buf, c, n);
    c += n;
    curpos_ += n;
    len -= n;
  }
}

void MidiWrite::put(FILE* f, long datapos, long datalen)
{
long oldpos = ftell(f);
unsigned char buf[256];
int n;

  fseek(f, datapos,SEEK_SET);
  while (datalen > 0)
  {
    n = sizeof(buf);
    if (datalen < n)
      n = (int)datalen;
    n = fread(buf, 1, n, f);
    if (n <= 0)
      break;
    put(n, buf);
    datalen -= n;
    datapos += n;
  }
  fseek(f, oldpos, SEEK_SET);
}

void MidiWrite::seek(long pos)
{
  assert(pos >= 0 && pos <= midilength());
  curpos_ = pos;
}

void MidiWrite::unrealisticpause(unsigned long /*tick*/)
{
  warning("generating unrealistic large pause");
}

int MidiWrite::unitsperquarter()
{
  return unitsperbeat_;
}

MidiCopy::MidiCopy(const char* filename, FILE* f) : MidiRead(filename, f)
{
  dest_ = NULL;
  for (int c = 0; c < 16; c++)
    mapchannel_[c] = c;        // no change
}

void MidiCopy::head(unsigned version, unsigned /*tracks*/, unsigned unitperbeat)
{
  if (dest_)
    dest_->head(version, 0, unitperbeat);
}

void MidiCopy::track(int /*trackno*/, long /*length*/, int /*channel*/)
{
  if (dest_)
    dest_->track();
}

void MidiCopy::endtrack(int /*trackno*/)
{
  if (dest_)
    dest_->endtrack();
}

void MidiCopy::event(int what, unsigned len, unsigned char* data)
{
  if (dest_)
    dest_->event(what, len, data);
}

void MidiCopy::event(int what, FILE* f, long datapos, long datalen)
{
  if (dest_)
    dest_->event(what, f, datapos, datalen);
}


void MidiCopy::seqnumber(unsigned int seqno)
{
  if (dest_)
    dest_->seqnumber(seqno);
}

void MidiCopy::smpteofs(int mode, int hour, int min, int sec, int frame, int fracframe)
{
  if (dest_)
    dest_->smpteofs(mode, hour, min, sec, frame, fracframe);
}

void MidiCopy::key(int signature, int isminor)
{
  if (dest_)
    dest_->key(signature, isminor);
}

void MidiCopy::prefixchannel(unsigned char channel)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->prefixchannel(mapchannel_[channel]);
}

void MidiCopy::prefixport(unsigned char port)
{
  if (dest_)
    dest_->prefixport(port);
}

void MidiCopy::text(int what, unsigned len, char* /*whattext*/, unsigned char* txt)
{
  if (dest_)
    dest_->text(what, len, txt);
}

void MidiCopy::meta(int what, unsigned len, unsigned char* data)
{
  if (dest_)
    dest_->meta(what, len, data);
}

void MidiCopy::meta(int what, FILE* f, long metadatapos, long metadatalen)

{
  if (dest_)
    dest_->meta(what, f, metadatapos, metadatalen);
}

void MidiCopy::end()
{
  if (dest_)
    dest_->end();
}

void MidiCopy::tact(int nom, int denom, int v1, int v2)
{
  if (dest_)
    dest_->tact(nom, denom, v1,v2);
}

void MidiCopy::tempo(unsigned long ticks)
{
  if (dest_)
    dest_->tempo(ticks);
}

void MidiCopy::program(int channel, int program)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->program(mapchannel_[channel], program);
}

void MidiCopy::control(int channel, int what, int value)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->control(mapchannel_[channel], what, value);
}

void MidiCopy::highbank(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->highbank(mapchannel_[channel], val);
}

void MidiCopy::wheel(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->wheel(mapchannel_[channel], val);
}

void MidiCopy::breath(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->wheel(mapchannel_[channel], val);
}

void MidiCopy::foot(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->foot(mapchannel_[channel], val);
}

void MidiCopy::portamentotime(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->portamentotime(mapchannel_[channel], val);
}

void MidiCopy::data(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->data(mapchannel_[channel], val);
}

void MidiCopy::volume(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->volume(mapchannel_[channel], val);
}

void MidiCopy::balance(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->balance(mapchannel_[channel], val);
}

void MidiCopy::expression(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->expression(mapchannel_[channel], val);
}

void MidiCopy::lowbank(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->lowbank(mapchannel_[channel], val);
}

void MidiCopy::hold(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->hold(mapchannel_[channel], val);
}

void MidiCopy::reverb(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->reverb(mapchannel_[channel], val);
}
                      
void MidiCopy::chorus(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->chorus(mapchannel_[channel], val);
}

void MidiCopy::datainc(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->datainc(mapchannel_[channel], val);
}

void MidiCopy::datadec(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->datadec(mapchannel_[channel], val);
}


void MidiCopy::noteon(int channel, int note, int vel)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->noteon(mapchannel_[channel], note, vel);
}

void MidiCopy::noteoff(int channel, int note, int vel)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->noteoff(mapchannel_[channel], note, vel);
}

void MidiCopy::time(unsigned long ticks)
{
  if (dest_)
    dest_->time(ticks);
}

void MidiCopy::pitchbend(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->pitchbend(mapchannel_[channel],val);
}

void MidiCopy::polyaftertouch(int channel, int note, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->polyaftertouch(mapchannel_[channel], note,  val);
}

void MidiCopy::aftertouch(int channel, int val)
{
  if (dest_ && mapchannel_[channel] >= 0)
    dest_->aftertouch(mapchannel_[channel],  val);
}

void MidiCopy::songpos(unsigned pos)
{
  if (dest_)
    dest_->songpos(pos);
}

void MidiCopy::songselect(unsigned char song)
{
  if (dest_)
    dest_->songselect(song);
}

void MidiCopy::tunerequest()
{
  if (dest_)
    dest_->tunerequest();

}

void MidiCopy::timingclock()
{
  if (dest_)
     dest_->timingclock();
}

void MidiCopy::start()
{
  if (dest_)
     dest_->start();
}

void MidiCopy::cont()
{
  if (dest_)
     dest_->cont();
}

void MidiCopy::stop()
{
  if (dest_)
     dest_->stop();
}

void MidiCopy::activesense()
{
  if (dest_)
     dest_->activesense();
}

void MidiCopy::sysex(unsigned syslen, unsigned char* sysdata)
{
  if (dest_)
     dest_->sysex(syslen, sysdata);
}

void MidiCopy::sysex(FILE* f, long sysdatapos, long sysdatalen)
{
  if (dest_)
     dest_->sysex(f, sysdatapos, sysdatalen);
}

void MidiCopy::xgreset()
{
  if (dest_)
     dest_->xgreset();
}

void MidiCopy::gmreset()
{
  if (dest_)
     dest_->gmreset();
}

void MidiCopy::gsreset()
{
  if (dest_)
     dest_->gsreset();
}

void MidiCopy::gsexit()
{
  if (dest_)
     dest_->gsexit();
}

void MidiCopy::setoutput(MidiWrite* dest)
{
  assert(dest != NULL && dest->getf() != NULL); // need a valid MidiWrite instance
  dest_ = dest;
}

void MidiCopy::stopoutput()
{
  dest_ = NULL; // owner is responsible for deleting the MidiWrite object
}

MidiWrite* MidiCopy::getoutput()
{
  return dest_;
}

void MidiCopy::mapchannel(int channel, int newchannel)
{
  assert(channel >= 0 && channel < 16);
  assert(newchannel >= 0 && newchannel < 16);
  mapchannel_[channel] = newchannel;
}

void MidiCopy::ignorechannel(int channel)
{
  assert(channel >= 0 && channel < 16);
  mapchannel_[channel] = -1;
}

MidiSerial::MidiSerial(const char* filename, FILE* f, char preload)
 : MidiRead(filename, f, preload)
{
  trackpos_ = 0;
  tracktime_ = 0;
  trackendpos_ = 0;
  trackready_ = 0;
  trackstatus_ = 0;
  if (runhead())
  {
    if (tracks_ < 0 || tracks_ >= 256)
      tracks_ = 0;
    else
    {
      trackpos_ = (long*)malloc(tracks_ * sizeof(long));
      trackendpos_ = (long*)malloc(tracks_ * sizeof(long));
      tracktime_= (long*)malloc(tracks_ * sizeof(long));
      trackready_ = (char*)malloc(tracks_ * sizeof(char));
      trackstatus_ = (int*)malloc(tracks_ * sizeof(int));
      if (!trackpos_ || !trackendpos_ || !tracktime_ || !trackready_ || !trackstatus_)
	clear();
    }
  }
}

void MidiSerial::clear()
{
  if (trackpos_)
    free(trackpos_);
  trackpos_ = NULL;
  if (trackendpos_)
    free(trackendpos_);
  trackendpos_ = NULL;
  if (tracktime_)
    free(tracktime_);
  tracktime_ = NULL;
  if (trackready_)
    free(trackready_);
  trackready_= NULL;
  if (trackstatus_)
    free(trackstatus_);
  trackstatus_= NULL;
  tracks_ = 0;
}

MidiSerial::~MidiSerial()
{
  clear();
}


int MidiSerial::run()
{
int saveoptions = options_;
int i;

  if (tracks_ == 1)
    return MidiRead::run();

  if (!trackpos_)
    return 0;

  skiptrack_ = 0;
  pos_ = curpos_ = 0;
  if (!runhead())
    return 0;
   for (i = 0; i < tracks_; i++)
   {
      trackpos_[i] = 0;
      trackendpos_[i] = 0;
      tracktime_[i] = 0;
      trackready_[i] = 0;
      trackstatus_[i] = -1;
   }

  // get track positions and first delta and status
  options_ = OPTION_NOEVENTS;
  int perctrack = 0;
  unsigned long maxtracklen = 0;
  for (i = 0; i < tracks_; i++)
  {
    trackpos_[i] = curpos_+8;
    trackno_ = i+1;
    if (!runtrack(trackno_))
      return 0;
    trackendpos_[i] = trackpos_[i] + tracklen_;

    if (tracklen_ > maxtracklen)
    {
      perctrack = i;
      maxtracklen = tracklen_;
    }
    if (tracklen_ == 0)
      trackready_[i] = 1;
    else
    {
      seek(trackpos_[i]);
      tracktime_[i] = getdelta();
      if ( tracktime_[i] >= NOTREALISTIC_PAUSE )
      {
	    unrealisticpause(tracktime_[i]);
	    skiptrack_ = 1;
      }
      trackpos_[i] = curpos_;
      seek(trackendpos_[i]);
    }
  }
  options_ = saveoptions;

  percent_ = 0;
  curunit_ = 0;
  unsigned long nexttime = 0;
  while (!skiptrack_)
  {
    trackno_ = 0;
    for (i = 0; i < tracks_; i++)
    if (!trackready_[i])
    {
      if (trackno_ == 0 || tracktime_[i] < nexttime)
      {
	    trackno_ = i+1;
	    nexttime = tracktime_[i];
	    if (nexttime == curunit_)
	      break;
      }
    }
    if (trackno_ == 0)
      break;

    time(nexttime - curunit_);
    calctime(nexttime-curunit_, curms_, currest_);

    for (i = 0; i < tracks_; i++)
    while (!trackready_[i] && tracktime_[i] == nexttime)
    {
      if (i == perctrack && maxtracklen > 0)
      {
	    int newpercent = (int)(((trackpos_[i]-(trackendpos_[i]-maxtracklen)) * 100) / maxtracklen);
	    if (newpercent > percent_)
	      percent(percent_ = newpercent);
      }

      trackno_ = i+1;
      lastcode_ = trackstatus_[i];
      seek(trackpos_[i]);
      curunit_ = nexttime;
      if (runevent(trackendpos_[i]) <= 0)
        return 0;
      if (curpos_ >= trackendpos_[i])
	    trackready_[i] = 1;
      else
      {
	    trackstatus_[i] = lastcode_;
	    unsigned long delta = getdelta();
	    tracktime_[i] += delta;
	    if ( delta >= NOTREALISTIC_PAUSE )
	      unrealisticpause(delta);
	    trackpos_[i] = curpos_;
      }
    }
  }

  percent(percent_ = 100);
  endmidi();
  return 1;
}

void MidiSerial::track(int /*trackno*/, long /*length*/, int /*channel*/)
{
}

void MidiSerial::endtrack(int /*trackno*/)
{
}
