#include <Arduino.h>
#include "components/classes/ComponentTester.hpp"
#include "constants.hpp"
#include "serial/classes/MsgService.hpp"

#define TEST_COMPONENTS

#ifdef TEST_COMPONENTS
ICompoentTester * tester;
#endif

void setup()
{
#ifdef TEST_COMPONENTS
    tester = new ComponentTester(GREEN_PIN, RED_PIN, SERVO_PIN);
    tester->init();
    MsgService.init();
#endif
    //Task initialization
    // TODO
}

void loop()
{
#ifdef TEST_COMPONENTS
    tester->test();
    if (MsgService.isMsgAvailable()){
        Msg * msg = MsgService.receiveMsg();
        if (msg->getContent() == "ping"){
            delay(500);
            MsgService.sendMsg("pong");
        }
        delete msg;
    }
#else
    // TODO
#endif
}