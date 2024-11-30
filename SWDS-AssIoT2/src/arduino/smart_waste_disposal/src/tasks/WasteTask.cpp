#include "tasks/WasteTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "components/Button.hpp"
#include "components/WasteSensor.hpp"
#include "components/Led.hpp"
#include "components/LCD.hpp"
#include "serial/MsgService.hpp"
#include "components/ServoMotor.hpp"

#define T1 0
#define T2 1
#define T3 2

WasteTask::WasteTask(unsigned int green_led_pin,
                     unsigned int red_led_pin,
                     unsigned int open_button_pin,
                     unsigned int close_button_pin,
                     unsigned int waste_sensor_echo_pin,
                     unsigned int waste_sensor_trig_pin,
                     unsigned int max_entered_waste_time,
                     unsigned int waste_received_time,
                     unsigned int waste_emptying_time,
                     unsigned int waste_max_level,
                     unsigned int door_pin,
                     TemperatureTask *tTask,
                     LCD *lcd) : TaskWithCounter(3)
{
    this->green_led = new Led(green_led_pin);
    this->red_led = new Led(red_led_pin);
    this->open_button = new Button(open_button_pin);
    this->close_button = new Button(close_button_pin);
    this->waste_sensor = new WasteSensor(waste_sensor_echo_pin, waste_sensor_trig_pin);
    this->waste_max_level = waste_max_level;
    this->tTask = tTask;
    this->lcd = lcd;
    this->servo = new ServoMotor(door_pin);
    this->add_time(max_entered_waste_time);
    this->add_time(waste_received_time);
    this->add_time(waste_emptying_time);
}

void WasteTask::init(unsigned int period)
{
    Task::init(period);
    this->waste_sensor->init();
    this->open_button->init();
    this->close_button->init();
    this->red_led->init();
    this->green_led->init();
    this->servo->init();

    to_closed();
}

void WasteTask::to_received()
{
    this->lcd->printToLine(0, "WASTE");
    this->lcd->printToLine(1, "RECEIVED");
    this->servo->close();
    state = RECEIVED;
    this->counter = 0;
}
void WasteTask::to_closed()
{
    this->green_led->switchOn();
    this->red_led->switchOff();
    this->lcd->printToLine(0, "PRESS OPEN TO");
    this->lcd->printToLine(1, "ENTER WASTE");
    this->servo->close();
    state = CLOSED;
    this->counter = 0;
}
void WasteTask::to_full()
{
    this->green_led->switchOff();
    this->red_led->switchOn();
    this->lcd->printToLine(0, "CONTAINER");
    this->lcd->printToLine(1, "FULL!");
    state = FULL;
}
void WasteTask::to_emptying()
{
    this->state = EMPTYING;
    this->counter = 0;
    this->servo->empty();
}
void WasteTask::to_errored()
{
    this->green_led->switchOff();
    this->red_led->switchOn();
    this->lcd->printToLine(0, "PROBLEM");
    this->lcd->printToLine(1, "DETECTED!");
    state = ERRORED;
}

void WasteTask::to_open()
{
    this->lcd->printToLine(0, "PRESS CLOSE");
    this->lcd->printToLine(1, "WHEN DONE");
    this->servo->open();
    state = OPEN;
}

void WasteTask::tick()
{
    const bool is_open_pressed = this->open_button->isPressed();
    const bool is_close_pressed = this->close_button->isPressed();
    const bool is_in_danger = tTask->isInDanger();
    const double temp = this->tTask->getTemp();
    const double waste_level = this->waste_sensor->getWasteLevel(temp);
    Serial.print(temp);
    Serial.print(",");
    Serial.println(waste_level);
    switch (state)
    {
    case CLOSED:
    {
        if (is_in_danger)
        {
            to_errored();
        }
        if (is_open_pressed)
        {
            to_open();
        }
        break;
    }
    case RECEIVED:
    {
        if (this->counter >= this->get_iterations(T2))
        {
            if (waste_level > this->waste_max_level)
            {
                to_closed();
            }
            else
            {
                to_full();
            }
        }
        else
        {
            counter++;
        }
        if (is_in_danger)
        {
            to_errored();
        }
        break;
    }
    case ERRORED:
    {
        if (!is_in_danger)
        {
            to_closed();
        }
        break;
    }
    case EMPTYING:
    {
        if (this->counter < this->get_iterations(T3))
        {
            this->counter++;
        }
        else
        {
            to_closed();
        }
        break;
    }
    case FULL:
    {
        if (MsgService.isMsgAvailable()){
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "EMPTY"){
                to_emptying();
            }
            delete msg;
        }
        break;
    }

    case OPEN:
    {
        if (is_close_pressed || this->counter >= this->get_iterations(T1) || waste_level <= this->waste_max_level)
        {
            to_received();
        }
        else if (this->counter < this->get_iterations(T1))
        {
            this->counter++;
        }
    }
    break;
    }
}