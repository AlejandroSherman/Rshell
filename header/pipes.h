#ifndef _PIPES_H_
#define _PIPES_H_

#include "connector.h"
#include <string>

using namespace std;

class Pipes :public Connector {
private:

public:
	Pipes() { }
	Pipes(Base* left, Base* right) : Connector(left, right) { }
	bool execute();
	string getPath() {
		return left->getPath() + " | " + right->getPath();
	}
};

#endif
