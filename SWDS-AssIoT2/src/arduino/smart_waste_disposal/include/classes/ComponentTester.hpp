#include "interfaces/IComponentTester.hpp"

class LCD;
class Led;
class ServoMotor;

class ComponentTester: public ICompoentTest{
    public:
    void test();
    void init() final;
    ~ComponentTester();
    ComponentTester(const unsigned int green_led_pin, const unsigned int red_led_pin, const unsigned int led_servo);
    private:
    LCD * lcd;
    Led * led_green;
    Led * led_red;
    ServoMotor * sv;
};