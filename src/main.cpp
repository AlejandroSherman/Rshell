#include "../header/base.h"
#include "../header/and.h"
#include<iostream>
#include<string>
using namespace std;

string command_plus_flag(string cmd, string flag){
	string result = cmd + " " + flag;
	return result;
}

int main()
{
	cout <<"guest@rshell:~$ ";
	string userinput;
	getline(cin,userinput);
	Base *input = new And();


	vector <string> tokens = (input->parsing(userinput));
	cout << "Size of tokens vector is: " << tokens.size() << endl;
	cout << "Contents of tokens vector are:" << endl;
	for (int i = 0; i < tokens.size(); ++i){
		cout << tokens.at(i) << endl;
	}

 vector <string> valid_commands {"ls", "mkdir", "echo", "git", "cd"}; //exit and comment are special and are handled in the parser
 vector <string> valid_flags{"-a", "-e", "-d", "-lR", "/"};
 string command;

 for (int i = 0; i < tokens.size(); ++i){
	 for (int j = 0; j < valid_commands.size(); ++j){
		 if (tokens.at(i) == valid_commands.at(j)){
			 command = tokens.at(i);
			 break;
		 }
	 }
 }
cout << command << endl;


	return 0;
}
