#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
#include<unistd.h>




typedef struct Node
{
	int data;
	struct Node* next;
}Node,*Node_p,**Node_pp;

Node_p CreatNode(int data)
{
	Node_p _n = (Node_p)malloc(sizeof(Node));
	if(_n == NULL)
	{
		return NULL;
	}
	_n->data = data;
	_n->next = NULL;
	return _n;
}

void Init(Node_pp list)
{
	*list = CreatNode(0);
}

void PushFront(Node_p list,int data)
{
	assert(list);
	Node_p _n = CreatNode(data);
	_n->next = list->next;
	list->next = _n;
	
}

void DelNode(Node_p node)
{
	assert(node);
	free(node);
	node = NULL;
}

int Isempty(Node_p list)
{
	assert(list);
	if(list->next != NULL)
	{
		return 0;
	}
	{
		return 1;
	}
}

void PopFront(Node_p list,int *data)
{
	assert(data);
	if(Isempty(list))
	{
		printf("The list is empty!\n");
		return;
	}
	Node_p _del = list->next;
	list->next = _del->next;
	*data = _del->data;
	DelNode(_del);
}

void Destory(Node_p list)
{
	int data = 0;
	assert(list);
	while(list->next)
	{
		PopFront(list,&data);
	}
	free(list);
	list = NULL;
	printf("list if destroy..\n");
}

void Print(Node_p list)
{
	assert(list);
	Node_p cur = list->next;
	while(cur)
	{
		printf("%d->",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;

void* Consumer(void *arg)
{
	Node_p head = (Node_p)arg;
	while(1)
	{
		int data = 0;
		pthread_mutex_lock(&mylock);
		if(Isempty(head))
		{
			pthread_cond_wait(&mycond,&mylock);
		}
		PopFront(head,&data);
		printf("consumer: %d\n",data);
		pthread_mutex_unlock(&mylock);
	}
	return NULL;
}

void* Producer(void *arg)
{
	Node_p head = (Node_p)arg;
	while(1)
	{
		usleep(123456);
		int data = rand()%1000;
		pthread_mutex_lock(&mylock);
		PushFront(head,data);
	    printf("Producer: %d\n",data);
		pthread_cond_signal(&mycond);
		pthread_mutex_unlock(&mylock);
	}
	return NULL;
}


int main()
{
	Node* head = NULL;
	Init(&head);
	pthread_t tid1,tid2;
	int ret1 = pthread_create(&tid1,NULL,Consumer,(void*)head);
	int ret2 = pthread_create(&tid2,NULL,Producer,(void*)head);
	printf("ret1:%d,ret2:%d\n",ret1,ret2);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mylock);
	pthread_cond_destroy(&mycond);
	return 0;
}









