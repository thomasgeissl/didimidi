#pragma once

class Mode {
  public:
    Mode(int id, String name) : _id(id), _name(name) {

    }
    int getId() {
      return _id;
    }
    String getName() {
      return _name;
    }
    int _id;
    String _name;
};

class ChannelToSlotMode : public Mode {
  public:
    ChannelToSlotMode() : Mode(0, "ch2slot") {}
};

class Baby8Mode : public Mode {
  public:
    Baby8Mode() : Mode(1, "baby8") {}
    void tick() {

    }
};
