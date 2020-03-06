#ifndef _INPUT_CPP_
#define _INPUT_CPP_

#include "../header/input.h"
#include "../header/base.h"
#include "../header/connector.h"
#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

using namespace std;

class Base;
class Connector;

bool Input::execute() {
  string filepath = "hello.txt"; //Hard coded for testing purposes, will be removed
  cout << "Reading file: hello.txt" << endl; //Will also be removed

  int file_fd = open(filepath.c_str(), O_RDONLY);
  if (file_fd < 0) {//Check if failed
  perror("Failed at open");
  exit(1);
  return false;
  }

  //Didn't fail to open so continue with input redirection
  int stdinsave = dup(0); //Save stdin
  int check = dup2(file_fd, 0);
  if (check < 0) {//Check if failed
  perror("Failed at dup2");
  exit(1);
  return false;
  }

  //Dup2 didn't fail so now file_fd is at index 0
  //Meaning all input that would normally comefrom to the keyboard now comes from the file at filepath
  left->execute(); //the input goes into the left side
  dup2(stdinsave, 0); //Restore stdin
  //Dup2 Shouldn't fail at this point, no need to error check

  int final_check = close(file_fd);
  if (final_check == -1) {//-1 is returned on failure
  perror("errno"); //special error msg close uses
  exit(1);
  return false;
  }
  else if (final_check == 0) {//0 is returned on success
  return true;
  }
  return true; //Shouldn't be reached
}



#endif
