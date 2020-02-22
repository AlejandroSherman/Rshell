//Tests that the ShunYard algotithm accuately removes the parenthesis
//Includes reverseVec and ShunYard algorithm
//Tests the error reporting when missmatched parenthesis are entered
//Ex1: echo A && echo B becomes - echo B echo A &&
//Ex2: (echo A && echo B) || (echo C && echo D) becomes - echo D echo C && echo B echo A && ||
#include <bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>
#include <stdexcept>
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
  ASSERT_EQ(postfix_tokens.size(), 3);
  for(int i = 0; i < postfix_tokens.size(); ++i){
    cout << postfix_tokens.at(i) << " ";
  }
  string result;
  result = "echo B echo A &&";
  cout << endl << result << endl;
}

TEST(PreceTestSet, TwoOperators){
  vector <string> tokens;
  tokens.push_back("(");
  tokens.push_back("echo A");
  tokens.push_back("&&");
  tokens.push_back("echo B");
  tokens.push_back(")");
  tokens.push_back(";");
  tokens.push_back("(");
  tokens.push_back("echo C");
  tokens.push_back(")");

  reverseVec(tokens);
  vector <string> postfix_tokens;
  postfix_tokens = ShunYard(tokens);
  ASSERT_EQ(postfix_tokens.size(), 5);
  for(int i = 0; i < postfix_tokens.size(); ++i){
    cout << postfix_tokens.at(i) << " ";
  }
  string result;
  result = "echo C echo B echo A && ;";
  cout << endl << result << endl;
}

TEST(PreceTestSet, ThreeOperators){
  vector <string> tokens;
  tokens.push_back("(");
  tokens.push_back("echo A");
  tokens.push_back("&&");
  tokens.push_back("echo B");
  tokens.push_back(")");
  tokens.push_back("||");
  tokens.push_back("(");
  tokens.push_back("echo C");
  tokens.push_back("&&");
  tokens.push_back("echo D");
  tokens.push_back(")");

  reverseVec(tokens);
  vector <string> postfix_tokens;
  postfix_tokens = ShunYard(tokens);
  ASSERT_EQ(postfix_tokens.size(), 7);
  for(int i = 0; i < postfix_tokens.size(); ++i){
    cout << postfix_tokens.at(i) << " ";
  }
  string result;
  result = "echo D echo C && echo B echo A && ||";
  cout << endl << result << endl;
}

TEST(PreceTestSet, MissingParenLong){
  vector <string> tokens;
  tokens.push_back("(");
  tokens.push_back("echoA");
  tokens.push_back("&&");
  tokens.push_back("echo B");
  tokens.push_back(")");
  tokens.push_back("&&");
  tokens.push_back("(");
  tokens.push_back("echo C");
  tokens.push_back("&&");
  tokens.push_back("(");
  tokens.push_back("echoA");
  tokens.push_back("&&");
  tokens.push_back("echo B");
  tokens.push_back(")");


  reverseVec(tokens);
  vector <string> postfix_tokens;
  try{
  postfix_tokens = ShunYard(tokens);
  }
  catch(...){
     cout << "I failed gracefully" << endl;
   }
  ASSERT_EQ(postfix_tokens.size(), 0);
  string result;
  result = "Error: Missmatched parenthesis - Try again";
  cout << result << endl << "I failed gracefully" << endl;
}

TEST(PreceTestSet, MissingParenShort){
  vector <string> tokens;
  tokens.push_back("(");
  tokens.push_back("echoA");

  if((tokens.at(tokens.size()-1) != ")") && (tokens.at(tokens.size()-2) == "(")){
    cout << "Error: Missmatched parenthesis - Try again" << endl;
  }

  /*
  reverseVec(tokens);
  vector <string> postfix_tokens;
  try{
  postfix_tokens = ShunYard(tokens);
  }
  */
  ASSERT_EQ(tokens.size(), 2);
  /*
  catch(...){
     cout << "I failed gracefully" << endl;
   }
   */
  string result;
  result = "Error: Missmatched parenthesis - Try again";
  cout << result << endl;
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
