#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void hander(int sig)
{
}

int mysleep(int time)
{
	struct sigaction act,oact;
	act.sa_handler = hander;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM,&act,&oact);

	sigset_t newset,oldset,sigmask;
	sigemptyset(&newset);
	sigemptyset(&oldset);
	sigaddset(&newset,SIGALRM);
	sigprocmask(SIG_BLOCK,&newset,&oldset);

	alarm(time);
	sigmask = oldset;
	sigdelset(&sigmask,SIGALRM);
	sigsuspend(&sigmask);

	sigaction(SIGALRM,&oact,&act);
	sigprocmask(SIG_SETMASK,&oldset,&newset);
	int ret = alarm(0);
	return ret;
}

int main()
{
	while(1)
	{
		int ret = mysleep(3);
		printf("mysleep is over ...%d\n",ret);
	}
	return 0;
}
