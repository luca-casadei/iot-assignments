#pragma once

#include "Arduino.h"

class Msg
{
  String content;

public:
  Msg(const String content)
  {
    this->content = content;
  }

  String getContent()
  {
    return content;
  }
};

class Pattern
{
public:
  virtual boolean match(Msg &m) = 0;
};

class MsgServiceClass
{

public:
  Msg *currentMsg;
  bool msgAvailable;

  void init();

  bool isMsgAvailable();
  Msg *receiveMsg();

  bool isMsgAvailable(Pattern &pattern);
  Msg *receiveMsg(Pattern &pattern);

  void sendMsg(const String &msg);
};

extern MsgServiceClass MsgService;
