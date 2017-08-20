#include <stdio.h>  
#include <signal.h>  
#include <unistd.h>  
#include <sys/types.h>  
   
void myhander(int sig)  
{  
	    printf("pid## %d receiving sig## %d\n",getpid(),sig);  
}     
void PrintPending(sigset_t set)  
{  
	    int i=1;  
		    for(;i<32;++i)  
				    {  
						        if(sigismember(&set,i))  
									        {  
												            printf("1 ");  
															        }  
								        else  
											        {  
														            printf("0 ");  
																	        }  
										    }  
			    printf("\n");  
}  
int main()  
{   
	    sigset_t s;  
		    sigemptyset(&s);   
			    sigaddset(&s,2);  
				  
				    sigset_t oldset;   
					    sigprocmask(SIG_SETMASK,&s,&oldset);
						      
						    signal(2,myhander);
							    int count=0;  
								    while(1)  
										    {  
												        sigset_t s1;  
														        sigprocmask(0,NULL,&s1);  
																        printf("block list:");  
																		        PrintPending(s1);  
																				          
																				        sigset_t p;  
																						        sigpending(&p);
																								        printf("pend  list:");  
																										        PrintPending(p);
																												  
																												        if(count==10)  
																															        {  
																																		            sigprocmask(SIG_SETMASK,&oldset,&s);   
																																					        }  
																														        sleep(1);  
																																  
																																        ++count;  
																																		    }  
									    return 0;  
}  
