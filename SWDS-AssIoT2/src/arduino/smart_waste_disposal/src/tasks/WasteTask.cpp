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

    this->state = CLOSED;
    this->counter = 0;
    this->lcd->printToLine(0, "PRESS OPEN TO");
    this->lcd->printToLine(1, "ENTER WASTE");
    this->green_led->switchOn();
    this->red_led->switchOff();
}

void WasteTask::tick()
{
    const bool isOpenPressed = this->open_button->isPressed();
    const bool isClosePressed = this->close_button->isPressed();
    const bool isInDanger = tTask->isInDanger();
    const double wasteLevel = this->waste_sensor->getWasteLevel(this->tTask->getTemp());
    switch (state)
    {
    case CLOSED:
    {
        if (isOpenPressed)
        {
            this->lcd->printToLine(0, "PRESS CLOSE");
            this->lcd->printToLine(1, "WHEN DONE");
            this->servo->open();
            state = OPEN;
        }
        break;
    }
    case RECEIVED:
    {
        if (this->counter >= this->get_iterations(T2))
        {
            Serial.println(wasteLevel);
            if (wasteLevel > this->waste_max_level)
            {
                this->green_led->switchOn();
                this->red_led->switchOff();
                this->lcd->printToLine(0, "PRESS OPEN TO");
                this->lcd->printToLine(1, "ENTER WASTE");
                state = CLOSED;
                this->counter = 0;
            }
            else
            {
                this->green_led->switchOff();
                this->red_led->switchOn();
                this->lcd->printToLine(0, "CONTAINER");
                this->lcd->printToLine(1, "FULL!");
                state = FULL;
            }
        }
        else
        {
            counter++;
        }
        if (isInDanger)
        {
            this->green_led->switchOff();
            this->red_led->switchOn();
            this->lcd->printToLine(0, "PROBLEM");
            this->lcd->printToLine(1, "DETECTED!");
            state = ERRORED;
        }
        break;
    }
    case ERRORED:
    {
        if (MsgService.isMsgAvailable())
        {
            Msg *msg = MsgService.receiveMsg();
            if (msg->getContent() == "RESTORE")
            {
                this->state = EMPTYING;
                this->counter = 0;
            }
            delete msg;
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
            this->green_led->switchOn();
            this->red_led->switchOff();
            this->lcd->printToLine(0, "PRESS OPEN TO");
            this->lcd->printToLine(1, "ENTER WASTE");
            state = CLOSED;
            this->counter = 0;
        }
        break;
    }
    case FULL:
    {
        if (MsgService.isMsgAvailable())
        {
            Msg *msg = MsgService.receiveMsg();
            if (msg->getContent() == "EMPTY")
            {
                this->state = EMPTYING;
                this->counter = 0;
            }
            delete msg;
        }
        break;
    }

    case OPEN:
    {
        if (isClosePressed || this->counter >= this->get_iterations(T1) || wasteLevel <= this->waste_max_level)
        {
            this->lcd->printToLine(0, "WASTE");
            this->lcd->printToLine(1, "RECEIVED");
            this->servo->close();
            state = RECEIVED;
            this->counter = 0;
        }
        else if (this->counter < this->get_iterations(T1))
        {
            this->counter++;
        }
    }
    break;
    }
}