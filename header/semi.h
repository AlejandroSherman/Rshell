#ifndef _SEMI_H_
#define _SEMI_H_
#include "connector.h"
#include <string>

using namespace std;

class Semi:public Connector{
private:

public:
	Semi(){ }
	Semi(Base *left, Base *right) : Connector(left, right) { }
	bool execute();
	string getPath(){
		return left->getPath() + " ; " + right->getPath(); 
	}
};

#endif
