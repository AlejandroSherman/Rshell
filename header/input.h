#ifndef _INPUT_H_
#define _INPUT_H_
#include "connector.h"
#include <string>

using namespace std;

class Input:public Connector{
private:

public:
	Input(){ }
	Input(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
  string getPath(){
    return left->getPath() + " < " + right->getPath();
  }
};

#endif
