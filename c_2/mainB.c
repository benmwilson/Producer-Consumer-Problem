#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


//#define SLEEP_TIMEOUT = 10000

#define MAX 5    //Number of slots initially available in the buffer
int M = 6;   //Max sleep time
int buffer[MAX];   //Circular buffer array of size MAX, allows the producer to add and the consumer to remove objects     
int fill = 0;
int take = 0;

sem_t empty; // number of empty semaphore slots
sem_t full;  // number of filled semaphore slots
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Initializes the static mutex mutex, setting its attributes to default values
time_t begin,end;
time_t sec,val =1;
long duration;
struct tm * currentTime;

void *producer(void *args) {
    int rand_sleep;
    for (int i = 0; i < MAX; i++){
        rand_sleep = rand() % M; // generates random sleeping time
        long k;
        begin= time(NULL);
        for(k = 0; k < 100000000; k++);
        int product = rand(); // Produce a random product
        sem_wait(&empty); // Decements the integer value of the semaphore by 1 which causes the caller to suspend execution waiting for subsequent thread
        pthread_mutex_lock(&mutex);// Prompting the Scheduler to do a context switch, which blocks threads ready to execute
        sleep(rand_sleep);
        buffer[fill] = product;
        end = time(NULL);
        duration = difftime(end, begin);
        sec = time(NULL);
        currentTime = localtime(&sec);
        printf("Producer %d: produced request id %d, length %.6ld seconds, at current time is %02d:%02d:%02d\n", getppid(), buffer[fill], duration, (currentTime->tm_hour),(currentTime->tm_min),(currentTime->tm_sec));
        fill = (fill + 1);
        pthread_mutex_unlock(&mutex); // Releases the mutex object and is no longer the owner releases the lock
        sem_post(&full); // Increments the value of the semaphore by 1 and if any threads are waiting on the semaphore, wake one of them up 
        
        begin= time(NULL);
        for(k = 0; k < 100000000; k++);
        sleep(rand_sleep);
        end = time(NULL);
        duration = difftime(end, begin);
        
        printf("Producer: sleeping for %.2f seconds\n", (float)duration ); 
    }
    return 0;
}

void *consumer(void *args) {
    int pid = 0;
    int rand_sleep;
    if(pid == 0){
        sleep(1);
    for (int i = 0; i < MAX; i++){
         pid = fork();
        rand_sleep = rand() % 6;
        long k;
        begin= time(NULL);
        for(k = 0; k < 150000000; k++);
        sem_wait(&full);// Decements the integer value of the semaphore by 1 which causes the caller to suspend execution waiting for subsequent thread
        int a =sleep(rand_sleep);
        pthread_mutex_lock(&mutex);// Prompting the Scheduler to do a context switch, which blocks threads ready to execute
        int product = buffer[fill];
        end = time(NULL);
        duration = difftime(end, begin);
        currentTime = localtime(&sec);
        printf("Consumer %d: assigned request ID %d for the next %.6ld seconds, current time is %02d:%02d:%02d\n", getpid(), product, duration, (currentTime->tm_hour),(currentTime->tm_min),(currentTime->tm_sec)); 
        pthread_mutex_unlock(&mutex);// Releases the mutex object and is no longer the owner releases the lock
        sem_post(&empty);
        sleep(rand_sleep);
        fill =(fill - 1);
        currentTime = localtime(&sec);
        printf("Consumer %d: completed request ID %d at %02d:%02d:%02d\n", getpid(), product, (currentTime->tm_hour),(currentTime->tm_min),(currentTime->tm_sec)); 
        wait(NULL);
        }
        return 0;   
   }
}

int main(int argc, char* argv[]){

    int THREAD_NUM;
    printf("Enter the number of consumer threads: ");
    scanf("%d", &THREAD_NUM); 

    pthread_t thread[THREAD_NUM+11]; // declares thread and the number available
    pthread_mutex_init(&mutex, NULL);// declares a mutex andinitialize default mutex attributes
    sem_init(&empty,0,MAX); // declares semaphore, 0 indicates shared resource, MAX indicates the value of mutex
    sem_init(&full,0,0);  // declares semaphore, 0 indicates shared resource, 0 indicates the value of mutex
    srand(time(NULL));

    //int container[5] = {1,2,3,4,5};
    int i;
    for ( i = 0; i < THREAD_NUM+1; i++){    
        if(i == 0 ){
            if(pthread_create(&thread[i], NULL, &producer, NULL)!= 0){ // starts a new thread in the producer and initaalizes the value to NULL so modified attributes arent affected
                perror("Failed to make producer thread!");
            }
        }else{
            if(pthread_create(&thread[i], NULL, &consumer, NULL)!= 0){ // starts a new thread in the consumer and initaalizes the value to NULL so modified attributes arent affected

                perror("Failed to make consumer thread!");
            }
        }
    }
    for ( i = 0; i < THREAD_NUM+1; i++){ 
        if(pthread_join(thread[i], NULL) !=0){// blocks the calling thread until the target thread 's in process terminates
            perror("I'm tired! Can't join");
        }       
    }
    //Shared resource protection
    pthread_mutex_destroy(&mutex); //Deletes mutex object, which identifies a mutex
    sem_destroy(&empty); //Deletes empty semaphore object, which identifies a semaphore
    sem_destroy(&full);  //Deletes empty semaphore object, which identifies a semaphore
    
    return 0;
}