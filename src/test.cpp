#ifndef _TEST_CPP_
#define _TEST_CPP_
#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "../header/test.h"

using namespace std;

bool Test::execute(){
  struct stat check;
  string path;


  if(wds.size() == 1){//only "test" or "[ ]" was entered
  cout << "(False)" << endl;
  return false;
  }

	if (wds.at(1) == "-e"){//found -e
    if(wds.size() == 2){//only "test -e" or "[ -e ]" was entered
    cout << "(False)" << endl;
    return false;
    }
    if((wds.at(wds.size() -1) != "]") && (wds.size() >= 4)){//Puts an error msg if multiple words put as a test commands arguments
    if(wds.at(0) == "test"){
    cout << "-bash: test: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    if(wds.at(0) == "["){
    cout << "-bash: [: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    }
    path = wds.at(2);
    if (stat(path.c_str(), &check) == 0){//if stat passes it returns 0
      cout << "(True)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }

  else if (wds.at(1) == "-f"){//found -f
    if(wds.size() == 2){//only "test -f" or "[ -f ]"was entered
    cout << "(False)" << endl;
    return false;
    }
    if((wds.at(wds.size() -1) != "]") && (wds.size() >= 4)){//Puts an error msg if multiple words put as a test commands arguments
    if(wds.at(0) == "test"){
    cout << "-bash: test: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    if(wds.at(0) == "["){
    cout << "-bash: [: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    }
    path = wds.at(2);
    if (stat(path.c_str(), &check) == 0){//still check if the basic -e check passes first
      if(S_ISREG(check.st_mode)){//returns 1 if passed
        cout << "(True)" << endl;
        return true;
      }
      else {
        cout << "(False)" << endl;
        return false;
      }
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }

  else if (wds.at(1) == "-d"){//found -d
    if(wds.size() == 2){//only "test -d" or "[ -d ]"was entered
    cout << "(False)" << endl;
    return false;
    }
    if((wds.at(wds.size() -1) != "]") && (wds.size() >= 4)){//Puts an error msg if multiple words put as a test commands arguments
    if(wds.at(0) == "test"){
    cout << "-bash: test: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    if(wds.at(0) == "["){
    cout << "-bash: [: " << wds.at(2) << ": unary operator expected"<< endl;
    }
    }
    path = wds.at(2);
    if (stat(path.c_str(), &check) == 0){//still check if the basic -e check passes first
      if(S_ISDIR(check.st_mode)){//returns 1 if passed
        cout << "(True)" << endl;
        return true;
      }
      else {
        cout << "(False)" << endl;
        return false;
      }
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }

  else {//no flag specified, treat as -e
    path = wds.at(1);
    if((wds.at(wds.size() -1) != "]") && (wds.size() >= 3)){//Puts an error msg if multiple words put as a test commands arguments
    if(wds.at(0) == "test"){
    cout << "-bash: test: " << wds.at(1) << ": unary operator expected"<< endl;
    }
    if(wds.at(0) == "["){
    cout << "-bash: [: " << wds.at(1) << ": unary operator expected"<< endl;
    }
    }
    if (stat(path.c_str(), &check) == 0){//if stat passes it returns 0
      cout << "(True)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }
  return false; //to cover bases, but shouldn't really reach here
}


#endif
