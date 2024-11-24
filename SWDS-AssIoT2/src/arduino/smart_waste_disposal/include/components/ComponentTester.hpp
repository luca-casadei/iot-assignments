class LCD;
class Led;
class ServoMotor;
class SerialCommunicator;

class ComponentTester{
    public:
    void test();
    virtual void init() final;
    ~ComponentTester();
    ComponentTester(const unsigned int green_led_pin, const unsigned int red_led_pin, const unsigned int led_servo);
    private:
    LCD * lcd;
    Led * led_green;
    Led * led_red;
    ServoMotor * sv;
};