#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>


static usage(const char* proc)
{
	printf("Usage: %s[local_ip] [local_port]\n",proc);
}

int startup(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);  //创建socket
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}
	printf("sock：%d\n",sock);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)  //进行绑定
	{
		perror("bind");
		exit(3);
	}
	
	if(listen(sock,10) < 0)  //将资源设置为监听状态
	{
		perror("listen");
		exit(4);
	}


	return sock;
}



int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	int listen_sock = startup(argv[1],atoi(argv[2]));//上面返回的是listen的sockt

	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);//监听套接字

		if(new_sock < 0)
		{
			perror("accept");
			continue;
		}

	//printf("get a new client [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	printf("get a new client\n");
	//客户端和服务器未能建立连接   继续监听

	//先read后write
	while(1)
	{
		char buf[1024];
		ssize_t s = read(new_sock,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			printf("client# %s\n",buf);
			write(new_sock,buf,strlen(buf));
		}
		else if(s == 0 )
		{
			printf("client close!!!\n");
			break;
		}
		else
		{
			perror("read");
			break;
		}
	}
	}
	return 0;
	
}









