#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<netinet/in.h>

static usage(const char* proc)
{
	printf("usage: [client_ip] [client_port]%s\n",proc);
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port =htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	

	if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
	{
		perror("connect");
		exit(3);
	}
	
	char  buf[1024];
	int fd;
	while(1)
	{
		printf("please Enter#: ");
		fflush(stdout);
		fd = dup(1);

		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s-1] = 0;

			close(1);
			dup2(sock,1);
			printf("%s",buf);
			fflush(stdout);
		}
		else
		{
			perror("read");
			exit(4);
		}
		dup2(fd,1);
		ssize_t _s = read(sock,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s] = 0;
			printf("server echo#: %s\n",buf);
		}
	}
	close(fd);
	close(sock);
	return 0;
}






