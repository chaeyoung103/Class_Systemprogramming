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
        fprintf(stderr, "error\n");
        return -1;
    }
    n=argc-1;
    for(i=1;i<=n;i++)
        if((childpid=fork())<=0)
            break;
    
    int s=1;
    int e= atoi(argv[i]);

    char ss[9];
    char ee[sizeof(argv[i])];
    sprintf(ss,"%d",s);
    sprintf(ee,"%d",e);
    if(childpid==0){
        execl("sum_202012667","sum_202012667",ss,ee,NULL);
        return 1;
    }
    else 
    {
        sleep(1);
        wait(&status);
        fprintf(stderr,"main pid: [%ld] all children done.\n",(long)getpid());
    }
    return 0;
}