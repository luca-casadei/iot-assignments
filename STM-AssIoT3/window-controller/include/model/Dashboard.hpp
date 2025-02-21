#pragma once

#include "constants.hpp"
#include "UserPanel.hpp"

class Dashboard
{

public:
  Dashboard(UserPanel *pUserPanel);

  void init();

  void notifyNewState(String msg);

  void notifyWindowOpening();

  void sync();

private:
  UserPanel *pUserPanel;
};
