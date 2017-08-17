#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/poll.h>
#include<sys/types.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define BUF_SIZE 1024

static usage(const char* proc)
{
	printf("Usage: [local_ip],[local_port]%s\n",proc);
}



int startup(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);


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

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));
	struct pollfd evs[BUF_SIZE];
	int timeout = 5000;
	int i = 0;
	for(;i < BUF_SIZE;i++)
	{
		evs[i].fd = -1;
		evs[i].events = 0;
	}
	evs[0].fd = listen_sock;
	evs[0].events = POLLIN;
	evs[0].revents = 0;

	int count = 0;

	while(1)
	{
		switch(poll(evs,count+1,timeout))
		{
			case -1:
				{
					perror("poll");
					break;
				}
			case 0:
				{
					printf("time out...\n");
					break;
				}
			default:
				{
					for(i = 0;i < BUF_SIZE;i++)
					{
						if(evs[i].fd == -1)
						{
							continue;
						}
						//listen_sock的读事件就绪
						else if(evs[i].fd == listen_sock && evs[i].revents & POLLIN)
						{
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
							if(new_sock < 0)
							{
								perror("accept");
								continue;
							}
							printf("get a new client! ip:%s port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
							int j = 1;
							for(; j < BUF_SIZE;j++)
							{
								if(evs[j].fd == -1)
								{

								    evs[j].fd = new_sock;
								    evs[j].events = POLLIN;
									break;
								}
							}
							if(j > count)
							{
								count = j;
							}
							if(j == BUF_SIZE)
							{
								close(new_sock);
							}
						}
						//普通事件的读事件就绪
						else if(evs[i].revents & POLLIN)
						{
							char buf[1024];
							ssize_t s = read(evs[i].fd,buf,sizeof(buf)-1);
							if(s > 0)
							{
								buf[s] = 0;

								printf("client echo#: %s\n",buf);
								write(evs[i].fd,buf,strlen(buf));
								evs[i].revents = 0;
							}
							else if(s == 0)
							{
								printf("client is cose!!!\n");
								close(evs[i].fd);
								evs[i].fd = -1;
							}
							else
							{
								perror("read");
								close(evs[i].fd);
								evs[i].fd = -1;
							}
						}
					}
					break;
				}
		}
	}
	return 0;
}





