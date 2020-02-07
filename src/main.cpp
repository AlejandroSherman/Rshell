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
 int pos;

 for (int i = 0; i < tokens.size(); ++i){
	 for (int j = 0; j < valid_commands.size(); ++j){
		 if (tokens.at(i) == valid_commands.at(j)){
			 command = tokens.at(i);
			 pos = i;
			 break;
		 }
	 }
 }
cout << "The command to be passed is: "<< command << endl;
pos = pos+1;
string new_command;

for (int i = 0; i < valid_flags.size(); ++i){
	if (valid_flags.at(i) == tokens.at(pos)){
		new_command = command_plus_flag(command, valid_flags.at(i));
		break;
	}
}

cout << "Now the command is :" << new_command << endl;
pos = pos+1;
string argument = tokens.at(pos);

cout << "The command to be created is :" << new_command << " with argument: " << argument << endl;
//Only works with one word arguments, need a way to know when the argument ends and another connector or command begins
//Still in preliminary stage
//Once working I think at this point we could create a new command like:
// Base task* = new Command(new_command, argument);
//Maybe we can make the steps done above into a function that trys to do this for all commands in the tokens vector
//and perhaps a connector can do it's own steps and perform the command steps for it's left and right side
//still unsure how it'll all come together lol

	return 0;
}
