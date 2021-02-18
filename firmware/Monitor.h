#pragma once

#include <deque>
//#include <MIDI.h> //https://github.com/FortySevenEffects/arduino_midi_library.git

class Monitor {
  public:
  std::deque<String> _messages;
};
