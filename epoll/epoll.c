#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>

#define MAX_EVENTS 10
#define SIZE 64

typedef struct epbuff{
	int fd;
	char buf[2048];
	int index;
}epbuff_t,*epbuff_p,**epbuff_pp;

//此实现方式是LT模式
static epbuff_p alloc_buff(int fd) //此处开空间之后后面就要是ptr指向的一段空间
{
	epbuff_p ptr = (epbuff_p)malloc(sizeof(epbuff_t));
	if(NULL == ptr)
	{
		perror("malloc");
		exit(9);
	}
	ptr->fd = fd;
	return ptr;
}

static void dealloc(epbuff_p ptr)//既然要malloc就得去free
{
	if(NULL != ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

static usage(const char* proc)
{
	printf("Usage: [local_ip],[local_port]%s\n",proc);
}

int setnonblocking(int sock) //将文件描述符设置为非阻塞的
{
	int old_option = fcntl(sock,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(sock,F_SETFL,new_option);
	return old_option;
}

void addfd(int epollfd,int fd,int enable_et) // 将文件描述符上的fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	if(enable_et)
	{
		event.events |= EPOLLET;
	}
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
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

//实现的是ET版本的epoll服务器  要实现非阻塞版本
int myread(int sock,char* buf)
{
	int len = 0;
	int total = 0;
	while((len = read(sock,buf+total,1024) > 0) && (len = 1024 ))
	{
		total += len;
	}
	if(len > 0 && len< 1024)
	{
		total += len;
	}
	buf[total] = '\0';
	return total;
}



int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));

	int epfd = epoll_create(SIZE);//先创建一个红黑树和队列
	if(epfd < 0)
	{
		perror("epoll_create");
		exit(5);
	}
	
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = alloc_buff(listen_sock);
	
	setnonblocking(listen_sock);//由于是ET工作模式下  将listen_sock设置为非阻塞的状态

	if(epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev) < 0)//往事件表上注册fd事件（把listen_sock）加到红黑树上去
	{
		perror("epoll_ctl");
		exit(6);
	}
	 
    int timeout = 5000;
	int nums = -1;

	struct epoll_event revs[MAX_EVENTS];
	while(1)
	{
		nums = epoll_wait(epfd,revs,MAX_EVENTS,timeout);
		switch(nums)
		{
			case 0:
				printf("time out!!!...\n");
				break;
			case -1:
				perror("epoll_wait");
				break;
			default:
				{
					int i = 0;
					for(;i < nums ;i++)
					{
						int sock = ((epbuff_p)(revs[i].data.ptr))->fd;
						if(sock == listen_sock && revs[i].events == EPOLLIN)
						{
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
							if(new_sock < 0)
							{
								perror("myaccept");
								continue;
							}
							printf("get a new client! ip： %s port：%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
							ev.events = EPOLLIN | EPOLLOUT;
							setnonblocking(new_sock);
							ev.data.ptr = alloc_buff(new_sock);
							int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
							if(ret < 0)
							{
								perror("epoll_ctl");
								exit(7);
							}
						}
						else if(sock != listen_sock && (revs[i].events & EPOLLIN))
						{
							//char buf[1024];
							char* buf = ((epbuff_p)(revs[i].data.ptr))->buf;
							ssize_t s = myread(sock,buf);
							if( s > 0)
							{
								buf[s] = '\0';
								printf("client#：%s\n",buf);  //如果读成功之后就会直接关心其写操作
								ev.events=EPOLLOUT;
								epoll_ctl(epfd,EPOLL_CTL_MOD,sock,&ev);
							}
							else if(s == 0) // 直接关闭连接
							{
								printf("client is close!\n");
								dealloc(revs[i].data.ptr);
								epoll_ctl(epfd,EPOLL_CTL_DEL,sock,NULL);
								close(sock);
							}
							else
							{
								perror("read");
								dealloc(revs[i].data.ptr);
								int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,sock,NULL);
								if(ret < 0)
								{
									perror("epoll_ctl");
									exit(8);
								}
								close(sock);
							}
						}
						else if(sock != listen_sock && (revs[i].events &EPOLLOUT))
						{
							const char* msg = "HTTP/1.0 200 OK\r\n\r\n Hello epoll!  ";
							//const char* msg = "Hello epoll!\n";
							ssize_t s = write(sock,msg,strlen(msg));
							if(s < 0)
							{
								perror("write");
								exit(10);
							}
							dealloc(revs[i].data.ptr);
							epoll_ctl(epfd,EPOLL_CTL_DEL,sock,NULL);
							close(sock);
						}
					}
					break;
				}
		}
	}

	return 0;
}





