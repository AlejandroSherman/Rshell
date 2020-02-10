#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_
#include "../header/base.h"
#include "../header/command.h"
#include <iostream>
#include <string>


using namespace std;

bool Command::execute(string command, vector<string> x) {
    //*****This needs to be changed to make a fork and execute the command by passing in it's argument (return true if succeeds and false if fails)*****
    // need to receive command and its argument
    //cout << endl << "command object here!" << endl << "My command is: " << cmd << endl << "My argument is: " << arg << endl;
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
}

#endif
