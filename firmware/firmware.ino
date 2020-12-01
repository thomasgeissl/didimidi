//tools/USB type: Serial + MIDI
#include "USBHost_t36.h" //https://github.com/PaulStoffregen/USBHost_t36.git

USBHost _usbHost;
MIDIDevice _midiHost(_usbHost);

void setup() {
  _usbHost.begin();
  _midiHost.setHandleNoteOff(OnNoteOff);
  _midiHost.setHandleNoteOn(OnNoteOn);
  _midiHost.setHandleAfterTouchPoly(onAfterTouchPoly);
  _midiHost.setHandleControlChange(OnControlChange);
  _midiHost.setHandleControlChange(onControlChange);
  _midiHost.setHandleProgramChange(onProgramChange);
  _midiHost.setHandleAfterTouch(onAfterTouch);
  _midiHost.setHandlePitchChange(onPitchChange);
  _midiHost.setHandleSystemExclusive(onSystemExclusiveChunk);
  _midiHost.setHandleTimeCodeQuarterFrame(onTimeCodeQuarterFrame);
  _midiHost.setHandleSongPosition(onSongPosition);
  _midiHost.setHandleSongSelect(onSongSelect);
  _midiHost.setHandleTuneRequest(onTuneRequest);
  _midiHost.setHandleClock(onClock);
  _midiHost.setHandleStart(onStart);
  _midiHost.setHandleContinue(onContinue);
  _midiHost.setHandleStop(onStop);
  _midiHost.setHandleActiveSensing(onActiveSensing);
  _midiHost.setHandleSystemReset(onSystemReset);
  _midiHost.setHandleRealTimeSystem(onRealTimeSystem);

  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleAfterTouchPoly(onAfterTouchPoly);
  usbMIDI.setHandleControlChange(onControlChange);
  usbMIDI.setHandleProgramChange(onProgramChange);
  usbMIDI.setHandleAfterTouch(onAfterTouch);
  usbMIDI.setHandlePitchChange(onPitchChange);
  usbMIDI.setHandleSystemExclusive(onSystemExclusiveChunk);
  usbMIDI.setHandleTimeCodeQuarterFrame(onTimeCodeQuarterFrame);
  usbMIDI.setHandleSongPosition(onSongPosition);
  usbMIDI.setHandleSongSelect(onSongSelect);
  usbMIDI.setHandleTuneRequest(onTuneRequest);
  usbMIDI.setHandleClock(onClock);
  usbMIDI.setHandleStart(onStart);
  usbMIDI.setHandleContinue(onContinue);
  usbMIDI.setHandleStop(onStop);
  usbMIDI.setHandleActiveSensing(onActiveSensing);
  usbMIDI.setHandleSystemReset(onSystemReset);
  usbMIDI.setHandleRealTimeSystem(onRealTimeSystem);
}

void loop() {
  _usbHost.Task();
  _midiHost.read();
  usbMIDI.read();
}

void OnNoteOn(byte channel, byte note, byte velocity)
{
  Serial.print("Note On, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(note);
  Serial.print(", velocity=");
  Serial.print(velocity);
  Serial.println();
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  Serial.print("Note Off, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(note);
  //Serial.print(", velocity=");
  //Serial.print(velocity);
  Serial.println();
}

void OnControlChange(byte channel, byte control, byte value)
{
  Serial.print("Control Change, ch=");
  Serial.print(channel);
  Serial.print(", control=");
  Serial.print(control);
  Serial.print(", value=");
  Serial.print(value);
  Serial.println();
}


void onAfterTouchPoly(byte channel, byte note, byte velocity) {}
void onControlChange(byte channel, byte control, byte value) {}
void onProgramChange(byte channel, byte program) {}
void onAfterTouch(byte channel, byte pressure) {}
void onPitchChange(byte channel, int pitch) {}
void onSystemExclusiveChunk(const byte *data, uint16_t length, bool last) {}
void onSystemExclusive(byte *data, unsigned int length) {}
void onTimeCodeQuarterFrame(byte data) {}
void onSongPosition(uint16_t beats) {}
void onSongSelect(byte songNumber) {}
void onTuneRequest() {}
void onClock() {}
void onStart() {}
void onContinue() {}
void onStop() {}
void onActiveSensing() {}
void onSystemReset() {}
void onRealTimeSystem(byte realtimebyte) {}
