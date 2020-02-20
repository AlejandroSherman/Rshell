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

bool Test::execute(){//currently designed to only successfully handle the first form of test flag or no flag and path
  struct stat check;
  string path;


  if(wds.size() == 1){//only "test" was entered
  cout << "(False)" << endl;
  return false;
  }

	if (wds.at(1) == "-e"){//found -e
    if(wds.size() == 2){//only "test -e" was entered
    cout << "(False)" << endl;
    return false;
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
    if(wds.size() == 2){//only "test -f" was entered
    cout << "(False)" << endl;
    return false;
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
    if(wds.size() == 2){//only "test -d" was entered
    cout << "(False)" << endl;
    return false;
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
