//stub of exit command file

#ifndef _EXIT_CPP_
#define _EXIT_CPP_
#include <string>
#include <iostream>
#include "exit.h"
using namespace std;

bool exit::execute(){
	if(wd == "exit")
		exit(0);
	else
		return true;
}
#endif
