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
	printf("Usage: %s[client_ip] [local_port]\n",proc);
}


int main(int argc,char* argv[])
{	
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	//udp的服务器的读和写是 recvfrom 和 sendto
	//UDP的服务器是只需要bind 不需要监听和连接   
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}
	
	 printf("sock %d\n",sock);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port =htons(atoi(argv[2]));
	server.sin_addr.s_addr =inet_addr(argv[1]);

	if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
	{
		perror("bind");
    	return 1;
	}

	char buf[1024];
	//struct sockaddr_in client;

	printf("get a new client!\n");
	while(1)
	{
		printf("[%s:%d]\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));
    	struct sockaddr_in client;
		socklen_t len = sizeof(client);
		ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
		if(s > 0)
		{
			buf[s] = 0;
			printf("[%s:%d]# %s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&client,sizeof(client));
		}
		else if(s == 0)
		{
			printf("client close!\n");
			continue;
		}
		else
		{
			perror("recvfrom");
			continue;
		}
	}
}








