<h1 align="center">
  The Producer-Consumer Problem
</h1>
<p align="center">
  
</p>

<p align="center">
In computing, the producer-consumer problem (also known as the bounded-buffer problem) is a classic example of a multi-process synchronization problem. The problem describes two processes, the producer and the consumer, which share a common, fixed-size buffer used as a queue. This repo houses two implementations of this problem coded in Java and C/C++.
  
</p> 

<p align="center">
  🚧
 This code was developed for the COSC 315 Operating Systems course at the University of British Columbia Okanagan.
  🚧
</p>

<br><br>

## Table of Contents

- [Documentation](#documentation)
- [Branches](#branches)
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

#### Design Choices
As a group, we decided to split the project into three implementations, each contributor making their own implementation. 

* Java design choices:

* Eric's C design choices:

    * Circular queue:
      * A circular queue was implemented to keep track of the values in the queue, such that as items continuously added and removed from the queue, there would be no out of bounds concern, or need for reallocation/dynamic memory. Helper functions such as enqueue, dequeue, isFull, isEmpty, display were created.

* Main function:
  * The main function initializes the queue , pthreads, and semaphores. 
  * Three semaphores were created; a semaphore that acted as a mutex to lock the critical sections of code, a semaphore with the count equal to the spaces in the queue to ensure the producer only writes when the queue is not full, a semaphore that ensures the consumer to only take when the queue is not empty an enables the producer and consumer to update each other when resources are available.
  * Pthreads were created, one dedicated to creating the producer, the rest creating consumers.
  * Joining the threads when finished and destroying/cleaning resources.

* Producer and consumer functions:

  * Producer: The producer was set to execute a set number of requests rather than to continuously, and infinitely attempt to enqueue to the circular queue. This was purely for testing purposes. The main functionality of the producer was to use a semaphore to wait until there was room in the queue to enqueue, then use a semaphore as a mutex to guarantee mutual exclusion while updating the queue, then unlocking the mutex, and finally posting (incrementing) the last semaphore to tell consumers there is another value in the queue, so then the consumer can then consumer it. 

  * Consumer: Checks the semaphore that the producer posted. If there is a positive value, the consumer can use the mutex to lock, dequeue from the queue, unlock the mutex, post to the semaphore that lets the producer know there is another spot available in the queue, then do the task that it was assigned from the queue.

* Features that did not get implemented:
  * I had trouble getting the consumers to have the values of when they were created assigned to them. I could not get both changing values and a static queue to be passed to all threads. From what I can understand the pthread parameters can only take either static variables or being passed a different set of parameters with different values. Thus I was not able to pass a queue that all threads needed to see and individual consumer numbers. Ways I could have fixed this would be to change the way I implemented my circular queue. I made my circular queue first and did not have the foresight to see that I should have designed it in a way to be manually initialized globally rather than having an initialize method that needed to be called to initialize the queue, so I would be able to simply reference the queue in the producer and consumer functions, rather than having to pass the queue through the pthread parameters allowing the consumer numbers to be passed.
  * I replaced the interator numbers with the pthread ids to keep track of the consumers


#### Features


### Branches
 - [Ben Wilson's branch](https://github.com/benmwilson/Producer-Consumer-Problem/tree/ben-java-implementation)
 - [Eric Shanks's branch](https://github.com/benmwilson/Producer-Consumer-Problem/tree/newEric) 
 - [Richardo Brown's branch](https://github.com/benmwilson/Producer-Consumer-Problem/tree/c_implementation)

### Contributors
 - [Ben Wilson](https://github.com/benmwilson)
 - [Eric Shanks](https://github.com/EricShanks68) 
 - [Richardo Brown](https://github.com/Buttertoastt)

### Resources
* https://www.geeksforgeeks.org/circular-queue-set-1-introduction-array-implementation/
* https://www.programiz.com/dsa/circular-queue
* https://www.youtube.com/watch?v=FcIubL92gaI
* https://www.geeksforgeeks.org/use-posix-semaphores-c/
* https://www.geeksforgeeks.org/producer-consumer-problem-in-c/
* https://www.geeksforgeeks.org/semaphores-in-process-synchronization/
* https://www.educative.io/edpresso/how-to-create-a-simple-thread-in-c
* https://docs.oracle.com/cd/E19683-01/806-6867/6jfpgdcnj/index.html
* https://www.youtube.com/watch?v=ukM_zzrIeXs
* https://www.youtube.com/watch?v=l6zkaJFjUbM
* https://stackoverflow.com/questions/20196121/passing-struct-to-pthread-as-an-argument
* https://man7.org/linux/man-pages/man2/timer_create.2.html
* https://www.geeksforgeeks.org/time-h-header-file-in-c-with-examples/
* https://c-for-dummies.com/blog/?p=69
* https://stackoverflow.com/questions/3930363/implement-time-delay-in-c




