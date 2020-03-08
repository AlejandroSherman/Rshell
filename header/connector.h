#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "base.h"
#include "command.h"

using namespace std;

class Base;

class Connector: public Base{
protected:
  Base* left;
  Base* right;
public:
  Connector() { };
  Connector(Base* lhs, Base* rhs) {
  left = lhs;
  right = rhs;
  }
  virtual bool execute() = 0;
  virtual string getPath() = 0;
};

#endif
