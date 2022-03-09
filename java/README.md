# Producer-Consumer-Problem Java Implementation

## How to Compile

Navigate to `/java/src/` and open a new terminal. Inside this terminal, type `javac Main.java` to compile the main execution file. 

All the files should come pre-compiled. If you come across errors, try compiling `Consumer.java`, `Monitor.java`, and `Producer.java` again the same as you did for `Main.java`.

## How to Run the Code

Navigate to `/java/src/` and open a new terminal. Inside this terminal, type `java Main X Y Z`, where;

X is the desired number of consumers, Y is the max duration of a request, and Z is sleep time between request generation.

Example: `java Main 8 8 8 `

## Sample Output

View a sample output [here](src/sampleoutput.txt) 

### References

- https://docs.oracle.com/javase/tutorial/essential/environment/cmdLineArgs.html
- https://www.techiedelight.com/queue-implementation-in-java/
