#ifndef __AND_CPP__
#define __AND_CPP__

#include "../header/and.h"
#include "../header/base.h"
#include "../header/connector.h"
#include <iostream>

using namespace std;

class Base;
class Connector;


bool And::execute() {
  return (left->execute()) && (right->execute());
}

#endif
