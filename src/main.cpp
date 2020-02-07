#include "../header/base.h"
#include "../header/and.h"
#include<iostream>
#include<string>
using namespace std;

string command_plus_flag(string cmd, string flag);

string find_command(vector<string> &tokens, vector<string> commands, int &index);

string update_command(vector<string> &tokens, vector<string> flags, string curr_command, int &pos);

string set_argument(vector<string> &tokens, vector<string> commands, int &pos);

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
 vector <string> valid_anything{"ls", "mkdir", "echo", "git", "cd", "exit", "#", "&&", "||", ";"};
 string command;
 int pos;


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

//Now works with multiple word arguments, and can tell when it encounters another command or connector
//Once working I think at this point we could create a new command like:
// Base task* = new Command(command, argument);
//Need this whole process to eventually be put into a loop or a fork to handle the entire line of tokens
//connector needs it's own functions still so it can do it's own steps and perform the command steps for it's left and right side
//still a work in progress, feel free to add and change things as you see fit

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
