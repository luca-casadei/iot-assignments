#pragma once

class ILed {
    public:
    virtual void switchOn(void) = 0;
    virtual void switchOff(void) = 0;
    virtual void init(void) = 0;
};