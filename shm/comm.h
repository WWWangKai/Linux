#ifndef _COMM_H__
#define _COMM_H__

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define PATH "."
#define PROJ_ID 0x6666

int creatShm(int size);    //创建 
int getShm(int size);     //获取 
int destroyShm(int shmid);  //删除 

#endif   //_COMM_H__
