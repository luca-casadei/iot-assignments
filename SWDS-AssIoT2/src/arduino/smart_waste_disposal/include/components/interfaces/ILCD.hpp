#pragma once

class ILCD{
    public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void printToLine(const unsigned int, const char *) = 0;
    virtual ~ILCD(){};
    virtual void init() = 0;
};