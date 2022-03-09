// 
//  Producer-Consumer-Problem Producer/Master thread
// 

public class Producer extends Thread {

  int maxReqLength, requestCount, id, requestLength, sleepTime;

  public Producer(int s, int l, int n) { // this data comes from the args in Main class
    sleepTime = s;
    maxReqLength = l;
    requestCount = n * 2;
  }

  public void run() {

    while (requestCount != 0) {

      id = (int) (Math.random() * 100); // generate random id from 1-100, couldn't get the sequentially increasing id to work
      
      requestLength = (int) (Math.random() * (double) maxReqLength) + 1; // generate requestLength based on the maxReqLength set in args

      int[] newRequest = new int[] { id, requestLength }; // generate new request

      try {

        Main.monitor.enqueue(newRequest); // enqueue the newly generated request
        System.out.println("[ PD ]: Producer going to bed for " + sleepTime + " second(s), goodnight...");
        sleep(sleepTime); // sleep for alloted sleep time

      } catch (Exception e) { // simple error catching
        System.out.println("[ PD ]: Exception... whoopsie!");
      }
      requestCount--;
    }
    System.out.println("[ PD ]: Producer terminated. See ya next time, nerd!");
  }

}