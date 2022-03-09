// 
//  Producer-Consumer-Problem Consumer/Slave Class
// 

public class Consumer extends Thread {

  int id;

  public Consumer(int i) {

    id = i;

  }

   int i = 2;

  public void run() {

    while (i != 0) {
    
      try {

        int[] temp = Main.monitor.dequeue();

        sleep(temp[1]);
        
        System.out.println("[ C" + this.id + " ]: Request ID " + temp[0] + " completed at time " + System.currentTimeMillis());

      } catch (InterruptedException e) {
        
        System.out.println("[ C" + this.id + "]: Exception... whoopsie!");
      }
      
      i--;
    }
    System.out.println("[ C" + this.id + " ]: Consumer terminated!");
  }
}