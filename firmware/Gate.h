#pragma once

class Gate {
  public:
    void begin(int pin, int ledPin) {
      _open = false;
      _pin = pin;
      _ledPin = ledPin;
      pinMode(_pin, OUTPUT);
      pinMode(_ledPin, OUTPUT);
    }
    void update() {
      digitalWrite(_pin, _open ? HIGH : LOW);
      digitalWrite(_ledPin, _open ? HIGH : LOW);

    }
    void set(bool value) {
      _open = value;
    }
    void open() {
      _open = true;
    }
    void close() {
      _open = false;
    }
    bool isOpen() {
      return _open;
    }
  private:
    int _pin;
    int _ledPin;
    bool _open;
};
