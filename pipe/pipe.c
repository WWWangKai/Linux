#include<stdio.h>
#include<unistd.h>

void capacitypipe()
{
	int fd[2];
	pipe(fd);
	char buf[4096];
	int i = 0;
	for(;i<sizeof(buf);i++)
	{
		buf[i] = '1';
	}
	i = 0;
	for(;i<100;i++)
	{
		ssize_t s = write(fd[1],buf,sizeof(buf));
		if(s<0)
		{
			perror("write");
		}
		else
		{
			printf("%d",s);
			printf("capacity## %d*4k=%dk\n",i,i*4);
		}
	}
	close(fd[0]);
	close(fd[1]);
}

int main()
{
	capacitypipe();
	return 0;
}
