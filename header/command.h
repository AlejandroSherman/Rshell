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
  string arg;
public:
  Command(){ }
  Command(string input, string argument){
    cmd = input;
    arg = argument;
}
  virtual bool execute ();

};



#endif
