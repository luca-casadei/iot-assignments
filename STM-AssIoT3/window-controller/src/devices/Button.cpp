#include "./devices/Button.hpp"

Button::Button(){
}

void Button::updateSyncTime(const long time)
{
	lastTimeSync = time;
}

long Button::getLastSyncTime(){
	return lastTimeSync;
}
