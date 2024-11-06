#ifndef __ISERVO_MOTOR__
#define __ISERVO_MOTOR__

class IServoMotor{
    public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void empty() = 0;
};

#endif