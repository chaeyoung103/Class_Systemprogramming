#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int isPrimeNumber(int n);
int countNumber(int ss, int ee);
int main(int argc, char *argv[]) {
    int n, i;
    int count = 0;
    int num = 0;
    int fd[2];
    char buf2[256];
    pid_t childpid = 0;
     pid_t parentpid;
    if (argc != 3) {
            fprintf(stderr, "error");
            return 0;
    }
    n = atoi(argv[1]);
    i = atoi(argv[2]);
    int ss = 1, ee = n / i;
    int temp = ee;
    pipe(fd);
    for (int j = 0; j < i; j++) {
        if(childpid>0){
            parentpid = getpid();
        }
        if ((childpid = fork()) == 0) {
            int cnt = countNumber(ss, ee);
            printf("Process[%ld] has found %d prime numbers in (%d ~ %d).\n", (long) getpid(), cnt, ss, ee);
            sprintf(buf2,"%d ",cnt);
            num = write(fd[1],buf2,strlen(buf2));
            return num;
        }
        ss = ee + 1;
        ee += temp;
        if (j == i - 2) {
                ee = n;
        }
     }
    int stat_loc;
    int prime = 0;
    int temp2;
    int waitPid;
     while((waitPid = waitpid(childpid,&stat_loc,0))>0){

        char buf[100];
        read(fd[0],buf,stat_loc);
        char *ptr = strtok(buf, " ");
        while(ptr!=NULL){
            prime+=atoi(ptr);
            ptr = strtok(NULL, " ");
        }
     }
    printf("[%d] has found %d prime numbers in (%d~%d)\n",parentpid, prime,1, n);
    return 0;
}

int countNumber(int ss, int ee) {
            int cnt = 0;
            for (; ss <= ee; ss++) {
                   if (isPrimeNumber(ss)) {
                         cnt++;
                   }
            }
            return cnt;
}

int isPrimeNumber(int n) {

        int i = 0;
        int last = n / 2;
        if (n <= 1)
                return 0;
        for (i = 2; i <= last; i++) {
                if ((n % i) == 0)
                        return 0;
        }
        return 1;
}