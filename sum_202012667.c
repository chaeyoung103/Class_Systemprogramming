#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int sum =0;

    if(argc=!3){
        fprintf(stderr,"error\n");
        return -1;
    }

    int start =atoi(argv[1]);
    int finish=atoi(argv[2]);
    for(int i=start;i<=finish;i++){
        sum+=i;
    }
    printf("Pid: [%ld] sum(%d ~ %d)=%d\n",(long)getpid(),start,finish,sum);
    return 0;
}