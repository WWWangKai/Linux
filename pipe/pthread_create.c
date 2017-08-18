#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread_run(void* arg)
{
	int count = 0;
	//pthread_t mid = *(pthread_t*)arg;
	while(count++<5)
	{
		sleep(1);
		printf("thread pid:%d,ppid:%d,tid:%lu\n",getpid(),getppid(),pthread_self());
	}
	printf("thread is over\n");
	//pthread_exit((void*)10);
	return NULL;
}

int main()
{
	printf("pthread\n");
	pthread_t tid;
	int ret = pthread_create(&tid,NULL,thread_run,pthread_self());
	if(ret != 0)
	{
		printf("pthread_create error\n");
		return -1;
	}
	else
	{
		sleep(1);
		printf("main pid:%d,ppid:%d,tid:%lu\n",getpid(),getppid(),pthread_self());
	}
	pthread_cancel(tid);
	int exitcode;
	pthread_join(tid,(void**)&exitcode);

	printf("main is over  %d\n",exitcode);
	return 0;
}

