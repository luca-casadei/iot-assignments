#ifndef __ILCD__
#define __ILCD__

class ILCD{
    public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void printToLine(const unsigned int, const char *) = 0;
};

#endif