#ifndef _TEST_H_
#define _TEST_H_
#include "command.h"
#include <string>
#include <vector>
using namespace std;

class Command;

class Test : public Command
{
private:
	string wd;
  vector<string> wds;
public:
	Test(string input, vector<string> arguments){
    wd = input;
    wds = arguments;
	};
	bool execute();
};
#endif
