#pragma once

#include "constants.hpp"
#include "UserPanel.hpp"

class Dashboard
{

public:
  Dashboard(UserPanel *pUserPanel);

  void init();

  void notifyNewState();

  void notifyWindowOpening();

  void sync();

private:
  UserPanel *pUserPanel;
};
