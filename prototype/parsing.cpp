#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int main()
{
	printf("This is Parsing being called by main.cpp\n");
	printf("Begin Parsing\n");

	string userinput;
	cout << "Enter a list of strings, seperate each with && in between" << endl; 
	getline(cin, userinput);
	cout << userinput << endl; 
	string delimiter = "&&";
	unsigned int position = 0; 
	string word;
		
	position = userinput.find(delimiter);	
	word = userinput.substr(0, position); //capture word from position 0 to delimiter
	cout << word << endl; 
	
	if (word == "ls -a") 
		system("ls -a");
	userinput.erase(0, position + delimiter.length()); //erase the word from whole string
	cout << userinput << endl;
	return 0;
}
