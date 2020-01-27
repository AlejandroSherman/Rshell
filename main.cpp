#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int fork_function()
{
	int cpid = fork(); //fork, child id into cpid
	if(cpid < 0)
	{
		perror("fork() error");
		exit(-1);
	}

	if(cpid == 0) //CHILD
	{
		printf("This is child process!\n");
		printf("Child PID is %d.\n\n", getpid());
		const char *name = "./parsing";
		execvp(name,NULL);
}
	else //PARENT
	{
		printf("This is parent process!\n");
		printf("Parent PID is %d.\n\n", getppid());
		printf("Now I will wait\n\n");
		cpid = wait(NULL);	//wait for child to finish		
	}
}
int main()
{
	fork_function(); 
	return 0; 
}
