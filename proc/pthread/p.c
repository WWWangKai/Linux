#include<stdio.h>
#include<pthread.h>

void* thread_run1()
{
	printf("i am thread_run1\n");
	printf("thread_run1 : %u\n",pthread_self());
	return NULL;
}

void* thread_run2()
{
	printf("i am thread_run2\n");
	printf("thread_run2 : %u\n",pthread_self());
	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,thread_run1,NULL);
	pthread_create(&tid2,NULL,thread_run2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
