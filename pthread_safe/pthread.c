#include<stdio.h>
#include<pthread.h>

int count = 0;

void* fun(void* arg)
{
	int i = 0;
	while(i < 5000)
	{
		i++;
		int tmp = count;
		printf("count : %d\n",count);
		count = tmp+1;
	}
}

int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,fun,NULL);
	pthread_create(&tid2,NULL,fun,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("count is :%d\n",count);
	return 0;
}
