#include "../header/base.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semi.h"
#include "../header/command.h"
#include "../header/connector.h"
#include "../header/exit.h"
#include "../header/test.h"
#include "../header/input.h"
#include "../header/output_t.h"
#include "../header/output_a.h"
#include "../header/pipes.h"
#include<sstream>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fcntl.h>
using namespace std;

//function declarations
Command* command_creator(vector<string> tokens, int pos);
//Command creation function creates a command object for the command located at pos
void reverseVec(vector<string> &tokens);
//Prepares input to be passed into ShunYard
vector<string> ShunYard(vector<string> tokens);
//Shunting Yard algorithm
vector<string> update_tokens(vector<string> tokens);
//Helper fucntion that combines strings belonging to one command

//Begin main
int main()
{
  while (true){
	cout <<"$ ";
	string userinput;
	getline(cin,userinput);

	Base *input = new Command();
  vector <string> tokens = (input->parsing(userinput));
 
  if (tokens.size() != 0) {
    
	int pos = 0;

  //if only an operator is entered output error msg and continue
	if((tokens.at(tokens.size()-1) == "&&") && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `&&'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == "||") && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `||'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == ";")  && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `;'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == "<")  && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `newline'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == ">")  && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `newline'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == ">>")  && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `newline'" << endl;
   continue;
  }
  else if ((tokens.at(tokens.size()-1) == "|")  && (tokens.size()==1)){
   cout << "-bash: syntax error near unexpected token `|'" << endl;
   continue;
  }

  //if last thing entered is an operator promt with > for another command, if it's ";" then ignore it, if it's "<" then treat as an error
  if(tokens.at(tokens.size()-1) == "&&"){
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
   cout << "> ";
   string userinput2;
 	 getline(cin,userinput2);
 	 Base *input2 = new Command();
   vector <string> tokens2 = (input2->parsing(userinput2));
   for (int i = 0 ; i < tokens2.size(); ++i){
    tokens.push_back(tokens2.at(i));
   }
 }
   else if (tokens.at(tokens.size()-1) == "|"){
    cout << "> ";
    string userinput2;
    getline(cin,userinput2);
    Base *input2 = new Command();
    vector <string> tokens2 = (input2->parsing(userinput2));
    for (int i = 0 ; i < tokens2.size(); ++i){
    tokens.push_back(tokens2.at(i));
   }
}
  else if (tokens.at(tokens.size()-1) == "<"){
     cout << "-bash: syntax error near unexpected token `newline'" << endl;
     continue;
  }
  else if (tokens.at(tokens.size()-1) == ">"){
    cout << "-bash: syntax error near unexpected token `newline'" << endl;
    continue;
 }
  else if (tokens.at(tokens.size()-1) == ">>"){
   cout << "-bash: syntax error near unexpected token `newline'" << endl;
   continue;
 }
  else if (tokens.at(tokens.size()-1) == ";") {
 	 tokens.resize(tokens.size()-1);
  }
      //Prime the tokens vector to have commands together
      vector <string> tokens_up;
      tokens_up = update_tokens(tokens);
   //END OF RAW INPUT OF INPUT TOKENS. AT THIS POINT BEGIN NEW ALGORITHM
   if(tokens_up.size() >= 2){//Handles edge case where "(command" is only entered
      if((tokens_up.at(tokens_up.size()-1) != ")") && (tokens_up.at(tokens_up.size()-2) == "(")){//handles edge case of missmatched parenthesis
      cout << "Error: Missmatched parenthesis - Try again" << endl;
      continue;
      }
   }
   reverseVec(tokens_up); //reverse the tokens_up vector
   vector <string> postfix_tokens;
   try{//In case there are missmatched parenthesis
   postfix_tokens = ShunYard(tokens_up);//Pefrom SY on tokens_up and return a new postfix vector of strings
   }
   catch(...){//When there are missmatched parenthesis will simply prompt for more input
     continue;
   }
   //reverse(postfix_tokens.begin(), postfix_tokens.end()); //no parenthesis should be present so just reverse and should have our prefix notation
   //this would change to pre fix but currently we keep it in postfix

   if (postfix_tokens.size() == 1){// only one command entered
     Base* single = command_creator(postfix_tokens, pos);
     single->execute();
     continue;
   }

   //Multiple command, need a tree
   stack <Base*> tree;
   Base* left;
   Base* right;

   for(int i = 0 ; i < postfix_tokens.size(); ++i){//Curently no priority in operators and work left to right unless there are parenthesis
     if (postfix_tokens.at(i) == "&&"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new And(left, right));
     }
     else if (postfix_tokens.at(i) == "||"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Or(left, right));
     }
     else if (postfix_tokens.at(i) == ";"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Semi(left, right));
     }
     else if (postfix_tokens.at(i) == "<"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Input(left, right));
     }
     else if (postfix_tokens.at(i) == ">"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Output_T(left, right));
     }
     else if (postfix_tokens.at(i) == ">>"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Output_A(left, right));
     }

     else if (postfix_tokens.at(i) == "|"){
       left = tree.top();
       tree.pop();
       right = tree.top();
       tree.pop();
       tree.push(new Pipes(left, right));
     }
     else{
       tree.push(command_creator(postfix_tokens,i));
     }
   }

//only thing left in the stack is the top node
Base* final = tree.top();
   tree.pop();
   final->execute();
}
}
	return 0;//should never be reached
}
//End of main

//Begin Function definitions
Command* command_creator(vector<string> tokens, int pos){
  string command;
  string temp;

  temp = tokens.at(pos);
  stringstream ss(temp);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> argument(begin, end); //populates the argument vector with the contents of the command i.e ls -a extra
  command = argument.at(0); // command is the first thing in the argument vector

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
    if(argument.size() == 1){
    argument.push_back(" ");
    }
    argument.resize(argument.size()-1);
  	return new Test(command,argument);
  }
  Command* test = new Command(command, argument); 
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
  vector <string> postfix_tokens;
  stack <string> s;
  for(int i = 0 ; i < tokens.size(); i++){
    if ((tokens.at(i) == "&&") || (tokens.at(i) == "||") || (tokens.at(i) == ";") || (tokens.at(i) == "<") || (tokens.at(i) == ">") || (tokens.at(i) == ">>") || (tokens.at(i) == "|")){//token is an operator
      // while((!s.empty()) && (s.top() != ")") && (s.top() != "(") && (tokens.at(i) == "|")){ //Code to have  pipe have less precedence then everything else
      //   postfix_tokens.push_back(s.top());
      //   s.pop();
      // }
      s.push(tokens.at(i));
    }
    else if(tokens.at(i) == "("){//token is a left paren
      s.push(tokens.at(i));
    }
    else if(tokens.at(i) == ")"){//token is a right paren
      while (s.top() != "("){
        postfix_tokens.push_back(s.top());
        s.pop();
        if(s.empty()){
          cout << "Error: Missmatched parenthesis - Try again" << endl;
          throw "This is an exception!";
          return postfix_tokens;
        }
      }
      if (s.top() == "("){
        s.pop();
      }
    }
    else{
      postfix_tokens.push_back(tokens.at(i));
    }
  }
  while (!s.empty()){
    if(s.top() == ")"){
      cout << "Error: Missmatched parenthesis - Try again" << endl;
       throw "This is an exception!";
       return postfix_tokens;
    }
    postfix_tokens.push_back(s.top());
    s.pop();
  }
  return postfix_tokens;
}

vector<string> update_tokens(vector<string> tokens){
  vector <string> tokens_up;
  int pos = 0;
  string temp;
  while(pos < tokens.size()){
    if ((tokens.at(pos) == "||") || (tokens.at(pos) == "&&") || (tokens.at(pos) == ";") || (tokens.at(pos) == "<") || (tokens.at(pos) == ">") || (tokens.at(pos) == ">>") || (tokens.at(pos) == "|") || (tokens.at(pos) == "(") || (tokens.at(pos) == ")")){

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

      while ((tokens.at(pos) != "||") && (tokens.at(pos) != "&&") && (tokens.at(pos) != ";") && (tokens.at(pos) != "<") && (tokens.at(pos) != ">") && (tokens.at(pos) != ">>")  && (tokens.at(pos) != "|") && (tokens.at(pos) != "(") && (tokens.at(pos) != ")")){
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
