#pragma once
#include <vector>
#include "./Modes.h"


class State {
  public:
    State () : _mode(ChannelToSlotMode()) {
      _modes.push_back(ChannelToSlotMode());

    }
    Mode getMode() {
      return _mode;
    }

    std::vector<Mode> _modes;
    Mode _mode;
};
