#pragma once
#include "./Trigger.h"
#include "./Gate.h"

class Slot {
  public:
    bool begin(int ledPin, int gateDacPin, int gatePin, bool hasTriggerAndVelocity) {
//      _trigger.begin(triggerPin);
//      _gate.begin(gatePin, ledPin);
//      _pitchOrCcPin = pitchOrCcPin;
//      _velocityOrValuePin = velocityOrValuePin;
      return true;
    }
    bool begin(int ledPin, int triggerPin, int gatePin, int pitchOrCcPin, int velocityOrValuePin) {
      _trigger.begin(triggerPin);
      _gate.begin(gatePin, ledPin);
      _pitchOrCcPin = pitchOrCcPin;
      _velocityOrValuePin = velocityOrValuePin;
      return true;
    }
    void update() {
      _trigger.update();
      _gate.update();
    }
    void trigger() {
      _trigger.trigger(20);
    }

    void setNoteOn(int note, int velocity) {
      _trigger.trigger(20);
      _gate.open();

      //      TODO: note to pwm, v/octave
      int value = 127;
      analogWrite(_pitchOrCcPin, value);
    }
    void setNoteOff(int note, int velocity) {
      _gate.close();
    }

    void setCc(int control, int value) {

    }
  private:
    Trigger _trigger;
    Gate _gate;
    int _pitchOrCcPin;
    int _velocityOrValuePin;
};
