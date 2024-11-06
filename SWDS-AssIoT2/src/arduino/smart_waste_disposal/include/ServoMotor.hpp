#include "IServoMotor.hpp"

class Servo;

class ServoMotor : public IServoMotor {
    public: 
    ServoMotor(unsigned int pin);
    ~ServoMotor();
    void open();
    void close();
    void empty();

    private:
    Servo * servo_motor;
};