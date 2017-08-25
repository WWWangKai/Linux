#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<arpa/inet.h>


int startup(const char* ip,int port)
{

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);//把点分十进制转为4字节

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock,10) < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}


static void usage(const char* proc)
{
	printf("[local_ip] [local_port]%s\n",proc);
}

int main(int argc,const char* argv)
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));
	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
		if(new_sock < 0)
		{
			perror("accept");
			continue;//监听失败的话 会继续监听 成功的话把new_sock交给下一步
		}
	
	printf("get a new client\n");

	while(1)//服务器端是先read 后write
	{
		char buf[1024];
		ssize_t s = read(new_sock,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			printf("client echo#: ",buf);
			write(new_sock,buf,strlen(buf));
		}
		else if(s == 0)
		{
			printf("client close !\n");
			break;
		}
		else
		{
			perror("read");
			break;
		}
	}
	}
	return ;
}






