#include "tasks/TemperatureTask.hpp"
#include "components/TemperatureSensor.hpp"
#include "serial/MsgService.hpp"

TemperatureTask::TemperatureTask(unsigned int temp_pin, unsigned int max_temp, unsigned int max_temp_time) : TaskWithCounter(1)
{
    this->temperature_sensor = new TemperatureSensor(temp_pin);
    this->max_temp = max_temp;
    this->add_time(max_temp_time);
}

void TemperatureTask::init(unsigned int period)
{
    Task::init(period);
    this->state = STABLE;
    this->counter = 0;
}

bool TemperatureTask::isInDanger(){
    return this->state == DANGER;
}

double TemperatureTask::getTemp(){
    return this->temperature_sensor->getTemperature();
}

void TemperatureTask::tick()
{
    const double temperature = this->temperature_sensor->getTemperature();
    switch (this->state)
    {
    case STABLE:
    {
        if (temperature >= this->max_temp)
        {
            this->counter = 0;
            this->state = UNSTABLE;
        }
        break;
    }
    case UNSTABLE:
    {
        if (temperature >= this->max_temp)
        {
            if (this->counter >= this->get_iterations())
            {
                this->state = DANGER;
            }
            else
            {
                this->counter++;
            }
        }
        else
        {
            this->state = STABLE;
        }
        break;
    }
    case DANGER:
    {
        if (MsgService.isMsgAvailable()){
            Msg* msg = MsgService.receiveMsg();    
            if (msg->getContent() == "RESTORE"){
                this->state = STABLE;
            }
            delete msg;
        }
        break;
    }
    }
}
