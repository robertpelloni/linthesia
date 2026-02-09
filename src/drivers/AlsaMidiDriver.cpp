// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#include "AlsaMidiDriver.h"
#include <iostream>
#include <sstream>

using namespace std;

AlsaMidiDriver::AlsaMidiDriver() :
  m_midi_initiated(false), m_emulate_kb(false), m_alsa_seq(NULL),
  m_local_out(-1), m_local_in(-1), m_anon_in(-1), m_keybd_out(-1),
  m_connected_in_client(-1), m_connected_in_port(-1),
  m_connected_out_client(-1), m_connected_out_port(-1) {
  Init();
}

AlsaMidiDriver::~AlsaMidiDriver() {
  Shutdown();
}

void AlsaMidiDriver::Init() {
  if (m_midi_initiated) return;

  int err = snd_seq_open(&m_alsa_seq, "default", SND_SEQ_OPEN_DUPLEX, 0);
  m_midi_initiated = true;

  if (err < 0) {
    m_alsa_seq = NULL;
    cerr << "WARNING :: could not open MIDI sequencer. No MIDI available" << endl;
    return;
  }

  int ownid = snd_seq_client_id(m_alsa_seq);
  snd_seq_set_client_name(m_alsa_seq, "Linthesia");

  m_local_out = snd_seq_create_simple_port(m_alsa_seq, "Linthesia Output",
                                         SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
                                         SND_SEQ_PORT_TYPE_MIDI_GENERIC);

  m_keybd_out = snd_seq_create_simple_port(m_alsa_seq, "Linthesia Keyboard",
                                         SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
                                         SND_SEQ_PORT_TYPE_MIDI_GENERIC);

  m_local_in = snd_seq_create_simple_port(m_alsa_seq, "Linthesia Input",
                                        SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
                                        SND_SEQ_PORT_TYPE_MIDI_GENERIC);

  m_anon_in = snd_seq_create_simple_port(m_alsa_seq, "Linthesia Annonce Listener",
                                       SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_NO_EXPORT,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
}

void AlsaMidiDriver::Shutdown() {
  if (m_alsa_seq) {
    snd_seq_close(m_alsa_seq);
    m_alsa_seq = NULL;
  }
}

void AlsaMidiDriver::RetrieveDevices(unsigned int perms, std::vector<MidiDeviceInfo>& devices) {
  if (m_alsa_seq == NULL) return;

  snd_seq_client_info_t* cinfo;
  snd_seq_port_info_t* pinfo;
  int count = 0, ownid = snd_seq_client_id(m_alsa_seq);

  snd_seq_client_info_alloca(&cinfo);
  snd_seq_port_info_alloca(&pinfo);
  snd_seq_client_info_set_client(cinfo, -1);

  while (snd_seq_query_next_client(m_alsa_seq, cinfo) >= 0) {
    snd_seq_port_info_set_client(pinfo, snd_seq_client_info_get_client(cinfo));
    snd_seq_port_info_set_port(pinfo, -1);

    while (snd_seq_query_next_port(m_alsa_seq, pinfo) >= 0) {
      if ((snd_seq_port_info_get_capability(pinfo) & perms) == perms) {
        int client = snd_seq_client_info_get_client(cinfo);
        int port = snd_seq_port_info_get_port(pinfo);

        if (client == ownid && (port == m_local_in || port == m_local_out))
          continue;

        MidiDeviceInfo d;
        d.id = count++;
        d.name = snd_seq_port_info_get_name(pinfo);
        d.client = client;
        d.port = port;
        devices.push_back(d);
      }
    }
  }
}

std::vector<MidiDeviceInfo> AlsaMidiDriver::GetInputDevices() {
  std::vector<MidiDeviceInfo> devices;
  RetrieveDevices(SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, devices);
  return devices;
}

std::vector<MidiDeviceInfo> AlsaMidiDriver::GetOutputDevices() {
  std::vector<MidiDeviceInfo> devices;
  RetrieveDevices(SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, devices);
  return devices;
}

void AlsaMidiDriver::OpenInput(unsigned int device_id) {
  auto devices = GetInputDevices();
  if (device_id >= devices.size()) return;
  auto d = devices[device_id];

  int res = snd_seq_connect_from(m_alsa_seq, m_local_in, d.client, d.port);
  if (res < 0) {
    cerr << "[WARNING] Input connect failed: " << snd_strerror(res) << endl;
  } else {
    m_connected_in_client = d.client;
    m_connected_in_port = d.port;
  }
}

void AlsaMidiDriver::CloseInput() {
  if (m_connected_in_client != -1) {
    snd_seq_disconnect_from(m_alsa_seq, m_local_in, m_connected_in_client, m_connected_in_port);
    m_connected_in_client = -1;
  }
  snd_seq_drop_input(m_alsa_seq);
}

MidiEvent AlsaMidiDriver::Read() {
  if (snd_seq_event_input_pending(m_alsa_seq, 1) < 1)
    return MidiEvent::NullEvent();

  MidiEventSimple simple;
  snd_seq_event_t* ev;
  snd_seq_event_input(m_alsa_seq, &ev);

  switch(ev->type) {
  case SND_SEQ_EVENT_NOTEON:
    simple.status = 0x90 | (ev->data.note.channel & 0x0F);
    simple.byte1 = ev->data.note.note;
    simple.byte2 = ev->data.note.velocity;
    break;
  case SND_SEQ_EVENT_NOTEOFF:
    simple.status = 0x80 | (ev->data.note.channel & 0x0F);
    simple.byte1 = ev->data.note.note;
    simple.byte2 = 0;
    break;
  case SND_SEQ_EVENT_PGMCHANGE:
    simple.status = 0xC0 | (ev->data.note.channel & 0x0F);
    simple.byte1 = ev->data.control.value;
    break;
  default:
    return MidiEvent::NullEvent();
  }
  return MidiEvent::Build(simple);
}

bool AlsaMidiDriver::HasInput() {
  return snd_seq_event_input_pending(m_alsa_seq, 1);
}

void AlsaMidiDriver::OpenOutput(unsigned int device_id) {
  auto devices = GetOutputDevices();
  if (device_id >= devices.size()) return;
  auto d = devices[device_id];

  int res = snd_seq_connect_to(m_alsa_seq, m_local_out, d.client, d.port);
  if (res < 0) {
    cerr << "[WARNING] Output connect failed: " << snd_strerror(res) << endl;
  } else {
    m_connected_out_client = d.client;
    m_connected_out_port = d.port;
  }
}

void AlsaMidiDriver::CloseOutput() {
  if (m_connected_out_client != -1) {
    snd_seq_disconnect_to(m_alsa_seq, m_local_out, m_connected_out_client, m_connected_out_port);
    m_connected_out_client = -1;
  }
}

void AlsaMidiDriver::Write(const MidiEvent &out) {
  snd_seq_event_t ev;
  snd_seq_ev_clear(&ev);
  snd_seq_ev_set_source(&ev, m_local_out);
  snd_seq_ev_set_subs(&ev);
  snd_seq_ev_set_direct(&ev);

  switch (out.Type()) {
  case MidiEventType_NoteOn:
    snd_seq_ev_set_noteon(&ev, out.Channel(), out.NoteNumber(), out.NoteVelocity());
    break;
  case MidiEventType_NoteOff:
    snd_seq_ev_set_noteoff(&ev, out.Channel(), out.NoteNumber(), out.NoteVelocity());
    break;
  case MidiEventType_ProgramChange:
    snd_seq_ev_set_pgmchange(&ev, out.Channel(), out.ProgramNumber());
    break;
  default:
    return;
  }
  snd_seq_event_output(m_alsa_seq, &ev);
  snd_seq_drain_output(m_alsa_seq);
}
