#include "comm.h"

int main()
{
	int shmid=getShm(4096);
	printf("getShm success!!  shmid:%d\n",shmid);

	char* addr=shmat(shmid,NULL,0);
	int i=0;
	while(i<26)
	{
		addr[i]='A'+i;
		sleep(1);
		++i;
		addr[i]=0;
	}

	shmdt(addr); 
	return 0;
}
