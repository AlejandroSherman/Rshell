#ifndef _EXIT_H_
#define _EXIT_H_
#include "command.h"
#include <string>

class Exit : public Command
{
private:
public:
	Exit(){};
	bool execute(string word)
	{
		if(word == "exit")
			exit(0);
		else
			return true;
	}
};
#endif
