#include"thread_pool.h"
#include<time.h>

static void* thread_routine(void* arg)
{
	struct timespec abstime;
	int timeout;
	printf("thread %d is start\n",(int)pthread_self());
	threadpool_t *pool=(threadpool_t *)arg;
	while(1)
	{
		timeout=0;
		condition_lock(&pool->status);
		pool->empty++;
		while(pool->first == NULL && !pool->quit)
		{
			printf("thread %d is wait\n",(int)pthread_self());
			clock_gettime(CLOCK_REALTIME,&abstime);
			abstime.tv_sec += 2;
			int status;
			status = condition_timewait(&pool->status,&abstime);
			if(status == ETIMEDOUT)
			{
				printf("thread %d wait time out\n",(int)pthread_self());
				timeout=1;
				break;
			}
		}
		pool->empty--;
		if(pool->first != NULL)
		{
			task_t *task = pool->first;
			pool->first = task->next;
			condition_unlock(&pool->status);
			task->run(task->arg);
			free(task);
			condition_lock(&pool->status);
		}
		if(pool->quit && pool->first == NULL)
		{
			pool->count--;
			if(pool->count == 0)
			{
				condition_signal(&pool->status);
			}
			condition_unlock(&pool->status);
			break;
		}
		if(timeout == 1)
		{
			pool->count--;
			condition_unlock(&pool->status);
			break;
		}

		condition_unlock(&pool->status);
	}

	printf("thread %d is exiting \n",(int)pthread_self());
	return NULL;
}

void threadpool_init(threadpool_t* pool,int threads)
{
	condition_init(&pool->status);
	pool->first = NULL;
	pool->last = NULL;
	pool->count = 0;
	pool->empty = 0;
	pool->maxthread = threads;
	pool->quit = 0;
}

void threadpool_add(threadpool_t* pool,void *(*run)(void* arg),void* arg)//将一个任务添加到线程池
{
	task_t* new_task =(task_t*)malloc(sizeof(task_t))	;
	new_task->run = run;
	new_task->arg = arg;
	new_task->next = NULL;

	condition_lock(&pool->status);//对线程池进行加锁
	if(pool->first == NULL)
	{
		pool->first = new_task;
	}
	else
	{
		pool->last->next = new_task;
	}
	pool->last = new_task;

	if(pool->empty > 0)//有空闲线程  那么就唤醒空闲的线程
	{
		condition_signal(&pool->status);
	}
	else if(pool->count < pool->maxthread)//
	{
		pthread_t tid;
		pthread_create(&tid,NULL,thread_routine,pool);
		pool->count++;
	}
	condition_unlock(&pool->status);
}

void threadpool_destroy(threadpool_t* pool)
{
	if(pool->quit)
	{
		return;
	}
	condition_lock(&pool->status);
	pool->quit = 1;
	if(pool->count > 0)
	{
		if(pool->empty > 0)
		{
			condition_broadcast(&pool->status);
		}
		while(pool->count)
		{
			condition_wait(&pool->status);
		}
	}
	condition_unlock(&pool->status);
	condition_destroy(&pool->status);
}


void* mytask(void * arg)
{
	printf("thread %d is working on task %d\n",\
	(int)pthread_self(),*((int*)arg));
	sleep(1);
	free(arg);
	return NULL;
}

int main()
{
	threadpool_t pool;
	threadpool_init(&pool,3);
	printf("Debug 1\n");
	int i;
	for(i=0;i<10;i++)
	{
		int *arg=malloc(sizeof(int));
		*arg=1;
		threadpool_add(&pool,mytask,arg);
	}
	printf("Debug 2\n");
	threadpool_destroy(&pool);
	return 0;
}




