#ifndef __SEMI_CPP__
#define __SEMI_CPP__

#include "../header/base.h"
#include "../header/connector.h"
#inlcude <iostream>

using namespace std;

class Base;

class Semi : public Connector {
public:
  Semi() { }
  Semi(Base *left, Base *right) : Connector(left, right) { }
  bool execute() {
     left->execute();
     return right->execute();
  }
};

#endif
