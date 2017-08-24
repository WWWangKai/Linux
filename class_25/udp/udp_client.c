#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>

static void usage(const char* proc)
{
	printf("%s [server_ip] [local_port]\n",proc);
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	//不需要绑定和监听
	//客户端需要先写后读
	char buf[1024];
	//struct sockaddr_in peer;
	while(1)
	{

    	struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		printf("please Enter#: ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s-1] = 0;
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));
			ssize_t _s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
			if(_s > 0)
			{
				buf[_s] = 0;
				printf("[%s:%d]: %s\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),buf);
			}
		}
	}
	close(sock);
	return 0;
}






