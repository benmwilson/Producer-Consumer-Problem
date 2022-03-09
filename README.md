<h1 align="center">
  The Producer-Consumer Problem
</h1>
<p align="center">
  
</p>

<p align="center">
In computing, the producer-consumer problem (also known as the bounded-buffer problem) is a classic example of a multi-process synchronization problem. The problem describes two processes, the producer and the consumer, which share a common, fixed-size buffer used as a queue. This repo houses two implementations of this problem coded in Java and C/C++.
  
</p> 

<p align="left">
  🚧
 This code was developed for the COSC 315 Operating Systems course at the University of British Columbia Okanagan.
  🚧
</p>

<br><br>

## Table of Contents

- [Documentation](#documentation)
- [Contributors](#contributors)
- [Resources](#resources) TBA



### Documentation
 - [Project Outline](#project-outline)
 - [Design Choices](#design-choices) TBA
 - [Feautres](#features) TBA
 - [Sample Output](/sampleoutputs.txt) TBA
 
 
#### Project Outline

The goal of this project is to use threads and synchronization to implement an
useful application based on the Producer Consumer problem, also known as the bounded-buffer problem.
This project has two parts, one completed in Java and another in C/C++
with the overall goal of demonstrating threading and synchronization
concepts in two widely used programming languages.

####Code compliation
Navigate to mainB.c and open a new terminal. Inside this terminal for windows, type:
step 1:gcc mainB.c -pthread to compile the main execution file.
step2: type ./a.out

Upon receiving the prompt how many threads would you like: 
input an integer

#### Implementation

The main function initializes the number of threads, mutex, pthreads and semaphores.
Two semaphores were created:
  sem_wait(&full) - Decements the sempahore by 1 and causes the caller to suspen execution waiting for subsequent thread
  sem_post(&full) - Increments the value of the semaphore by 1 and if any threads are waiting on the semaphore, wake one of them up
pthread(): 
  pthread_mutex_init(&mutex, NULL) was used to declare a mutex and initialize default mutex attributes 

A for loop was used to start a new thread upto N+1 if i is zero generate and Producer other otherwise it generates a consumer thread,additionaly pthread_create was used within the loop starts a new thread in the producer and consumer threads and initalizes the value to NULL so modified attributes arent affected.
Lastly, the thread and semaphore objects where destroyed using pthread_mutex_destroy, sem_destroy(&empty), and sem_destroy(&full)
 
Producer functions:
The producer was set to execute a set number of requests and add them to the circular buffer, using a random sleep value betwwen 1 and 5, the producer will sleep for the a timer is set when it wakes and begins by decrementing the semaphore by 1 the locking the mutex. At which point a random product id is generated and a time is calculated to generate the request id and the time it took to execute. After which the request is added to the buffer slot is then incremented by 1. Lastly the mutex is unlocked, and the semaphore is incremented.

 

Consumer functions: 
The consumer was set to consume a set number of requests and remove them to the circular buffer, using a random sleep value betwwen 1 and 5, the consumer will sleep for the a timer is set when it wakes and begins by decrementing the semaphore by 1 the locking the mutex. At which point a random an existing request id is consumed and a time is calculated to consume the request id and the time it took to be consumed. After which the request after which the mutex is unlocked, and the semaphore is incremented. Then the buffer slot is decemented by 1, and the consumer waits for another request id to be generated to repeat the process.


#### Features


<p align="center">
Circular Buffer
Pthreads to have mutiple consumers take from the queue
Semaphore to ensure consumer/producer notify each other when a new action can be performed
Mutext to gaurentee mutual exclusion in the critical section of code(enqueue, dequeue)
Timer/delay function to make the producer/consumer wait n seconds to emulate execution time
  </p>
### Contributors
 - [Ben Wilson](https://github.com/benmwilson)
 - [Eric Shanks](https://github.com/EricShanks68)
 - [Richardo Brown](https://github.com/Buttertoastt)

### Resources

