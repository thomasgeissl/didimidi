#pragma once
#include "./defines.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306.git


class Display {
  public:
    Display() : _display(Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)) {

    }
    void begin() {
      if (!_display.begin(SSD1306_SWITCHCAPVCC, ADDRESS_DISPLAY)) {
        Serial.println(F("could not init display"));
      }
      _display.clearDisplay();
      _display.display();
      _lines[0] = "> item 1";
      _lines[1] = "> item 2";
      _lines[2] = "> item 3";
      _lines[3] = "> item 4";

    }

    void draw() {
      _display.clearDisplay();
      _display.setTextSize(1);
      _display.setTextColor(SSD1306_WHITE);
      _display.setCursor(0, 0);
      _display.println(_title);
      auto y = 10;
      auto lineHeight = 6;
      auto offsetY = 6;
      _display.drawLine(0, y, _display.width(), y, SSD1306_WHITE);
      y = 18;

      for (auto i = 0; i < 4; i++) {
        y = 18 + i * (lineHeight + offsetY);
        _display.setCursor(0, y);
        _display.println(_lines[i]);
      }
      _display.display();
    }

    void setTitle(String title) {
      _title = title;
    }
  private:
    Adafruit_SSD1306 _display;
    String _title;
    String _lines[4];
};
