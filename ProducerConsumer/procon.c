
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


//turn some of the define values into user input values
#define NUM_THREADS 3
#define SIZE 5
#define NUM_REQUESTS 4
#define MAX_WAIT_TIME 7

//SEMAPHORE
sem_t mutex; //this locks the queue
sem_t wait_if_empty; //this makes consumer wait until there is something to grab
sem_t wait_if_full; //this makes producer wait until there is room to add to the queue


//QUEUE FUNCTIONS
typedef struct {
    int id, time;
    int message[];
}request;

void initRequest(request *r, int id, int time){
    r-> message[2];
}

typedef struct{
    int head;
    int tail;
    int size;
   request items[];
}queue;

//initialize Queue class
void initQueue(queue *q, int elements){
q-> head = -1;
q-> tail = -1;
q-> size = elements;
q -> items[elements];
}
//isEmpty
//if the queue is empty return 1(tr
int isEmpty(queue *q) {
    if(q->head == -1){
        return 1;
    } else{
        return 0;
    }
}

//isFull
//if the queue is full return 1(true)
int isFull(queue *q){
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == (q->size)- 1)) {
      // if((q->head == 0 && q->tail == (q->size) -1) || q->tail == (q->head)%((q->size)-1)){
        return 1;
    }else{return 0;}

}

void enqueue(queue *q, int id, int time){
     //int message[2] = {id, time};
     request message = {id, time};
    if(isFull(q)){
        printf("queue full (enqueue)\n");
    } else{
        if(q->head == -1){
            q->head = 0;
        }
        q->tail = (q->tail  + 1)% q->size;
        q->items[q->tail] = message;
        printf("Insert values id %d and execution time %d\n", message.id, message.time);
    }
}

request dequeue(queue *q){
    request return_values;
    if(isEmpty(q)){
        printf("empty queue\n");
    } else{
        return_values = q->items[q->head];
        printf("we dequeuing these values: %d, %d\n", return_values.id, return_values.time);
        if(q->head == q->tail){
            q->head = -1;
            q->tail = -1;
        } else{
            q->head = (q->head + 1) % q->size;
        }
        //printf("dequeue\n");
        return return_values;
    }
}

void display(queue *q){
    if(isEmpty(q)){
        printf("queue empty\n");
    } else{
        for(int i = q->head; i != q->tail; i = (i+1) %q->size){
            printf("the id is: %d, the execution time is: %d \n", q->items[i].id, q->items[i].time);
        }
        printf("the id is: %d, the execution time is: %d \n", q->items[q->tail].id, q->items[q->tail].time);
    }
}

//Pthread args
typedef struct{
    queue queue;
    int number;
}pargs;

//PRODUCER CONSUMER

void producer(queue *q){
    //pargs *producer_pargs = (pargs*)Pargs;
    int ID = 0;
    int wait;

    //Timer
    time_t pro_t;
    time(&pro_t);
    int randomTimeProducer;
    int timer_secs_init = clock() / CLOCKS_PER_SEC;
    int timer_secs_diff;
    int timer_elapsed;
   
        // //produce n amount of requests
    for(int i = 0; i < NUM_REQUESTS; i++){
        //wait for random seconds
        wait = 1;
        if(wait == 1){
            randomTimeProducer = rand() %MAX_WAIT_TIME;
            printf("producer is sleeping for %d seconds\n", randomTimeProducer);
            int timer_secs_init = clock() / CLOCKS_PER_SEC;
            while (timer_elapsed < randomTimeProducer)
            {
                timer_secs_diff = clock() / CLOCKS_PER_SEC;
                timer_elapsed = timer_secs_diff - timer_secs_init;
            }
            wait = 0;
        }
        
        //semaphore for producer
        sem_wait(&wait_if_full);
        //while the queue is not full -> add a value to the queue
        //if(!isFull(q)){
            sem_wait(&mutex); //lock the queue from being read
            ID++; //update id sequentially
            int randomTimeConsumer = rand() %(MAX_WAIT_TIME *2);
            enqueue(q, ID,randomTimeConsumer);
            //printf("inserted id: %d, time: %d\n", ID, randomTimeConsumer);
            display(q);
           // printf("\n");
            sem_post(&mutex); //release lock on updating the
    
      //  }
        sem_post(&wait_if_empty); //let consumer know there is a request available
    }
    //give the consumers a chance to consume final request
    // while(1){

    // }
    // while(!isEmpty(q)){
    //     wait = 1;
    //     if(wait == 1){
    //         randomTimeProducer = 30;
    //        printf("waiting for queue to be empty\n");
    //         int timer_secs = clock() / CLOCKS_PER_SEC;
    //         while (timer_secs < randomTimeProducer)
    //         {
    //             timer_secs = clock() / CLOCKS_PER_SEC;
    //         }
    //         wait = 0;
    //     }
    // }

}

 void consumer(queue *q){
    
    int isem = isEmpty(q);
    

    //values from queue
    request values;

    //Timer
    time_t con_t;
    time(&con_t);
    //each thread will run its own version of consumer, so busy is a local variable to that thread
    //try to consume
for(int i = 0; i < (NUM_REQUESTS); i++){
    int busy = 0;
        //wait until something to consume
        sem_wait(&wait_if_empty);
        //if(isEmpty(q) == 0){
        //lock and aquire data from the queue
        busy = 1;
        sem_wait(&mutex);
        values = dequeue(q);
        //printf("Consumer %d assigned request %d, processing request for the next %d seconds\n", pid_t, values.id, values.time);
        display(q);
        sem_post(&mutex);
       // }
        sem_post(&wait_if_full);

        if(busy == 1){
            // current time is CURRENT-TIME
            // Consumer i: completed request ID n at time CURRENT-TIME
            printf("the current time is: %s", ctime(&con_t));
            int timer_secs_init = clock() / CLOCKS_PER_SEC;
            int timer_secs_diff;
            int timer_elapsed;
            while (timer_elapsed < values.time)
            {
                timer_secs_diff = clock() / CLOCKS_PER_SEC;
                timer_elapsed = timer_secs_diff - timer_secs_init;
                //printf("timer:%d\n", timer_elapsed);
            }
            printf("Consumer %ld: completed request %d at %s\n", pthread_self(), values.id, ctime(&con_t));
           // printf("\n");
            busy = 0;
        }
    //need to go to top again
    }
}



//MAIN

pid_t pid_fork;
//main func

int main(int argc,  char* argv[]){
   // int num_threads = 5;
    pthread_t thread[NUM_THREADS];
    //pthread_t parent_thread;

    //intialize the queue
    queue q;
    
    initQueue(&q, SIZE);

     //initialize pthread arguments (queue)
    pargs thread_arg;
    thread_arg.queue = q;
     
    

    //initialize semaphore
     sem_init(&mutex, 0, 1); //mutex will always only have 1
     sem_init(&wait_if_full, 0, (SIZE));//the producer will be able to continue add to queue initally for the size of the queue
     sem_init(&wait_if_empty, 0, 0); //the queue is initally 0, so consumer cannot try to take something
     
    
    //these are the childern threads
    for(int i = 0; i <NUM_THREADS; i++){
        
        //parent //do we need to make the iiinital thread the parent thread?
        if(i == 0){
            fflush(stdout);
             thread_arg.number = i;
             pthread_create(&thread[i], NULL, (void *)producer, &thread_arg);
             
        } else{
            fflush(stdout);
            thread_arg.number = i;
            pthread_create(&thread[i], NULL, (void *)consumer, &thread_arg);
        }

    }
    fflush(stdout);
    //make the
    for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(thread[i], NULL);  
}

//destroy the semaphores
sem_destroy(&mutex);
sem_destroy(&wait_if_empty);
sem_destroy(&wait_if_full);
    

}




