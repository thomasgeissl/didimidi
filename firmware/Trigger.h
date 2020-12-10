#pragma once

class Trigger {
  public:
    void begin(int pin) {
      _pin = pin;
      pinMode(_pin, OUTPUT);
    }
    void update() {
      if (millis() > _timeStamp) {
        digitalWrite(_pin, LOW);
      }
    }
    void trigger(int timeInMs) {
      _timeStamp = millis() + timeInMs;
      digitalWrite(_pin, HIGH);
    }
  private:
    int _pin;
    unsigned long _timeStamp;
};
