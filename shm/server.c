#include"comm.h"

int main()
{
	int shmid = creatShm(4096);
	sleep(3);
	char* addr=shmat(shmid,NULL,0);
	int i = 0;
	while(i < 26)
	{
		printf("%s\n",addr);
		sleep(1);
		++i;
	}
	shmdt(addr);
	int ret = destroyShm(shmid);
	return 0;
}
