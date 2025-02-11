#ifndef __DASHBOARD__
#define __DASHBOARD__

#include "pins.hpp"
#include "HWPlatform.hpp"

class Dashboard {

public:
  Dashboard();

  void init();
  
  void notifyNewState();
  
  bool checkAndResetDischargeRequest();
  bool checkAndResetMaintenanceDone();

  void sync();

 private:
  bool dischargeCmdRequested;
  bool maintenanceDoneNotified;
};

#endif
