#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>



#define MAX 5           //BufferSize
#define producer_MAX 1 // MaxItems
int buffer[MAX];
int fill = 0;
int take = 0;


sem_t empty;
sem_t full;
//sem_t mutex;
pthread_mutex_t mutex;

void *producer(void *pid) {
    int product;
    for (int i = 0; i < MAX; i++) {
        product = rand(); // Produce a random product
        sem_wait(&empty);
        // scope of lock reduced
        pthread_mutex_lock(&mutex);
        buffer[fill] = product;
        printf("Producer %d: Added item %d at %d\n", *((int *)pid), buffer[fill], fill); 
        fill = (fill + 1)%MAX;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cpid) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&full);
        // scope of lock reduced
        pthread_mutex_lock(&mutex);
        int product = buffer[take];
        printf("Consumer %d: consumed item %d from %d\n", *((int *)cpid), product, take); 
        take = (take + 1)%MAX;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
    }
}

int main()
{
    pthread_t prod[5],cons[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,1,MAX);
    sem_init(&full,0,1);
    
    int container[5] = {1,2,3,4,5};
    for(int i = 1; i<2; i++){
        pthread_create(&prod[i], NULL, (void *)producer, (void *)&container[i]);
    }
    for(int i = 0; i<MAX; i++){
        pthread_create(&cons[i], NULL, (void *)consumer, (void *)&container[i]);
    }
    for(int i = 0; i<1; i++){
        pthread_join(prod[i],NULL);
    }
    for(int i = 0; i<MAX; i++){
        pthread_join(prod[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


/*

#define MAX 1

int buffer[MAX];
int fill = 0;
int use  = 0;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int b = buffer[use];
    use = (use + 1) % MAX;
    return b;
}

int loops = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(∅);
 
        // scope of lock reduced
        sem_wait(&mutex;);
        put(i);
        sem_post(&mutex;);

        sem_post(&full;);
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&full;);

        // scope of lock reduced
        sem_wait(&mutex;);
        int b = get();
        sem_post(&mutex;);

        sem_post(∅);
        printf("%d\n", b);
    }
}

struct shmseg{
    int cntr;
    int write_done;
};

void shared_memory_cntr_incremment(int pid, struct shmseg* shmp, int total_count);
int main(int argc, char *argv[])
{

int shmid;
struct shmseg* shmp;
char* bufptr;
int total_count;
int sleep_time;
pid_t pid;

if(argc != 2){
    total_count = 10000;
}else{
    total_count = atoi(argv[1]);
    if(total_count <10000){
        total_count = 10000;
    }
}
printf("Total count is %d\n", total_count);
//shhmid = shmget(sizeof(struct shmseg), 0644|IPS_CREAT);


//Parent Process - Runs once



}
*/




