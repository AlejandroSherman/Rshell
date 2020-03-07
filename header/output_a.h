#ifndef _OUTPUT_A_H_
#define _OUTPUT_A_H_
#include "connector.h"
#include <string>

using namespace std;

class Output_A:public Connector{
private:

public:
	Output_A(){ }
	Output_A(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
  string getPath(){
    return left->getPath() + " >> " + right->getPath();
  }
};

#endif
