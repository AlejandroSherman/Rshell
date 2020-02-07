#include "../header/base.h"
#include "../header/and.h"
#include<iostream>
#include<string>
using namespace std;

string command_plus_flag(string cmd, string flag);

string find_command(vector<string> &tokens, vector<string> commands, int &index);

string update_command(vector<string> &tokens, vector<string> flags, string curr_command, int &pos);

string set_argument(vector<string> &tokens, vector<string> commands, int &pos);

string command_creator(vector<string> &tokens, int &pos);
//Command creation function, gets command, flag, and arguments for one command and leaves blank spaces in the token vector ...
//where these used to be.
//This function currently returns a string of the command and it's argument, but this function should actually return a new command object
//Example: should return new Command(command, argument);
//Currently returns a string for ease of premilinary testing



int main()
{
	cout <<"guest@rshell:~$ ";
	string userinput;
	getline(cin,userinput);
	Base *input = new And();

  vector <string> tokens = (input->parsing(userinput));
	int pos = 0;

 while(pos < tokens.size()){ //Keeps looking for commands untill all of tokens has been viewed
 string command_and_argument = command_creator(tokens, pos);
 cout << "The command and argument is: " << command_and_argument << endl;
 cout << "This function should actually create a command that can be executed in a fork" << endl;
 //place the returned command into a vector of commands
 //here check if tokens.at(pos) is an operator.
 //if it is take note of it and do something with it later
 //continue to collect the rest of the commands
}

	return 0;
}

string command_plus_flag(string cmd, string flag){
	string result = cmd + " " + flag;
	return result;
}

string find_command(vector<string> &tokens, vector<string> commands, int &index){
	string command = "";
	for (int i = 0; i < tokens.size(); ++i){
 	 for (int j = 0; j < commands.size(); ++j){
 		 if (tokens.at(i) == commands.at(j)){
 			 command = tokens.at(i);
 			 index = i+1;
			 tokens.at(i) = "";
			 return command;
 		 }
 	 }
  }
	return command;
}

string update_command(vector<string> &tokens, vector<string> flags, string curr_command, int &pos){
  string new_command = curr_command;
	for (int i = 0; i < flags.size(); ++i){
		if (flags.at(i) == tokens.at(pos)){
			new_command = command_plus_flag(curr_command, flags.at(i));
			tokens.at(pos) = "";
			pos = pos+1;
			return new_command;
		}
	}
	return new_command;
}

string set_argument(vector<string> &tokens, vector<string> commands, int &pos){
	string argument = "";
	for (; pos < tokens.size(); ++pos){
	for (int i = 0; i < commands.size(); ++i){
		if (tokens.at(pos) == commands.at(i)){
			return argument;
		}
	}
	argument = argument + " " + tokens.at(pos);
	tokens.at(pos) = "";
  }
	return argument;
}

string command_creator(vector<string> &tokens, int &pos){
	vector <string> valid_commands {"ls", "mkdir", "echo", "git", "cd"}; //exit and comment are special and are handled in the parser
  vector <string> valid_flags{"-a", "-e", "-d", "-lR", "/"};
  vector <string> valid_anything{"ls", "mkdir", "echo", "git", "cd", "exit", "#", "&&", "||", ";"};
  string command;

	cout << "Size of tokens vector is: " << tokens.size() << endl;
	cout << "Contents of tokens vector are:" << endl;
	for (int i = 0; i < tokens.size(); ++i){
		cout << tokens.at(i) << endl;
	}

 command = find_command(tokens, valid_commands, pos);

 cout << endl << "The command to be passed is: "<< command << endl;

 cout << endl << "Contents of tokens vector now are:" << endl;
 for (int i = 0; i < tokens.size(); ++i){
	 cout << tokens.at(i) << endl;
 }
 //the current index of pos is the one after the previously found command
 if (pos >= tokens.size()){ //fixes an issue where if only one command was passed in e.g : "cd" pos would be out of bounds
	 pos = pos-1;
 }

 command = update_command(tokens, valid_flags, command, pos);
 cout << endl << "Now the command is: " << command << endl;
 cout << endl << "Contents of tokens vector now are:" << endl;
 for (int i = 0; i < tokens.size(); ++i){
 	cout << tokens.at(i) << endl;
 }

string argument;
argument = set_argument(tokens, valid_anything, pos);

argument.erase(0, 1); //argument always has a leading whitespace, removing it here

cout << endl << "The command to be created is: " << command << " with argument: " << argument << endl;
cout << endl << "Contents of tokens vector now are:" << endl;
for (int i = 0; i < tokens.size(); ++i){
 cout << tokens.at(i) << endl;
}

command = command + " argument: " + argument;
return command;

//Now works with multiple commands
//Now works with multiple word arguments, and can tell when it encounters another command or connector
//This function currently returns a string for ease of tesing, but should actually return a command object created like:
// Base task* = new Command(command, argument); return task... or something like this
//still a work in progress, feel free to add and change things as you see fit
//Prints state of token vector for ease of testing

}
