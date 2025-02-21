#pragma once

#include "pins.hpp"
#include "HWPlatform.hpp"

enum SystemState{ AUTOMATIC, MANUAL };

class Dashboard {

public:
  Dashboard();

  void init();
  
  void notifyNewState();
  
  void sync();

 private:
  SystemState actualState;
};
