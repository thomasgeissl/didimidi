//tools/USB type: Serial + MIDI
#include "Wire.h"
#include <SPI.h>
#include <Encoder.h>
#include <EEPROM.h>

#include "USBHost_t36.h" //https://github.com/PaulStoffregen/USBHost_t36.git
#include <MIDI.h> //https://github.com/FortySevenEffects/arduino_midi_library.git
#include <JC_Button.h> //https://github.com/JChristensen/JC_Button.git
#include <DAC57X4.h> //https://github.com/laserlance/Arduino-Precision-DAC-AD57X4



#include "./defines.h"
#include "./Slot.h"
#include "./Trigger.h"
#include "./State.h"

#include "./Display.h"
#include "./Monitor.h"

#include "./mcp4922.h"



MIDI_CREATE_DEFAULT_INSTANCE();

// inputs
USBHost _usbHost;
MIDIDevice _midiHost(_usbHost);
Button _backButton(PIN_BACKBUTTON, DEBOUNCETIME_BUTTON, true, true);
Button _confirmButton(PIN_CONFIRMBUTTON, DEBOUNCETIME_BUTTON, true, true);
Encoder _rotary(PIN_ROTARY_A, PIN_ROTARY_B);

int _gateDacs[] = {PIN_DAC_0, PIN_DAC_1, PIN_DAC_2, PIN_DAC_3};

// outputs

Slot _slots[NUMBEROFSLOTS];
Trigger _clock;
Display _display;

State _state;
Monitor _monitor;
long _position  = 0;


DAC57X4 _audioDacs[] = {DAC57X4(4, AD5754_VOLTAGE_SELECTION, PIN_DAC_4), DAC57X4(4, AD5754_VOLTAGE_SELECTION, PIN_DAC_5) };


void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(PIN_DAC_0, OUTPUT);
  pinMode(PIN_DAC_1, OUTPUT);
  pinMode(PIN_DAC_2, OUTPUT);
  pinMode(PIN_DAC_3, OUTPUT);

  digitalWrite(PIN_DAC_0, HIGH);
  digitalWrite(PIN_DAC_1, HIGH);
  digitalWrite(PIN_DAC_2, HIGH);
  digitalWrite(PIN_DAC_3, HIGH);

  SPI.begin();


  _clock.begin(PIN_CLOCK);
  _slots[0].begin(PIN_LED_SLOT0, 2, 3, 4, 5);
  _slots[1].begin(PIN_LED_SLOT1, 6, 7, 8, 9);
  _slots[2].begin(PIN_LED_SLOT2, 24, 25, 28, 29);
  _slots[3].begin(PIN_LED_SLOT3, 14, 15, 22, 23);

  _confirmButton.begin();
  _backButton.begin();


  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);
  MIDI.setHandleAfterTouchPoly(onAfterTouchPoly);
  MIDI.setHandleControlChange(onControlChange);
  MIDI.setHandleProgramChange(onProgramChange);
  //  MIDI.setHandleAfterTouch(onAfterTouch);
  //  MIDI.setHandlePitchChange(onPitchChange);
  MIDI.setHandleSystemExclusive(onSystemExclusiveChunk);
  MIDI.setHandleTimeCodeQuarterFrame(onTimeCodeQuarterFrame);
  MIDI.setHandleSongPosition(onSongPosition);
  MIDI.setHandleSongSelect(onSongSelect);
  MIDI.setHandleTuneRequest(onTuneRequest);
  MIDI.setHandleClock(onClock);
  MIDI.setHandleStart(onStart);
  MIDI.setHandleContinue(onContinue);
  MIDI.setHandleStop(onStop);
  MIDI.setHandleActiveSensing(onActiveSensing);
  MIDI.setHandleSystemReset(onSystemReset);
  //  MIDI.setHandleRealTimeSystem(onRealTimeSystem);


  _usbHost.begin();
  _midiHost.setHandleNoteOff(onNoteOff);
  _midiHost.setHandleNoteOn(onNoteOn);
  _midiHost.setHandleAfterTouchPoly(onAfterTouchPoly);
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


  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
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

  _display.begin();

}

void loop() {
  //  setVoltage(PIN_DAC_0, 0, false, 1024 * 4 - 1);
  //  delay(1000);
  //  setVoltage(PIN_DAC_0, 0, false, 0);
  //  delay(1000);

  _clock.update();
  for (auto i = 0; i < NUMBEROFSLOTS; i++) {
    _slots[i].update();
  }

  //  if (MIDI.read())
  //  {
  //    switch (MIDI.getType())
  //    {
  //      case midi::ProgramChange:
  //        break;
  //      default:
  //        break;
  //    }
  //  }
  _usbHost.Task();
  _midiHost.read();
  usbMIDI.read();

  _backButton.read();
  _confirmButton.read();

  if (_backButton.wasPressed()) {
    Serial.println("cancel button was pressed");

  }
  if (_confirmButton.wasPressed()) {
    Serial.println("ok button was pressed");
  }

  auto position = _rotary.read();
  if (position != _position) {
    Serial.println(position);
    _position = position;
  }
  _display.draw();
}

void draw() {
  //  _display.clearDisplay();
  ////  _display.drawLine(_display.width() - 1, 0, 0, i, SSD1306_WHITE);
  //  _display.setTextSize(1); // Draw 2X-scale text
  //  _display.setTextColor(SSD1306_WHITE);
  //  _display.setCursor(0, 0);
  //  _display.println(F("didimidi"));
  //  _display.display();
}

void onNoteOn(byte channel, byte note, byte velocity)
{
  Serial.print("Note On, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(note);
  Serial.print(", velocity=");
  Serial.print(velocity);
  Serial.println();

  switch (_state.getMode().getId()) {
    case 0: {
        if (channel < NUMBEROFSLOTS) {
          _slots[channel].setNoteOn(note, velocity);
          setVoltage(PIN_DAC_0, 0, false, map(note, 0, 127, 0, 1024 * 4 - 1));
        }
        break;
      }
  }
}

void onNoteOff(byte channel, byte note, byte velocity)
{
  Serial.print("Note Off, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(note);
  //Serial.print(", velocity=");
  //Serial.print(velocity);
  Serial.println();

  //  switch (_mode) {
  //    case Mode::CHANNELTOSLOT: {
  //        if (channel < NUMBEROFSLOTS) {
  //          _slots[channel].setNoteOff(note, velocity);
  //        }
  //        break;
  //      }
  //  }
}

void onControlChange(byte channel, byte control, byte value)
{
  Serial.print("Control Change, ch=");
  Serial.print(channel);
  Serial.print(", control=");
  Serial.print(control);
  Serial.print(", value=");
  Serial.print(value);
  Serial.println();

  String text = "cc: ";
  text += control;
  text += ", value: ";
  text += value;

  _display.setTitle("midi monitor");
}


void onAfterTouchPoly(byte channel, byte note, byte velocity) {}
void onProgramChange(byte channel, byte program) {}
void onAfterTouch(byte channel, byte pressure) {}
void onPitchChange(byte channel, int pitch) {}
void onSystemExclusiveChunk(const byte *data, uint16_t length, bool last) {}
void onSystemExclusive(byte *data, unsigned int length) {}
void onTimeCodeQuarterFrame(byte data) {}
void onSongPosition(uint16_t beats) {}
void onSongSelect(byte songNumber) {}
void onTuneRequest() {}
void onClock() {
  _clock.trigger(20);
}
void onStart() {}
void onContinue() {}
void onStop() {}
void onActiveSensing() {}
void onSystemReset() {}
void onRealTimeSystem(byte realtimebyte) {}
