#ifndef _ADD_H_
#define _ADD_H_
#include "connector.h"
#include <string>

using namespace std;

class And:public Connector{
private:

public:
	And(){ }
	And(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
	string getPath(){
		return left->getPath() + " && " + right->getPath(); 
	}
};

#endif
