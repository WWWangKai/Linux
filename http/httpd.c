#include"httpd.h"



int startup(char* ip,int port)
{
	//创建套接字
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		print_log("socket failed!\n",FATAL);
		perror("socket");
		exit(2);
	}

	//端口号进行复用
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));


	//绑定套接字
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		print_log("bind is failed!\n",FATAL);
		perror("bind");
		exit(3);
	}


	//处于监听状态
	if(listen(sock,10) < 0)
	{
		print_log("listen is failed!\n",FATAL);
		perror("listen");
		exit(4);
	}
	print_log("create listenfd success",NORMAL);
	return sock;
}



void clear_header(int sock)
{
	int ret = 0;
	char buf[SIZE];
	do{
		ret = get_line(sock,buf,sizeof(buf));
		printf("%s",buf);
	}while(ret > 0 && strcmp(buf,"\n") != 0);
}


void print_log(char *log_msg,int level)  //打印日志
{
	char *arr[10]=
	{
		"NORMAL",
		"WARNING",
		"FATAL",
	};

	printf("%s %s\n",log_msg,arr[level]);
	char *path="log/wwwlog";
	int fd=open(path,O_WRONLY|O_APPEND|O_CREAT,0644);

	char buf[SIZE];
	memset(buf,0,SIZE);

	strncpy(buf,log_msg,strlen(log_msg));

	strncat(buf,arr[level],strlen(arr[level]));

	time_t tm;
	char str[30];
	str[0] = ' ';
	time(&tm);
	strcpy(str+1,ctime(&tm));
	strcat(buf,str);
	write(fd,buf,strlen(buf));

	close(fd);
}

void request_404(int sock)
{
	printf("enter request_404...\n");
	char *path="wwwroot/404.html";

	struct stat st;
	if(stat(path,&st) < 0){
		return;
	}
	int fd=open(path,O_RDONLY);
	if(fd < 0)
	{
		print_log("open failed",FATAL);
		return;
	}
	char buf[SIZE];
	memset(buf,0,SIZE);

	sprintf(buf,"HTTP/1.0 404 NotFound\r\n\r\n");

	if(send(sock,buf,strlen(buf),0) < 0){
		print_log("send failed!",FATAL);
		return;
	}

	if(sendfile(sock,fd,NULL,sizeof(buf)) < 0){
		print_log("sendfile failed!",FATAL);
		return;
	}

	const char *content_type="Content-Type:text/html;charset=UTF-8\r\n";
	send(sock,content_type,strlen(content_type),0);
	send(sock,"\r\n",strlen("\r\n"),0);

	close(fd);
}


void echo_error(int sock,int err_code)  //错误处理
{
	printf("enter echo_error...\n");
	switch(err_code)
	{
		case 401:
			break;
		case 404:
			request_404(sock);
			break;
		case 500:
			break;
		case 503:
			break;
		default:
			break;
	}
}


void echo_client(int nums)
{
}

void echo_www(int sock,char *path,int size)
{
	printf("path%s\n ",path);
	int new_fd = open(path,O_RDONLY);
	if(new_fd < 0)
	{
		print_log("open failed",FATAL);
		//echo_error(sock,404);
		return;
	}
	const char *status_line = "HTTP/1.0 200 OK\r\n";
	const char *blank_line = "\r\n";

	send(sock,status_line,strlen(status_line),0);
	send(sock,blank_line,strlen(blank_line),0);

	if(sendfile(sock,new_fd,NULL,size) < 0)
	{
		print_log("sendfile failed",FATAL);
		//echo_error(sock,404);
	}

	close(new_fd);
}

void urldecode(char *p)  
{  
	register i=0;  
	while(*(p+i))  
	{  
		if ((*p=*(p+i)) == '%')  
		{  
			*p=*(p+i+1) >= 'A' ? ((*(p+i+1) & 0XDF) - 'A') + 10 : (*(p+i+1) - '0');  
			*p=(*p) * 16;  
			*p+=*(p+i+2) >= 'A' ? ((*(p+i+2) & 0XDF) - 'A') + 10 : (*(p+i+2) - '0');  
			i+=2;  
		}  
		else if (*(p+i)=='+')  
		{  
			*p=' ';  
		}  
		p++;  
	}  
	*p='\0';  
}  

void exe_cgi(int sock,const char* path,const char* method,const char* query_string)
{
	int content_length = -1;
	if(strcasecmp(method,"get") == 0)
	{
		clear_header(sock);
	}
	else
	{
		char buf[SIZE];
		int ret = 0;
		do{
			ret = get_line(sock,buf,sizeof(buf));
			if(strncasecmp(buf,"Content-Length: ",16) == 0)
			{
				content_length = atoi(buf+16);
			}
		}while(ret >0 && strcmp(buf,"\n") != 0);

		if(content_length == -1)
		{
			//echo_error(sock,404);
			return;
		}
	}

	const char* status_line="http/1.0 200 OK\r\n";
	const char* type_line="Content-Type:text/html;charset=UTF-8\r\n";
	const char* line="Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
	//const char* type_line="Content-Type:text/html;charset=gb2312\r\n";
	const char* blank_line="\r\n";

	send(sock,status_line,strlen(status_line),0);
	send(sock,type_line,strlen(type_line),0);
	send(sock,line,strlen(line),0);
	send(sock,blank_line,strlen(blank_line),0);

	int input[2];
	int output[2];
	if(pipe(input) < 0)
		return;
	if(pipe(output) < 0)
		return;
	char method_env[SIZE];
	char query_string_env[SIZE];
	char content_length_env[SIZE];

	pid_t id = fork();

	if(id < 0)
	{
		perror("fork");
		echo_error(sock,404);
		return;
	}
	else if(id == 0)
	{
		close(input[1]);
		close(output[0]);

		dup2(input[0],0);
		dup2(output[1],1);

		sprintf(method_env,"METHOD=%s",method);
		putenv(method_env);
		if(strcasecmp(method,"GET") == 0)
		{
			sprintf(query_string_env,"QUERY_STRING=%s",query_string);
			putenv(query_string_env);
		}
		if(strcasecmp(method,"POST") == 0)
		{
			sprintf(content_length_env,"CONTENT_LENGTH=%d",content_length);
			putenv(content_length_env);
		}
		execl(path,path,NULL);
		exit(1);
	}
	else
	{
		close(input[0]);
		close(output[1]);
		int i=0;
		char c='\0';
		if(strcasecmp(method,"POST") == 0)  
		{
			for(i=0; i<content_length; ++i)
			{

				recv(sock,&c,1,0);    
				write(input[1],&c,1);   
			}
		}

		while(read(output[0],&c,1) > 0)   
		{
			send(sock,&c,1,0);    
		}
		waitpid(id,NULL,0);
		close(input[1]);
		close(output[0]);
	}
}



int handle_request(int sock)
{
	char buf[SIZE];
	char method[SIZE/10];
	char url[SIZE];
	char path[SIZE];
	int ret = 0;
	int nums = 0;
	int cgi = 0;
	char* query_string = NULL;
	//int fd = (int)arg;
#ifdef _DEBUG_
#endif
	if(get_line(sock,buf,sizeof(buf)) < 0)
	{
		//print_log("get_line",WARNING);
		ret = -1;
		nums = 404;
		goto end;
	}
	//GET /a/b/index.html http/1.0
	//先获取method   后获取url  再对method方法进行判断是否是get或者post方法  还有cgi方法   最后还要将参数进行分离
	//还要判断路径是否存在  不存在就404报错   路径存在还要看要获取的资源的method和size  
	//如果资源的路径是一个文件夹  那么就要在后面给上添加主页信息   资源是一个二进制文件就执行cgi
	//clear_header   echo_client   echo_www
	int i = 0;
	int j = 0;
	while(i < sizeof(method) - 1 && j < sizeof(buf) && !isspace(buf[j]))//获取method
	{
		method[i] = buf[j];
		i++,j++;

	}
	method[i] = 0;
	//获取url
	while(j < sizeof(buf) && isspace(buf[j]))
	{
		j++;
	}
	i = 0;
	while(i < sizeof(url) && j < sizeof(buf) && !isspace(buf[j]))
	{
		url[i] = buf[j];
		i++,j++;
	}
	url[i] = 0;
	printf("method %s\n",method);
	//由于get和post有大小写之分  过滤非get和post的方法
	if(strcasecmp(method,"get") && strcasecmp(method,"post"))
	{
		print_log("not GET or POST",WARNING);
		//echo_error(sock,404);
		ret = -2;
		nums = 404;
		goto end;
	}

	//get方法会将参数放在后面   要将参数进行分离
	if(strcasecmp(method,"post") == 0)
	{
		cgi = 1;
	}
	else
	{
		query_string = url;
		while(*query_string != '\0')
		{
			if(*query_string == '?')
			{
				*query_string = '\0';
				query_string++;
				cgi = 1;
				break;
			}
			query_string++;
		}
	}


	//把wwwroot追加在path的前面

	sprintf(path,"wwwroot%s",url);
	if(path[strlen(path)-1] == '/')
	{
		strcat(path,"index.html");
	}


	printf("path  %s\n",path);
	//然后再判断是否是一个文件夹   是否是二进制文件 
	struct stat st;
	if(stat(path,&st) < 0)
	{
		print_log("stat failed",WARNING);
		//echo_error(sock,404);
		ret = -3;
		nums = 404;
		goto end;
	}
	else
	{
		if(S_ISDIR(st.st_mode))
		{
			strcat(path,"index.html");
		}
		else if((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		{
			cgi = 1;
		}
		else
		{}
	}
	if(cgi == 1)
	{
		exe_cgi(sock,path,method,query_string);
	}
	else
	{
		clear_header(sock);
		echo_www(sock,path,st.st_size);
	}
	//最后再看是否是cgi处理还是普通的 
end:
	echo_client(nums);
	close(sock);
	return ret;
}

int get_line(int sock,char buf[],int len)
{
	char c = '\0';
	int i = 0;
	while(c != '\n' && i < len-1)
	{
		ssize_t s = recv(sock,&c,1,0);
		if(s > 0)
		{
			if(c == '\r')
			{
				ssize_t m = recv(sock,&c,1,MSG_PEEK);
				if((m > 0) && (c == '\n'))
				{
					recv(sock,&c,1,0);
				}
				else
					c = '\n';
			}
			buf[i++] = c;

		}
		else
		{
			print_log("get_line",FATAL);
			//echo_error(sock,404);
			printf("get_line is faild\n");
			c = '\n';
			continue;
		}

	}
	buf[i] = 0;
	return i;
	print_log("get_line is success!",NORMAL);
	printf("get_line is succed\n");
}












