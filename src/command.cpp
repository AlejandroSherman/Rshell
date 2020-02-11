#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_
#include "../header/base.h"
#include "../header/command.h"
#include <iostream>
#include <string>


using namespace std;

bool Command::execute() {
   //vector<string> x;
    cout << "command object here!" << endl << "My command is: " << cmd << " My arguments are: ";
    for(int i = 0; i < args.size(); ++i){
      cout << args.at(i)<< " ";
    }
    cout << endl;
    /*
    bool result = true;
    char* arg[500];
    cout << endl;
    int i = 0;
    while (i < x.size())
    {
        arg[i] = (char*)x.at(i).c_str();
        i++;
    }
    arg[i] = NULL;

    pid_t pid = fork();
    if (pid < 0) //error on forking
        perror("fork() error");

    else if (pid == 0) {                    //child process
        if (execvp(arg[0], arg) < 0) {      //error on execvp
            printf("An execvp() error/n");
            result = false;
            exit(-1);
        }
    }

    else if (pid > 0) {                     //parent process
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("wait() error");
            result = false;
        }
        if (WIFEXITED(status) != 0)           //if normal, should return 0
        {
            int exit_status = WEXITSTATUS(status);
            printf("Exit status of the child was %d\n", exit_status);
            result = false;
        }

    }
    return result;
    */
}

#endif
