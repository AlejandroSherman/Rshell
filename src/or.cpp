#ifndef __OR_CPP__
#define __OR_CPP__

#include "../header/or.h"
#include "../header/base.h"
#include "../header/connector.h"
#include <iostream>

using namespace std;

class Base;
class Connector;


bool Or::execute() {
  return (left->execute()) || (right->execute());
}

#endif
