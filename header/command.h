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
  virtual bool execute (string argument); 

};



#endif
