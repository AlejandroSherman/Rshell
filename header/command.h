#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <iostream>
#include <string>
#include "base.h"
#include <vector>
using namespace std;

class Base;

class Command : public Base {
protected:
  string cmd;
  vector<string> args;
public:
  Command(){ }
  Command(string input, vector<string> arguments){
    cmd = input;
    args = arguments;
}
  virtual bool execute ();
  virtual string getPath(){
    return cmd;
  }
};



#endif
