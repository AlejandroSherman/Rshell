#ifndef _PIPES_CPP_
#define _PIPES_CPP_
#include "../header/pipes.h"
#include "../header/base.h"
#include "../header/connector.h"
#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std; 

class Base;
class Connector;
void dup2check(int check) {
	if (check < 0)
	{
		perror("dup2 failed");
		exit(1);
	}
}
void forkcheck(pid_t check) {
	if (check < 0)
	{
		perror("Fork failed in pipes");
		exit(1);
	}
}
void pipeExe(Base* cmd) {
	vector<string> args = cmd->getVector();
	char* arg[500];
	int i = 0; 
	while(i < args.size()) {
		arg[i] = (char*)args.at(i).c_str();
		i++;
	}
	arg[i] = NULL;
	const char* cmd_exe = args.at(0).c_str();
	if (execvp(cmd_exe, arg) == -1) {      //error on execvp
		printf("%s: command not found\n", cmd_exe);
		exit(1);
	}
}
bool Pipes::execute() {
	cout << "Pipe is called!" << endl; 
	const int READ = 0, WRITE = 1; 
	int pipefd[2], stdfd_in, stdfd_out, check; 
	pid_t cpid1, cpid2; 
	pipe(pipefd); 
	cpid1 = fork(); 
	forkcheck(cpid1);
	if (cpid1 == 0) //child 1
	{
		cout << "This is child 1" << endl; 
		close(pipefd[READ]);
		stdfd_out = dup(1);
		cout << "stdfdout is " << stdfd_out << endl;

		check = dup2(pipefd[WRITE], WRITE);
		dup2check(check);

		pipeExe(left); 
		check = dup2(stdfd_out, WRITE);
		dup2check(check);

		cout << "This is end of child 1" << endl;

	}
	else
	{
		cpid2 = fork();
		forkcheck(cpid2);
		if (cpid2 == 0)			//child 2
		{
			cout << "This is child 2" << endl;
			close(pipefd[WRITE]);
			stdfd_in = dup(0);
			cout << "stdfdin is " << stdfd_in << endl; 
			check = dup2(pipefd[READ], READ);
			dup2check(check);

			pipeExe(right);
			check = dup2(stdfd_in, READ);
			cout << "Check is " << check << endl; 
			dup2check(check);
			cout << "This is end of child 2" << endl; 
		}
	}

	waitpid(cpid1, nullptr, 0);
	close(pipefd[1]);

	waitpid(cpid2, nullptr, 0);
	close(pipefd[0]);
	close(stdfd_in);
	close(stdfd_out);
	return true;
}
#endif
