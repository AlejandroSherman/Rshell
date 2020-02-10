#ifndef __SEMI_CPP__
#define __SEMI_CPP__

#include "../header/semi.h"
#include "../header/base.h"
#include "../header/connector.h"
#include <iostream>

using namespace std;

class Base;
class Connector;


bool Semi::execute() {
  left->execute();
  return right->execute();
}

#endif
