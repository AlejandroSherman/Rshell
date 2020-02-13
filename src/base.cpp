#ifndef _BASE_CPP_
#define _BASE_CPP_
#include "../header/base.h"
#include <iostream>
#include <string>
string checkSpace(string);
string found_connector(string, int, vector<string>&, string);
string found_quotation(string, size_t, vector<string>&);

vector<string> Base::parsing(string userinput)
{
	size_t pos_space, pos_quote;
	string word;
	vector <string> x;
	bool last_word = false;
	char delimiter_space = ' ';
	char delimiter_quotation = '"';
	string connector;
	while (true)
	{
		userinput = checkSpace(userinput); //get rid of front and back space

		pos_quote = userinput.find(delimiter_quotation);

		if (userinput.find('"') != string::npos) // if userinput contain '"'
		{
			pos_space = userinput.find(delimiter_space);
			if (pos_space == string::npos || pos_quote < pos_space)	// no space found e.g "hello"
																	// or quotation before space e.g " echo "
				userinput = found_quotation(userinput, pos_quote, x);
		}

		pos_space = userinput.find(delimiter_space);
		if (pos_space == string::npos) // no more space, last word
		{
			last_word = true;
			word = userinput;
		}
		else {
			word = userinput.substr(0, pos_space);
			userinput = userinput.erase(0, pos_space + 1);
		}

		int pos_and = word.find("&&");
		int pos_or = word.find("||");
		if (pos_and != string::npos && pos_or != string::npos) // both && and || exist
		{
			if (pos_and < pos_or) // && before ||
				word = found_connector(word, pos_and, x, "&&");
			else
				word = found_connector(word, pos_or, x, "||");
			if (word != "" && word.at(0) == '#')					// if the first char is #
				return x;
		}
		else if (pos_and != string::npos)
		{
			word = found_connector(word, pos_and, x, "&&");
			if (word != "" && word.at(0) == '#')					// if the first char is #
				return x;
		}
		else if (pos_or != string::npos)
		{
			word = found_connector(word, pos_or, x, "||");
			if (word != "" && word.at(0) == '#')					// if the first char is #
				return x;
		}
		while (word.find(';') != string::npos) {		// if ; is found, e.g hello;bye, parse into "hello" ";" "bye"
			word = found_connector(word, word.find(';'), x, ";");	// call found semi to handle
			if (word == "")							// if empty string, break loop
				break;
			if (word.at(0) == '#')					// if the first char is #, done parsing
				return x;
		}
		if (word != "")
			x.push_back(word);	//no # or ; found, push the last word
		if (last_word == true)
			return x;
	}
}
string checkSpace(string userinput)
{
	while (true)
	{
		if (userinput == "")
			return userinput;
		if (userinput.front() == ' ')
			userinput.erase(0, 1);
		if (userinput.back() == ' ')
			userinput.erase(userinput.length() - 1, userinput.length());
		else
			return userinput;
	}
}
string found_connector(string word, int pos, vector<string>& x, string connector)	// ';' is found, this function is called
														// handle one ';' each time this is called
{
	if (pos == 0) // if first char is ';', push ';', return word after';'
	{
		x.push_back(connector);
		word = word.substr(connector.length(), word.length());
	}
	else //; is found in middle of word, push char before ';', push ';', return word after ';'
	{
		x.push_back(word.substr(0, pos));

		x.push_back(connector);

		pos = pos + connector.length();
		word = word.substr(pos, word.length());
	}
	return word;
}
string found_quotation(string userinput, size_t pos1, vector<string>& x) // pos1 is the first quotation, pos2 is the second quotation if found
{
	size_t pos2;
	pos2 = userinput.find('"', pos1 + 1); // try to find the second quotation
	// if second quotation found
	// push first quotation
	// push contents btw quotation
	// push second quotation
	if (pos2 != string::npos)
	{
		//x.push_back("\"");temporarily removed these lines to see what the arguments looked like
		x.push_back(userinput.substr(pos1 + 1, pos2 - pos1 - 1));
		//x.push_back("\"");temporarily removed these lines to see what the arguments looked like
		userinput = userinput.erase(pos1, pos2 - pos1 + 1);
		userinput = checkSpace(userinput);
	}
	return userinput;
}
#endif
