#ifndef _OR_H_
#define _OR_H_
#include "connector.h"
#include <string>

using namespace std;

class Or:public Connector{
private:

public:
	Or(){ }
	Or(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
};

#endif
