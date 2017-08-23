#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>

void handler(int sig)
{
	pid_t cid;
	while((cid = waitpid(-1,NULL,0) > 0))
	{
		printf("wait child success: %d\n",cid);
	}
	printf("child is quit :%d\n",getpid());
}

int main()
{
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD,&act,NULL);

	signal(SIGCHLD,handler);
	int id = fork();
	if(id == 0)
	{
		printf("child : %d\n",getpid());
		sleep(3);
		exit(1);
	}
	return 0;
}

