#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_
#include "../header/base.h"
#include "../header/command.h"
#include <iostream>
#include <string>

using namespace std;

bool Command::execute(){
 cout << "command object here!" << endl << "My command is: " << cmd << endl << "My argument is: " << arg << endl;
}

#endif
