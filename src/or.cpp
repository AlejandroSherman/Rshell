#ifndef __OR_CPP__
#define __OR_CPP__

#include "../header/base.h"
#include "../header/connector.h"
#inlcude <iostream>

using namespace std;

class Base;

class Or : public Connector {
public:
  Or() { }
  Or(Base *left, Base *right) : Connector(left, right) { }
  bool execute() {
    return (left->execute()) || (right->execute());
  }
};

#endif
