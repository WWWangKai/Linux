#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int ring[64];  //环形队列
sem_t blank;  //空格  表示空格的信号量
sem_t datas;  //数据   表示数据的信号量

void* Producer(void* arg)
{
	int i = 0;
	while(1)
	{
		sleep(1);
		sem_wait(&blank);
		int data = rand()%10000;
		ring[i] = data;
		i++;
		i %= 64;
		printf("produce: %d\n",data);
		sem_post(&datas);
	}
}

void* Consumer(void* arg)
{
	int i = 0;
	while(1)
	{
		sleep(1);
		sem_wait(&datas);
		int data = ring[i];
		i++;
		i %= 64;
		printf("consumer: %d\n",data);
		sem_post(&blank);
	}
}


int main()
{
	sem_init(&blank,0,64);
	sem_init(&datas,0,0);
	pthread_t producer;
	pthread_t consumer;
	pthread_create(&producer,NULL,Producer,NULL);
	pthread_create(&consumer,NULL,Consumer,NULL);
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);

	sem_destroy(&blank);
	sem_destroy(&datas);
	return 0;
}






