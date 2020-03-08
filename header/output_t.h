#ifndef _OUTPUT_T_H_
#define _OUTPUT_T_H_
#include "connector.h"
#include <string>

using namespace std;

class Output_T:public Connector{
private:

public:
	Output_T(){ }
	Output_T(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
  string getPath(){
    return left->getPath() + " > " + right->getPath();
  }
};

#endif
