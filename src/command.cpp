#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_
#include "../header/base.h"
#include "../header/command.h"
#include <iostream>
#include <string>

using namespace std;

bool Command::execute(){ //This needs to be changed to make a fork and execute the command by passing in it's argument (return true if succeeds and false if fails)
 cout << "command object here!" << endl << "My command is: " << cmd << endl << "My argument is: " << arg << endl;
}

#endif
