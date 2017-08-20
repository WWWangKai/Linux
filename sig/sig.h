#include<stdio.h>  
#include<unistd.h>  
#include<signal.h>  
  
void showpending(sigset_t *pending)  
{  
	    int i=0;  
		    for(i=1;i<=31;i++)  
				    {  
						        if(sigismember(pending,i))  
									            printf("1 ");  
								        else  
											            printf("0 ");  
										    }  
			    printf("\n");  
}  
  
void handler(int sign)  
{  
	    printf("pid is %d,sign is %d\n",getpid(),sign);  
		    return;  
}  
  
int main()  
{  
	    sigset_t sigset,osigset;  //定义信号集对象  
		    sigemptyset(&sigset);     //清空初始化  
			    sigemptyset(&osigset);      
				    sigaddset(&sigset,SIGINT);    //添加2号信号到已经存在的信号集中  
					    sigprocmask(SIG_SETMASK,&sigset,&osigset); //读取或更改信号的信号屏蔽字  
						  
						    signal(2,handler);  //对2号信号进行自定义的信号处理操作  
							  
							    int count=0;  
								    sigset_t pending;  
									    while(1)  
											    {  
													        sigpending(&pending);  //获取未决信号  
															        showpending(&pending); //打印pending表  
																	        sleep(1);  
																			        if(count++ > 3)  
																						        {  
																									            sigprocmask(SIG_SETMASK,&osigset,&sigset);  //count秒之后清空pending表  
																												            count=0;  
																															        }  
																					    }  
										    return 0;  
}  
