#ifndef _ADD_H_
#define _ADD_H_
#include "connector.h"
#include <string>

using namespace std;

class And:public Connector{
private:

public:
	And(){};
	bool execute(){return false;}
};

#endif
