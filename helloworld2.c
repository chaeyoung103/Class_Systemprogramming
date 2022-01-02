#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>

int main(int argc,char* argv[])
{
    pid_t childpid=0;
    int i,n,status;
    if(argc<2){
        fprintf(stderr, "usage %s processes\n",argv[0]);
        return -1;
    }
    n=atoi(argv[2]);
    for(i=1;i<=n;i++)
        if((childpid=fork())<=0)
            break;
    int num = atoi(argv[1]);
    int s= num/n*(i-1)+1;
    int e= num/n*i;

    char ss[9];
    char ee[9];
    snprintf(ss,9,"%d",s);
    snprintf(ee,9,"%d",e);
    if(childpid==0){
        execl("helloworld2","helloworld2",ss,ee,NULL);
        return 1;
    }
    else 
    {
        sleep(1);
        wait(&status);
        fprintf(stderr,"[%ld] completed all tasts.\n",(long)getpid());
    }
    return 0;
}

