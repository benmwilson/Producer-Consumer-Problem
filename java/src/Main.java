// 
//  Producer-Consumer-Problem Main Class
// 

public class Main {
  public static Monitor monitor;

  public static void main(String[] args) {

    monitor = new Monitor(10);

    Producer producer = new Producer(Integer.parseInt(args[2]), Integer.parseInt(args[1]), Integer.parseInt(args[0])); // use args
    
    producer.start();

    for (int x = 0; x < Integer.parseInt(args[0]); x++) { // start up all the consumers/slave threads required
      new Consumer(x).start();

    }
  }
}