#ifndef _BASE_CPP_
#define _BASE_CPP_
#include "../header/base.h"
#include <iostream>
#include <string>
string checkSpace(string);
string found_semi(string, int, vector<string>&);
void found_comment(string, int, vector<string>&);
string found_quotation(string, size_t, vector<string>&);

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
		x.push_back("\"");
		x.push_back(userinput.substr(pos1 + 1, pos2 - pos1 - 1));
		x.push_back("\"");
		userinput = userinput.erase(pos1, pos2 - pos1 + 1);
		userinput = checkSpace(userinput);
	}
	return userinput;
}
vector<string> Base::parsing(string userinput) //*****parser needs to be updated to separate a ";" to it's own token*****
{ //*****parser needs to know when a "#" is found so the rest of the input is ignored, parser also needs to have anything that is between quotations to be treated as one token*****
	size_t pos = 0, pos_quote = 0;
	string word;
	vector <string> x;

	char delimiter_space = ' ';
	char delimiter_quotation = '"';
	while (true)
	{
		userinput = checkSpace(userinput);
		// check for quotation,
		pos_quote = userinput.find(delimiter_quotation);
		if (pos_quote != string::npos) // if quotation found
		{
			if (pos == string::npos || pos_quote < pos)		// if no space is found while quotation is found or
			{												// quotation comes first, call found_quotation
				userinput = found_quotation(userinput, pos_quote, x);
			}
			// else, the first word has no quotation, continue
		}
		pos = userinput.find(delimiter_space);
		if (pos == userinput.npos)//If no space found, then this is the last word
		{
			word = userinput;
			//check if last word is emepty
			//case for last word received

			while (word.find(';') != string::npos && word.find('#') != string::npos) // if both ; and # is found in word
			{
				if (word.find(';') < word.find('#'))	// if ';' first, e.g h;e#llo
					word = found_semi(word, word.find(';'), x);	// process ';' then compare again in case more ';' is found
				else {									// if "#" first, e.g h#e'llo
					found_comment(word, word.find('#'), x);				// process #, then return vector x
					return x;
				}
			}
			// if not both ';' and '#' found, check seprately
			while (word.find(';') != string::npos) // if ';' is found, loop until no ';' is found
			{
				if (word.find(';') != string::npos)
					word = found_semi(word, word.find(';'), x);
				else
					return x;
			}

			// if comment is found, process comment, then return vector x
			if (word.find('#') != string::npos)
			{
				found_comment(word, word.find('#'), x);
				return x;
			}

			// no quotation or comment found, push the word to vector, return vector x
			//if last word is "" then no check needed, return vector x
			if (word == "")
				return x;

			x.push_back(word);
			return x;

		}
		else // case for not the last word
		{
			word = userinput.substr(0, pos);
			while (word.find(';') != string::npos && word.find('#') != string::npos) // if both ; and # is found in word
			{
				if (word.find(';') < word.find('#') != string::npos)	// if ';' first, e.g h;e#llo
					word = found_semi(word, word.find(';'), x);					// process ';' then compare again in case more ';' is found
				else {													// if "#" first, e.g h#e'llo
					found_comment(word, word.find('#'), x);						// process #, then return vector x
					return x;
				}
			}
			// if not both ';' and '#' found, check seprately
			while (word.find(';') != string::npos) // if ';' is found, loop until no ';' is found
			{
				word = found_semi(word, word.find(';'), x);
			}

			// if comment is found, process comment, then return vector x
			if (word.find('#') != string::npos)
			{
				found_comment(word, word.find('#'), x);
				return x;
			}
			if (word != "")
				// no quotation or comment found, push the word to vector, erase the word
				x.push_back(word);

			userinput = userinput.erase(0, pos + 1);
		}
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
string found_semi(string word, int pos, vector<string>& x)	// ';' is found, this function is called
														// handle one ';' each time this is called
{
	if (pos == 0) // if first char is ';', push ';', return word after';'
	{
		x.push_back(";");
		word = word.substr(1, word.length());
	}
	else //; is found in middle of word, push char before ';', push ';', return word after ';'
	{
		x.push_back(word.substr(0, pos));

		x.push_back(";");

		pos++;
		word = word.substr(pos, word.length());
	}
	return word;
}
void found_comment(string word, int pos, vector<string>& x) //'#' is found, this function is called
{
	if (pos != 0) // if the first char is not '#', push char before '#'
		x.push_back(word.substr(0, pos));
}
#endif
