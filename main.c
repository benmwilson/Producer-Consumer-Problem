#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define SLEEP_TIMEOUT = 10000
#define THREAD_NUM  10
#define MAX 5    //Number of slots initially available in the buffer
int buffer[MAX];        
int fill = 0;
int take = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
clock_t start,end,duration;

void *producer(void *args) {
    for (int i = 1; i < MAX+1; i++){
        start = clock();
        int product = rand(); // Produce a random product
        sem_wait(&empty);
        // scope of lock reduced
        pthread_mutex_lock(&mutex);
        buffer[fill] = product;
        end = clock();
        duration = ((float)(end-start))/(CLOCKS_PER_SEC/1000);
        printf("Producer %d: produced request id %d, length %.f seconds at %d\n", getppid(), buffer[fill], (float)duration, fill);
        start =clock();
        fill = (fill + 1);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(10);
        end = clock();
        duration = ((float)(end-start))/(CLOCKS_PER_SEC/1000);
        printf("Producer: sleeping for %.f milliseconds\n", (float)duration ); 
    }
}

void *consumer(void *args) {
    int pid = fork();
    if(pid == 0){
            sleep(1);
        }
        for (int i = 1; i < MAX; i++){
            start = clock();
            sem_wait(&full);
            // scope of lock reduced
            pthread_mutex_lock(&mutex);
            int product = buffer[take];
            pthread_mutex_unlock(&mutex);
            end = clock();
            duration = ((float)(end-start))/(CLOCKS_PER_SEC/1000);  
            printf("Consumer %d: assigned request ID %d for the next %.f seconds (caller: %d)item from %d\n", getpid(), product, (float)duration , i,  take);
            sem_post(&empty);
            start =clock();
            take =(take + 1)%MAX;
            sleep(10);
            end = clock();
            duration = ((float)(end-start))/(CLOCKS_PER_SEC/1000);
            printf("Consumer: sleeping for %.f milliseconds\n", (float)duration ); 
            wait(NULL);
            return 0;   
        }
}

int main(int argc, char* argv[]){

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