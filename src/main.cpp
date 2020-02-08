#include "../header/base.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semi.h"
#include "../header/command.h"
#include "../header/connector.h"
#include<iostream>
#include<string>
using namespace std;

string command_plus_flag(string cmd, string flag);

string find_command(vector<string> &tokens, vector<string> commands, int &index);

string update_command(vector<string> &tokens, vector<string> flags, string curr_command, int &pos);

string set_argument(vector<string> &tokens, vector<string> commands, int &pos);

Command* command_creator(vector<string> &tokens, int &pos);
//Command creation function, gets command, flag, and arguments for one command and leaves blank spaces in the token vector ...
//where these used to be.




int main() //compile in ubunutu with: g++ main.cpp base.cpp command.cpp and.cpp or.cpp semi.cpp, and then do: ./a.out
{ //example input: cd -e hello there && ls -a how are you doing
	cout <<"guest@rshell:~$ ";
	string userinput;
	getline(cin,userinput);
	Base *input = new Command();

  vector <string> tokens = (input->parsing(userinput));
	int pos = 0;

  vector <Command*> command_objects;
	vector <string> operators; // A vector of connector strings to later be made into a vector of operator objects

	cout << "The tokens vector at the start is: " << endl; //Show what is inside the tokens vector
	for (int i = 0; i < tokens.size(); ++i){
	 cout << tokens.at(i) << endl;
	}

 while(pos < tokens.size()){ //Keeps looking for commands untill all of tokens has been viewed
 command_objects.push_back(command_creator(tokens, pos)); //the command is placed into a vector of commands
 if(pos != tokens.size()){
 if ((tokens.at(pos) == "&&") || (tokens.at(pos) == "||") || (tokens.at(pos) == ";")){ //Checks if an operator has been encountered
	 operators.push_back(tokens.at(pos));
	 tokens.at(pos) = "";
	 pos = pos+1;
 }
}
 //continue to collect the rest of the commands
}
//once all of tokens have been handled, go through the vector of operators and execute them using their execute fuction, and do so based on the commands that have been entered

 if (operators.size() == 0){ //No operators just execute the one command
 command_objects.at(0)->execute();
}
 else { //There are operators, execute them in order
 int c1 = 0;
 int c2 = 1;
 vector <Connector*> connector_objects;
 for (int i = 0; i < operators.size(); ++i){
	 if(operators.at(i) == "&&"){
		 connector_objects.push_back(new And(command_objects.at(c1), command_objects.at(c2)));
		 c1 = c1+1;
		 c2 = c2+1;
	 }
	 else if (operators.at(i) == "||"){
		 connector_objects.push_back(new Or(command_objects.at(c1), command_objects.at(c2)));
		 c1 = c1+1;
		 c2 = c2+1;
	 }
	 else if (operators.at(i) == ";"){
		 connector_objects.push_back(new Semi(command_objects.at(c1), command_objects.at(c2)));
		 c1 = c1+1;
		 c2 = c2+1;
	 }
 }
 //should now have a vector of operators, execute them
 for (int i = 0; i < connector_objects.size(); ++i){
	 connector_objects.at(i)->execute();
 }
 }

 cout << endl << "The tokens vector at the end is: " << endl; //Show what is inside the tokens vector
 for (int i = 0; i < tokens.size(); ++i){
	cout << tokens.at(i) << endl;
 }

	return 0;
}

string command_plus_flag(string cmd, string flag){ //helper function
	string result = cmd + " " + flag;
	return result;
}

string find_command(vector<string> &tokens, vector<string> commands, int &index){ //helper function
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

string update_command(vector<string> &tokens, vector<string> flags, string curr_command, int &pos){ //helper function
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

string set_argument(vector<string> &tokens, vector<string> commands, int &pos){ //helper function
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

Command* command_creator(vector<string> &tokens, int &pos){ //funciton used in main that creates commands from the tokens vector
	vector <string> valid_commands {"ls", "mkdir", "echo", "git", "cd", "exit"};
  vector <string> valid_flags{"-a", "-e", "-d", "-lR", "/"};
  vector <string> valid_anything{"ls", "mkdir", "echo", "git", "cd", "exit", "#", "&&", "||", ";"};
  string command;

	// cout << "Size of tokens vector is: " << tokens.size() << endl;
	// cout << "Contents of tokens vector are:" << endl;
	// for (int i = 0; i < tokens.size(); ++i){
	// 	cout << tokens.at(i) << endl;
	// }

 command = find_command(tokens, valid_commands, pos);

 // cout << endl << "The command to be passed is: "<< command << endl;
 //
 // cout << endl << "Contents of tokens vector now are:" << endl;
 // for (int i = 0; i < tokens.size(); ++i){
	//  cout << tokens.at(i) << endl;
 // }
 //the current index of pos is the one after the previously found command
 if (pos >= tokens.size()){ //fixes an issue where if only one command was passed in e.g : "cd" pos would be out of bounds
	 pos = pos-1;
 }

 command = update_command(tokens, valid_flags, command, pos);
 // cout << endl << "Now the command is: " << command << endl;
 // cout << endl << "Contents of tokens vector now are:" << endl;
 // for (int i = 0; i < tokens.size(); ++i){
 // 	cout << tokens.at(i) << endl;
 // }

string argument;
argument = set_argument(tokens, valid_anything, pos);

argument.erase(0, 1); //argument always has a leading whitespace, removing it here

// cout << endl << "The command to be created is: " << command << " with argument: " << argument << endl;
// cout << endl << "Contents of tokens vector now are:" << endl;
// for (int i = 0; i < tokens.size(); ++i){
//  cout << tokens.at(i) << endl;
// }

//command = command + " argument: " + argument;
//if (command == "exit"){//untested
	//return new Exit(command);
//}
return new Command(command,argument);

//Now works with multiple commands
//Now works with multiple word arguments, and can tell when it encounters another command or connector
// can be changed if needed
// needs to be updated to handle "exit"
}
