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

bool Pipes::execute() {
	const int READ = 0, WRITE = 1; 
	int pipefd[2], stdfd_in, stdfd_out, check; 
	pid_t cpid1, cpid2; 
	pipe(pipefd); 

	cpid1 = fork(); 
	if (cpid1 < 0)
	{
		perror("Fork failed in pipes");
		exit(1); 
		return false; 
	}
	if (cpid1 == 0) //child 1
	{
		close(pipefd[READ]);
		stdfd_out = dup(1);
		check = dup2(pipefd[WRITE], WRITE);
		if (check < 0)
		{
			perror("dup2 failed");
			exit(1); 
			return false; 
		}
		left->execute(); 
		check = dup2(stdfd_out, 1);
	}
	else if(cpid2 == 0)			//child 2
	{
		close(pipefd[WRITE]); 
		stdfd_in = dup(0); 
		check = dup2(pipefd[READ], READ);
		if (check < 0)
		{
			perror("dup2 failed");
			exit(1);
			return false;
		}
		right->execute(); 
		check = dup2(stdfd_in, 1);
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
