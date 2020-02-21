#include "../header/base.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semi.h"
#include "../header/command.h"
#include "../header/connector.h"
#include "../header/exit.h"
#include "../header/test.h"
#include<sstream>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

//function declarations
vector<string> set_argument(vector<string> &tokens, vector<string> commands, int &pos);
//helper function
Command* command_creator(vector<string> &tokens, int &pos);
Command* command_creator_two(vector<string> &tokens, int &pos);
//Command creation function, gets command, flag, and arguments for one command and leaves blank spaces in the token vector ...
//where these used to be.
void reverseVec(vector<string> &tokens);
vector<string> ShunYard(vector<string> tokens);
vector<string> update_tokens(vector<string> tokens);

int main()
{
  while (true){
	cout <<"$ ";
	string userinput;
	getline(cin,userinput);

	Base *input = new Command();
  vector <string> tokens = (input->parsing(userinput));

  if (tokens.size() != 0){

	int pos = 0;

  vector <Command*> command_objects;
	vector <string> operators; // A vector of connector strings to later be made into a vector of operator objects

  /*
	if(tokens.size() != 0){
	cout << "The tokens vector at the start is: " << endl; //Show what is inside the tokens vector
	for (int i = 0; i < tokens.size(); ++i){
	 cout << tokens.at(i) << endl;
	}
} */

  //if only an operator is entered output error msg and continue
	if((tokens.at(tokens.size()-1) == "&&") && (tokens.size()==1)){
 	 //tokens.resize(tokens.size()-1);
   cout << "-bash: syntax error near unexpected token `&&'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == "||") && (tokens.size()==1)){
 	 //tokens.resize(tokens.size()-1);
   cout << "-bash: syntax error near unexpected token `||'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == ";")  && (tokens.size()==1)){
 	 //tokens.resize(tokens.size()-1);
   cout << "-bash: syntax error near unexpected token `;'" << endl;
   continue;
  }

  //if last thing entered is an operator promt with > for another command
  if(tokens.at(tokens.size()-1) == "&&"){
 	 //tokens.resize(tokens.size()-1);
   cout << "> ";
   string userinput2;
 	 getline(cin,userinput2);
 	 Base *input2 = new Command();
   vector <string> tokens2 = (input2->parsing(userinput2));
   for (int i = 0 ; i < tokens2.size(); ++i){
    tokens.push_back(tokens2.at(i));
   }
  }
  else if (tokens.at(tokens.size()-1) == "||"){
 	 //tokens.resize(tokens.size()-1);
   cout << "> ";
   string userinput2;
 	 getline(cin,userinput2);
 	 Base *input2 = new Command();
   vector <string> tokens2 = (input2->parsing(userinput2));
   for (int i = 0 ; i < tokens2.size(); ++i){
    tokens.push_back(tokens2.at(i));
   }
  }
  else if (tokens.at(tokens.size()-1) == ";") {
 	 tokens.resize(tokens.size()-1);
   /*
   cout << "> ";
   string userinput2;
 	 getline(cin,userinput2);
 	 Base *input2 = new Command();
   vector <string> tokens2 = (input2->parsing(userinput2));
   for (int i = 0 ; i < tokens2.size(); ++i){
    tokens.push_back(tokens2.at(i));
    }
    */
   }
   /*
   for(int i = 0 ; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
     }
    cout << endl;
   */
   //Prime the tokens vector to have commands together
   vector <string> tokens_up;
   tokens_up = update_tokens(tokens);
    /*
   for(int i = 0 ; i < tokens_up.size(); ++i){
    cout << tokens_up.at(i) << " ";
     }
    cout << endl;
   */

   //END OF RAW INPUT OF INPUT TOKENS AT THIS POINT BEGIN NEW ALGORITHM
   if((tokens_up.at(tokens_up.size()-1) != ")") && (tokens_up.at(tokens_up.size()-2) == "(")){//handles edge case of missmatched parenthesis
    cout << "Error: Missmatched parenthesis - Try again" << endl;
    continue;
  }
   reverseVec(tokens_up);
   vector <string> prefix_tokens;
   try{//In case there are missmatched parenthesis
   prefix_tokens = ShunYard(tokens_up);
   }
   catch(...){//When there are missmatched parenthesis will simply prompt for more input
     continue;
   }
   //reverse(prefix_tokens.begin(), prefix_tokens.end()); //no parenthesis should be present so just reverse and should have our prefix notation
   //this would change to pre fix but currently we keep it in postfix

   /*
   for(int i = 0 ; i < prefix_tokens.size(); ++i){
    cout << prefix_tokens.at(i) << " ";
     }
  */

   if (prefix_tokens.size() == 1){// only one command entered
     Base* single = command_creator_two(prefix_tokens, pos);
     single->execute();
     continue;
   }

   stack <Base*> tree;
   Base* left;
   Base* right;
   //Connector* opp;

   for(int i = 0 ; i < prefix_tokens.size(); ++i){
     if (prefix_tokens.at(i) == "&&"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       //opp = new And(left, right);
       tree.push(new And(left, right));
     }
     else if (prefix_tokens.at(i) == "||"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Or(left, right));
     }
     else if (prefix_tokens.at(i) == ";"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Semi(left, right));
     }
     else{
       tree.push(command_creator_two(prefix_tokens,i));
     }
   }
//only thing left in the stack is the top node
Base* final = tree.top();
   tree.pop();
   final->execute();

 /*
 while(pos < tokens.size()){ //Keeps looking for commands untill all of tokens have been viewed
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

 if (operators.size() == 0){ //No operators present, just execute the one command
 command_objects.at(0)->execute();
}
 else { //There are operators, execute them in order
 vector <Connector*> connector_objects;

 if(operators.at(0) == "&&"){//create the first operator
	 connector_objects.push_back(new And(command_objects.at(0), command_objects.at(1)));
 }
 else if (operators.at(0) == "||"){
	 connector_objects.push_back(new Or(command_objects.at(0), command_objects.at(1)));
 }
 else if (operators.at(0) == ";"){
	 connector_objects.push_back(new Semi(command_objects.at(0), command_objects.at(1)));
 }
 int com_loc = 2;

 for (int i = 1; i < operators.size(); ++i){ //the rest of the operators are created
	 if(operators.at(i) == "&&"){
		 connector_objects.push_back(new And(connector_objects.at(i-1), command_objects.at(com_loc)));
		 com_loc++;
	 }
	 else if (operators.at(i) == "||"){
		 connector_objects.push_back(new Or (connector_objects.at(i-1), command_objects.at(com_loc)));
		 com_loc++;
	 }
	 else if (operators.at(i) == ";"){
		 connector_objects.push_back(new Semi(connector_objects.at(i-1), command_objects.at(com_loc)));
		 com_loc++;
	 }
 }
   connector_objects.at(connector_objects.size()-1)->execute();
 }
  */
}
}
	return 0;//should never be reached
}

vector<string> set_argument(vector<string> &tokens, vector<string> commands, int &pos, string comm){ //helper function
	vector<string> arguments;
	arguments.push_back(comm);
	for (; pos < tokens.size(); ++pos){
	for (int i = 0; i < commands.size(); ++i){
		if (tokens.at(pos) == commands.at(i)){
			return arguments;
		}
	}
	//argument = argument + " " + tokens.at(pos);
	arguments.push_back(tokens.at(pos));
	tokens.at(pos) = "";
  }
	return arguments;
}

Command* command_creator(vector<string> &tokens, int &pos){ //funciton used in main that creates commands from the tokens vector
  vector <string> valid_anything{"exit", "#", "&&", "||", ";"};
  string command;

 command = tokens.at(pos);
 tokens.at(pos) = "";
 pos++;

 //the current index of pos is the one after the previously found command
 vector<string> argument;
 if(pos >= tokens.size()){ //fixes an issue where if only one command was passed in e.g : "cd" pos would be out of bounds
	 //vector<string> argument;
   argument.push_back(command);
 }
else{
  //vector<string> argument = set_argument(tokens, valid_anything, pos, command);
  argument = set_argument(tokens, valid_anything, pos, command);
}
if (command == "exit"){
	return new Exit(command);
}
if (command == "test"){
	return new Test(command,argument);
}
if (command == "["){
  if (argument.at(argument.size() - 1) != "]"){
    cout << "-bash: [: missing `]'" << endl;
  }
  argument.resize(argument.size()-1);
	return new Test(command,argument);
}
return new Command(command,argument);
}

Command* command_creator_two(vector<string> &tokens, int &pos){
  string command;
  string temp;

  temp = tokens.at(pos);
  stringstream ss(temp);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> argument(begin, end);
  command = argument.at(0);

  if (command == "exit"){
  	return new Exit(command);
  }
  if (command == "test"){
  	return new Test(command,argument);
  }
  if (command == "["){
    if (argument.at(argument.size() - 1) != "]"){
      cout << "-bash: [: missing `]'" << endl;
    }
    argument.resize(argument.size()-1);
  	return new Test(command,argument);
  }
  return new Command(command,argument);
}

void reverseVec(vector<string> &tokens){
  reverse(tokens.begin(), tokens.end()); //revereses the contents of the vector
  for (int i = 0; i < tokens.size(); ++i){//manually flips each parenthesis
    if (tokens.at(i) == ")"){
      tokens.at(i) = "(";
    }
    else if (tokens.at(i) == "("){
      tokens.at(i) = ")";
    }
  }
  return;
}

vector<string> ShunYard(vector<string> tokens){
  vector <string> prefix_tokens;
  stack <string> s;
  for(int i = 0 ; i < tokens.size(); i++){
    if ((tokens.at(i) == "&&") || (tokens.at(i) == "||") || (tokens.at(i) == ";")){//token is an operator
      s.push(tokens.at(i));
    }
    else if(tokens.at(i) == "("){//token is a left paren
      s.push(tokens.at(i));
    }
    else if(tokens.at(i) == ")"){//token is a right paren
      while (s.top() != "("){
        prefix_tokens.push_back(s.top());
        s.pop();
        if(s.empty()){
          cout << "Error: Missmatched parenthesis - Try again" << endl;
          throw "This is an exception!";
          return prefix_tokens;
        }
      }
      if (s.top() == "("){
        s.pop();
      }
    }
    else{
      prefix_tokens.push_back(tokens.at(i));
    }
  }
  while (!s.empty()){
    if(s.top() == ")"){
      cout << "Error: Missmatched parenthesis - Try again" << endl;
       throw "This is an exception!";
       return prefix_tokens;
    }
    prefix_tokens.push_back(s.top());
    s.pop();
  }
  return prefix_tokens;
}

vector<string> update_tokens(vector<string> tokens){
  vector <string> tokens_up;
  int pos = 0;
  string temp;
  while(pos < tokens.size()){
    if ((tokens.at(pos) == "||") || (tokens.at(pos) == "&&") || (tokens.at(pos) == ";") || (tokens.at(pos) == "(") || (tokens.at(pos) == ")")){
      tokens_up.push_back(tokens.at(pos));
      pos++;
    }
    else {
      temp = tokens.at(pos);
      pos++;
      if (pos == tokens.size()){
        tokens_up.push_back(temp);
        break;
      }
      //while (pos < tokens.size()){
      while ((tokens.at(pos) != "||") && (tokens.at(pos) != "&&") && (tokens.at(pos) != ";") && (tokens.at(pos) != "(") && (tokens.at(pos) != ")")){
        temp = temp + " " + tokens.at(pos);
        pos++;
        //continue;
        if (pos == tokens.size()){
          break;
        }
      }
     //}
      tokens_up.push_back(temp);
    }
}
  return tokens_up;
}
