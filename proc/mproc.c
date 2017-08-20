#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main()
{
	printf("This is one\n");
	pid_t id = fork();
	printf("This is two\n");
	if(id==0)
	{
		printf("This is child\n:%d ppid:%d\n",getpid(),getppid());
		exit(1);
	}
	else
	{
		sleep(1);
		printf("This is father:%d\n",getpid());
		waitpid(-1,NULL,0);
	}
	return 0;
}

