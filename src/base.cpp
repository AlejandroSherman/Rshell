#ifndef _BASE_CPP_
#define _BASE_CPP_
#include "../header/base.h"
#include <iostream>
#include <string>
string checkSpace(string);

vector<string> Base::parsing(string userinput) //*****parser needs to be updated to separate a ";" to it's own token*****
{ //*****parser needs to know when a "#" is found so the rest of the input is ignored, parser also needs to have anything that is between quotations to be treated as one token*****
	size_t pos = 0;
	string word;
	vector <string> x;
	while(true)
	{
		userinput = checkSpace(userinput);
		string delimiter = " ";
		pos = userinput.find(delimiter);
		if(pos == userinput.npos)
		{
			word = userinput;
			if(userinput != "")//check if last word is emepty
				//cout << word << endl; //last word received
				x.push_back(word);
				return x;
			//break;
		}
		else
		{
			word = userinput.substr(0,pos);
			x.push_back(word);
			//cout << word << endl; //send word to other function
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
