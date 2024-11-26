#include "tasks/WasteTask.hpp"
#include "components/Button.hpp"
#include "components/WasteSensor.hpp"
#include "components/Led.hpp"
#include "components/LCD.hpp"
#include "serial/MsgService.hpp"
#include <Arduino.h>

WasteTask::WasteTask(unsigned int green_led_pin,
                     unsigned int red_led_pin,
                     unsigned int open_button_pin,
                     unsigned int close_button_pin,
                     unsigned int waste_sensor_echo_pin,
                     unsigned int waste_sensor_trig_pin,
                     unsigned int max_entered_waste_time,
                     unsigned int waste_received_time,
                     unsigned int waste_emptying_time,
                     unsigned int waste_max_level) : TaskWithCounter(3)
{
    this->green_led = new Led(green_led_pin);
    this->red_led = new Led(red_led_pin);
    this->open_button = new Button(open_button_pin);
    this->close_button = new Button(close_button_pin);
    this->waste_sensor = new WasteSensor(waste_sensor_echo_pin, waste_sensor_trig_pin);
    this->waste_received_time = waste_received_time;
    this->waste_emptying_time = waste_emptying_time;
    this->waste_max_level = waste_max_level;
}

void WasteTask::init(unsigned int period)
{
    Task::init(period);
    this->state = CLOSED;
    this->counter = 0;
}

void WasteTask::tick()
{
    switch (state)
    {
    case CLOSED:
    {
        if (open_button->isPressed())
        {
            state = OPEN;
        }
        break;
    }
    case RECEIVED:
    {
       /* if(this->counter >= this->waste_received_time){
            if(this->waste_sensor->getWasteLevel() > this->waste_max_level)
            {
                state = CLOSED;
                this->counter = 0;
            } else {
                state = FULL;
            }
        }
        if(temperature_task->isInDanger()){
            state = ERRORED;
        }*/
        break;
    }
    case ERRORED:
    {
        if (MsgService.isMsgAvailable()){
            Msg* msg = MsgService.receiveMsg();    
            if (msg->getContent() == "RESTORE"){
                this->state = EMPTYING;
                this->counter = 0;
            }
            delete msg;
        }
        break;
    }
    case EMPTYING:
    {
        if(this->counter < this->waste_emptying_time){
            this->counter++;
        } else {
            state = CLOSED;
            this->counter = 0;
        }
        break;
    }
    case FULL:
    {
        if (MsgService.isMsgAvailable()){
            Msg* msg = MsgService.receiveMsg();    
            if (msg->getContent() == "EMPTY"){
                this->state = EMPTYING;
                this->counter = 0;
            }
            delete msg;
        }
        break;
    }

    case OPEN:
    {
        if (close_button->isPressed() || this->counter >= this->max_entered_waste_time /*|| waste_sensor->getWasteLevel() <= this->waste_max_level*/)
        {
            state = RECEIVED;
            this->counter = 0;
        }
        else if(this->counter < this->max_entered_waste_time)
        {
            this->counter++;
        }
    }
    break;
    }
}