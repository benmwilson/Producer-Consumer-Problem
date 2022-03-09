# Producer-Consumer-Problem Java Implementation

## How to Compile

Navigate to `/java/src/` and open a new terminal. Inside this terminal, type `javac Main.java` to compile the main execution file. 

All the files should come pre-compiled. If you come across errors, try compiling `Consumer.java`, `Monitor.java`, and `Producer.java` again the same as you did for `Main.java`.

## How to Run the Code

Navigate to `/java/src/` and open a new terminal. Inside this terminal, type `java Main X Y Z`, where;

X is the desired number of consumers, Y is the max duration of a request, and Z is sleep time between request generation.

Example: `java Main 8 8 8 `

## Implementation

This implementation of the Producer-Consumer-Problem relies on a `Main.java` class that calls on `Consumer.java`, `Monitor.java`, and `Producer.java`. The Producer creates requests with a random ID and random job length to be picked up by a Consumer. The Producer and Consumer do not directly modify the queue, instead they interact with the Monitor and the Monitor modifies the queue accordinly. 

Once a request is created, it is stored in the `requestQueue` to be picked up by a Consumer. Once a Consumer is granted a request, it processes (consumer thread sleeps to imitate work) it for its specified duration. Upon completing the request, the Consumer thread goes idle until it is assigned a new request to complete.

The Producer and Consumer communicate with the Monitor via notify() and wait() methods. When the queue is full, the Producer will wait until it becomes empty and will notify a Consumer thread when this happens. Also when the queue is empty, the Consumer will wait and notify the Producer thread.

This problem was quite interesting to implement in Java. There are already lots of implementatations of this problem, and when I was figuring out my implementation I decided to go with things I knew worked well already. Using a LinkedList for the queue was found to be easier than working with Arrays and provided some nice methods to help in computation. Overall, this was a somewhat tough project but with a thought out plan and execution mixed with good research, it went over quite well.

## Sample Output

View a sample output [here](src/sampleoutput.txt) 

### References

- https://docs.oracle.com/javase/tutorial/essential/environment/cmdLineArgs.html
- https://www.techiedelight.com/queue-implementation-in-java/
