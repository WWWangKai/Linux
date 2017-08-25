#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>


int main()
{
	int sv[2];
	int ret = socketpair(PF_LOCAL,SOCK_STREAM,0,sv);
	if(ret < 0)
	{
		perror("socketpair");
		return 1;
	}

	pid_t id = fork();
	if(id < 0)
	{	
		perror("fork");
		exit(2);
	}
	else if(id == 0) //child
	{
		close(sv[0]);
		char buf[1024];
		char *msg = "i am a child...";
		while(1)
		{
			ssize_t s = write(sv[1],msg,strlen(msg));
			if(s > 0)
			{
				read(sv[1],buf,sizeof(buf)-1);
				printf("f->c: %s\n",buf);
			}
			sleep(1);
			close(sv[1]);
		}
	}
	else//father
	{
		close(sv[1]);
		char buf[1024];
		char *msg = "i am a father...";
		while(1)
		{
			ssize_t s = read(sv[0],buf,sizeof(buf)-1);
			if(s > 0)
			{
				printf("c->: %s\n",buf);
				write(sv[0],msg,strlen(msg));
			}
			close(sv[0]);
		}
	}
	return 0;
}




