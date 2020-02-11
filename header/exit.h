#ifndef _EXIT_H_
#define _EXIT_H_
#include "command.h"
#include <string>
using namespace std;

class Exit : public Command
{
private:
	string wd;
public:
	Exit(string word){
		wd = word;
	};
	bool execute(){
		if(wd == "exit")
		exit(0);
		//cout << "This is exit here, I would be exiting now" << endl;
		//else
			//return true;
	}
};
#endif
