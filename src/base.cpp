#ifndef _BASE_H_
#define _BASE_H_
#include "../header/base.h"
#include <iostream>
#include <string>
string checkSpace(string);

void Base::parsing(string userinput)
{
	size_t pos = 0; 
	string word; 
	while(true)
	{
		userinput = checkSpace(userinput);
		string delimiter = " ";
		pos = userinput.find(delimiter);
		if(pos == userinput.npos)
		{
			word = userinput;
			if(userinput != "")//check if last word is emepty
				cout << word << endl; //last word received
			break;
		}
		else
		{
			word = userinput.substr(0,pos);
			cout << word << endl; //send word to other function
			userinput = userinput.erase(0,pos+delimiter.length());
		}
	}
}
string checkSpace(string userinput)
{
	while (true)
	{
		if(userinput == "")
			return userinput;
		if(userinput.front() == ' ')
			userinput.erase(0,1);
		else
			return userinput;
	}
}

#endif
