#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include"condition.h"
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct task
{
	void *(*run)(void* args);
	void *arg;
	struct task *next;
}task_t;

typedef struct threadpool
{
	condition_t status;
	task_t *first;
	task_t *last;
	int count;
	int maxthread;//最大的线程的数量
	int quit;  //是否退出
	int empty; //用于描述空闲线程的数量
}threadpool_t;

void threadpool_init(threadpool_t* pool,int threads);
void threadpool_add(threadpool_t* pool,void *(*run)(void* arg),void* arg);
void threadpool_destroy(threadpool_t* pool);

#endif


