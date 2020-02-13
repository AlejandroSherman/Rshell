#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_
#include "../header/base.h"
#include "../header/command.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


using namespace std;

bool Command::execute() {
   //vector<string> x;
    //cout << "command object here!" << endl << "My command is: " << cmd << " My arguments are: ";
    //for(int i = 0; i < args.size(); ++i){
    //    cout << args.at(i)<< " ";
    //}
    //cout << "The size of argument vector: " << args.size() << endl;
    //cout << "Start executing ";
    //cout << endl;

    const char* cmd_exe = cmd.c_str(); 
    bool result = true;
    char* arg[500];
    int i = 0;
    pid_t pid = fork();
    while (i < args.size())
    {
        arg[i] = (char*)args.at(i).c_str();
        i++;
    }
    arg[i] = NULL;
    
    if (pid < 0) //error on forking
        perror("fork() error");

    else if (pid == 0) {                    //child process
        if (execvp(arg[0], arg) == -1) {      //error on execvp
            perror("Execvp returned, error execvp");
            exit(1);
        }
    }

    else if (pid > 0) {                     //parent process
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("Wait() error");
            result = false;
        }
        int exit_status = WEXITSTATUS(status);
        if (exit_status != 0)           //if normal, should return 0
        {
            printf("Child failed, exit statlsus of the child was %d\n", exit_status);
            result = false;
        }
    }
    return result; 
}

#endif
