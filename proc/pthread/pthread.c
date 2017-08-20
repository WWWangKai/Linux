#include<stdio.h>
#include<pthread.h>

void* thread1()
{
	printf("I am thread1\n");
	printf("thread1: %u\n",pthread_self());
	return NULL;
}

void* thread2()
{
	printf("I am thread2\n");
    printf("thread2: %u\n",pthread_self());
	return NULL;
}


int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
