#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<stdlib.h>


sem_t sem1;
sem_t sem2;

void *sem_a(void *arg);
void *sem_b(void *arg);
void *sem_c(void *arg);

int main()
{
        int state = 0;
        pthread_t t1,t2,t3;
        void * result_t = NULL;
    
        sem_init(&sem1,0,0);
        sem_init(&sem2,0,1);    
        
        pthread_create(&t1,NULL,sem_a,NULL); 
        pthread_create(&t2,NULL,sem_b,NULL);
        pthread_create(&t3,NULL,sem_c,NULL); 
        pthread_join(t1,&result_t);
        pthread_join(t2,&result_t);
        pthread_join(t3,&result_t);
        
        
        printf("\nAll threads done!!\n");
        sem_destroy(&sem1);
        sem_destroy(&sem2);
        return 0;
}
void *sem_a(void *arg)
{
    for(int i=0;i<5;i++){
        printf("A");
        usleep(2);
    }
}
void *sem_b(void *arg)
{
    
    for(int i=0;i<5;i++){
        
        printf("B");
        usleep(2);
    }
}
void *sem_c(void *arg)
{
    for(int i=0;i<5;i++){
        
        printf("C");
        usleep(2);
    }
}
 