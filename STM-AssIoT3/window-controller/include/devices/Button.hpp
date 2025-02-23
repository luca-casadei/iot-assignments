#pragma once

class Button {
 
public:
  Button();
  virtual bool isPressed() = 0;
  virtual bool isClicked() = 0;

  virtual void sync() = 0;
  long getLastSyncTime();

protected:
  void updateSyncTime(const long time);

private:
  long lastTimeSync;

};
