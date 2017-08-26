#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>

int fds[sizeof(fd_set)*8];

static usage(const char* proc)
{
	printf("usage :%s [local_ip] [local_port]\n",proc);
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
	local.sin_addr.s_addr = inet_addr(ip);//点分十进制化为四字节
    
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
	printf("fd_set: %d\n",sizeof(fd_set)*8);
	int fds[sizeof(fd_set)];
	int nums = sizeof(fds)/sizeof(fds[0]);
	int i = 0;
	for(; i < nums; i++)
	{
		fds[i] = -1;
	}
	fds[0] = listen_sock;
	int maxfd = -1;
	fd_set rfds;//读事件
	fd_set wfds;//写事件
	while(1)
	{
		int maxfd = -1;
		struct timeval timeout = {2,0};
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		i = 0;
		for(; i < nums;i++)
		{
			if(fds[i] == -1)
			{
				continue;
			}
			FD_SET(fds[i],&rfds);
			if(maxfd < fds[i])
			{
				maxfd = fds[i];
			}
		}
		switch(select(maxfd+1,&rfds,&wfds,NULL,&timeout))
		{                      
			case -1:   //select失败
				perror("select");
				break;
			case 0:    //超过时间没有任何描述符就绪
				printf("time out!\n");
				break;
			default:   //成功
				{
				//at least one fd ready!
				i = 0;
				for(; i < nums;i++)
				{
					if(i == 0 && FD_ISSET(fds[i],&rfds))//listen_sock is ready, get connect
					{
						struct sockaddr_in client;
						socklen_t len = sizeof(client);
						int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
						if(new_sock < 0)
						{
							perror("accept");
							continue;
						}
						//accept只是获得了一个新的连接  但是不能保证读和写正常
						//如果对面一直不发数据  那么就会一直处于read里的等待情况  就会导致服务器的不能正常运行
						
						printf("get a new client: [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));


						int j = 1;
						for(; j < nums ; j++)
						{
							if(fds[j] == -1)
							{
								break;
							}
						}
						if(j == nums)//已经达到所能监听的文件描述符的最大值 只能关闭
						{
							close(new_sock);
						}
						else
						{
							fds[j] = new_sock;
						}
					}
					else if(i != 0 && FD_ISSET(fds[i],&rfds))//normal fd is ready
					{
						char buf[1024];
						ssize_t s = read(fds[i],buf,sizeof(buf)-1);
						if( s > 0)
						{
							buf[s] = 0;
							printf("client# %s\n",buf);
						    FD_SET(fds[i],&wfds);

						}
						else if(s == 0)
						{
							printf("client is quit！\n");
							close(fds[i]);
							fds[i] = -1;
						}
						else
						{
							perror("read");
							close(fds[i]);
							fds[i] = -1;
						}
					}
					 if(i !=0 && FD_ISSET(fds[i],&wfds))//普通的写操作
					{
						const char* msg = "hello client!\n";
						ssize_t s = write(fds[i],msg,strlen(msg));
						if(s < 0)
						{
							perror("write");
						}
						else
						{
							FD_CLR(fds[i],&wfds);
						}
					}
				}
				break;
			}
		}

	}
	close(listen_sock);
	return 0;
}








