//Tests that the ShunYard algotithm accuately removes the parenthesis
//Includes reverseVec and ShunYard algorithm
//In each test mock create a generic vector of tokens and conduct tests to ensure the functions return in the desired form
//Can also try and catch missing parenthesis
//Ex1: echo A && echo B becomes - echo B echo A &&
//Ex2: (echo A && echo B) || (echo C && echo D) becomes - echo D echo C && echo B echo A && ||
#include <bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#ifndef _PRECE_TEST_H_
#define _PRECE_TEST_H_

void reverseVec(vector<string> &tokens);
vector<string> ShunYard(vector<string> tokens);

TEST(PreceTestSet, oneOperator){
  vector <string> tokens;
  tokens.push_back("echo A");
  tokens.push_back("&&");
  tokens.push_back("echo B");

  reverseVec(tokens);
  vector <string> postfix_tokens;
  postfix_tokens = ShunYard(tokens);
  ASSERT_EQ(tokens.size(), 3);
  for(int i = 0; i < prefix_tokens.size(); ++i){
    cout << prefix_tokens.at(i) << " ";
  }
  string result;
  result = "echo B echo A &&"
  cout << result;
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


#endif
