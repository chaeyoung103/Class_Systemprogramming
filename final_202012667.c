#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <string.h>
#include <setjmp.h>

void * Inc(void * arg);
void * Dec(void * arg);
int num=0;
int count =0;
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
    if(argc<2){
        fprintf(stderr, "error\n");
        return -1;
    }
    num= atoi(argv[0]);

    pthread_mutex_init(&mutex, NULL);

    printf("initial count = %d\n",count);
    pthread_t inc;
    pthread_t dec;
    pthread_create(&inc, NULL,Inc, NULL);
    pthread_create(&dec, NULL,Dec, NULL);

    pthread_join(inc, NULL);
    pthread_join(dec, NULL);

    printf("final count = %d\n",count);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *Inc(void *arg ){
    for(int i =1;i<=num;i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
}

void *Dec(void *arg ){
    for(int i =1;i<=num;i++){
        pthread_mutex_lock(&mutex);
        count--;
        pthread_mutex_unlock(&mutex);
    }
}