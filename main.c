#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define TIMER = 1000
#define THREAD_NUM  3
#define MAX 5    //Number of slots initially available in the buffer
int buffer[MAX];        
int fill = 0;
int take = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *args) {
    int c1;
    for (int i = 0; i < MAX; i++)
    {
       
    
        c1 = 1;
        int product = rand(); // Produce a random product
        sem_wait(&empty);
        // scope of lock reduced
        pthread_mutex_lock(&mutex);
        buffer[fill] = product;
        printf("Producer: produced request id %d, length x seconnds at %d\n",  buffer[fill], fill);
        fill = (fill + 1);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        c1++;
        sleep(1); 
    }
    
}

void *consumer(void *args) {
    for (int i = 1; i < MAX+1; i++)
    {    
        sem_wait(&full);
        // scope of lock reduced
        pthread_mutex_lock(&mutex);
        int product = buffer[take];
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer %d: consumed item %d from %d\n", i, product, take);
        take =(take + 1)%MAX;
        sleep(1);   
    }
}

int main(int argc, char* argv[])
{
    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,MAX);
    sem_init(&full,0,0);
    srand(time(NULL));

    //int container[5] = {1,2,3,4,5};
    int i;
    for ( i = 0; i < THREAD_NUM; i++){    
        if(i == 0 ){
            if(pthread_create(&thread[i], NULL, &producer, NULL)!= 0){
                perror("Failed to make producer thread!");
            }
        }else{
            if(pthread_create(&thread[i], NULL, &consumer, NULL)!= 0){
                perror("Failed to make consumer thread!");
            }
        }
    }
    for ( i = 0; i < THREAD_NUM; i++){ 
        if(pthread_join(thread[i], NULL) !=0){
            perror("I'm tired! Can't join");
        }       
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
