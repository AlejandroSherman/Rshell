#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <iostream>
#include <string>
#include "base.h"
using namespace std;

class Base;

class Command : public Base {
protected:
  string cmd;
public:
  Command();
  Command(string input){
    cmd = input;
  }
  virtual bool execute { //perhaps this function could see waht the command is, and if it's valid, return true and then execute the command, and if invalid return a false
}
};



#endif
