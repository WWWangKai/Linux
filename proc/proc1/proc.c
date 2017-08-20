#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/type.h>
#include<sys/wait.h>
int main()
{
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork error!");
		return -1;
	}
	else if(id == 0)
	{
		printf("child is: %d,father is: %d\n",getpid(),getppid());
	}
	else
	{
		sleep(1);
		printf("father is :%d\n",getpid());
		wait(NULL);
	}
	return 0;
}
