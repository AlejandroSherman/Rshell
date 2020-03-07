#ifndef _OUTPUT_T_CPP_
#define _OUTPUT_T_CPP_

#include "../header/output_t.h"
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

bool Output_T::execute() {//Output truncate: creates a new file if there isn't one and if there is one, overrites it
  string filepath = right->getPath();
  //cout << "Opening file: " << filepath << endl;

  //Open the file with these flags: Write only, if file doesn't exist create one, overrite the file, allow permissions
  int file_fd = open(filepath.c_str(), O_WRONLY |  O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (file_fd < 0) {//Check if failed
  perror("Failed at open"); //Shouldn't traditionally fail as it creates the file if there isn't one
  return false;
  }

  //Didn't fail to open so continue with output redirection
  int stdoutsave = dup(1); //Save stdout
  int check = dup2(file_fd, 1);
  if (check < 0) {//Check if failed
  perror("Failed at dup2"); //doesn't usually fail so never really see this msg
  exit(1); //Force out of the file
  return false;
  }

  //Dup2 didn't fail so now file_fd is at index 1
  //Meaning all output that would normally go to the screen now goes to the file at filepath
  left->execute(); //the output from the leftside now goes to the rightside file
  dup2(stdoutsave, 1); //Restore stdout
  //Dup2 Shouldn't fail at this point, no need to error check

  int final_check = close(file_fd);
  if (final_check == -1) {//-1 is returned on failure
  perror("errno"); //special error msg close uses
  exit(1); //Force out of the file
  return false;
  }
  else if (final_check == 0) {//0 is returned on success, closed correctly
  return true;
  }
  return true; //Shouldn't be reached
}



#endif
