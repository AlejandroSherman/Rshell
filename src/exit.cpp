//stub of exit command file

#ifndef _EXIT_CPP_
#define _EXIT_CPP_
#include <string>
#include <iostream>
#include "exit.hpp"
using namespace std; 

bool exit::execute(string word){
	if(word == "exit")
		exit(0);
	else
		return true;
}
#endif
