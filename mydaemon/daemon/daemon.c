#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>

void my_daemon()
{
	umask(0);
	if(fork() > 0)
	{
		exit(1);
	}
	setsid();

	if(fork() > 0)
	{
		exit(1);
	}
	chdir("/");
	close(0);
	close(1);
	close(2);
	signal(SIGCHLD,SIG_IGN);
}

int main()
{
	my_daemon();
	while(1)
	{
	}
	return 0;
}
