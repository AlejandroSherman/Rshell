#ifndef _BASE_CPP_
#define _BASE_CPP_
#include "../header/base.h"
#include <iostream>
#include <string>
string checkSpace(string);
string found_connector(string, size_t, vector<string>&, string);
string found_quotation(string, size_t, vector<string>&);
string found_paren(string);
string found_paren(string userinput, char deli, string str)
{
	size_t paren = userinput.find(deli);
	if (paren != string::npos)
	{
		string temp = userinput;
		userinput = "";
		while (paren != string::npos)
		{
			userinput.append(temp.substr(0, paren));
			userinput.append(str);
			temp = temp.erase(0, paren + 1);
			paren = temp.find(deli);
		}
		userinput.append(temp);
	}
	return userinput;
}
vector<string> Base::parsing(string userinput)
{
	size_t pos_space, pos_quote;
	string word;
	vector <string> x;
	bool last_word = false;
	char delimiter_space = ' ';
	char delimiter_quotation = '"';
	string connector;
	if (userinput.find('(') != string::npos)
		userinput = found_paren(userinput, '(', " ( ");
	if (userinput.find(')') != string::npos)
		userinput = found_paren(userinput, ')', " ) ");
	while (true)
	{
		userinput = checkSpace(userinput); //get rid of front and back space
		if (userinput == "" || userinput.at(0) == '#')
			return x;
		pos_quote = userinput.find('"');
		if (pos_quote != string::npos) // if userinput contain '"'
		{
			pos_space = userinput.find(delimiter_space);
			if (pos_space == string::npos || pos_quote < pos_space)	// no space found e.g "hello"
																	// or quotation before space e.g " echo "
				userinput = found_quotation(userinput, pos_quote, x);
			pos_quote = userinput.find('"');
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

		size_t pos_and = word.find("&&");
		size_t pos_or = word.find("||");
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
		//if (userinput.back() == ' ')
		//	userinput.erase(userinput.length() - 1, userinput.length());
		else
			return userinput;
	}
}
string found_connector(string word, size_t pos, vector<string>& x, string connector)	// ';' is found, this function is called
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
	while (pos1 != string::npos)
	{
		string temp;
		if (pos2 != string::npos)		//if second quotation is found
		{
			size_t c1 = userinput.find("&&", pos2 + 1); //check if connector after first set of ""
			size_t c2 = userinput.find("||", pos2 + 1);

			//pos1 = userinput.find('"');
			//pos2 = userinput.find('"', pos1 + 1);
			if (c1 != string::npos) // e.g "hello" && random stuff
			{
				temp = userinput.substr(0, c1);
				temp = temp.erase(pos2, 1);
				temp = temp.erase(pos1, 1);
				x.push_back(temp);
				userinput = userinput.erase(0, c1 - 1);
				return userinput;
			}
			else if (c2 != string::npos && c2 < pos1) // e.g "hello" || random stuff
			{
				temp = userinput.substr(0, c2);
				temp = temp.erase(pos2, 1);
				temp = temp.erase(pos1, 1);
				x.push_back(temp);
				userinput = userinput.erase(0, c2 - 1);
				return userinput;
			}
			userinput = userinput.erase(pos2, 1);
			userinput = userinput.erase(pos1, 1);
			pos1 = userinput.find('"');
			pos2 = userinput.find('"', pos1 + 1);
		}
	}
	x.push_back(userinput);
	return "";
}
#endif