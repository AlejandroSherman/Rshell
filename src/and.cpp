#ifndef __AND_CPP__
#define __AND_CPP__

#include "../header/base.h"
#include "../header/connector.h"
#inlcude <iostream>

using namespace std;

class Base;

class And : public Connector {
public:
  And() { }
  And(Base *left, Base *right) : Connector(left, right) { }
  bool execute() {
    return (left->execute()) && (right->execute());
  }
};

#endif
