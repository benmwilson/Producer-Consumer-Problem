// 
//  Producer-Consumer-Problem Monitor Class
// 

import java.util.*;

public class Monitor {
    int count;
    int size;

    public static Queue<int[]> requestQueue; // requestQueue to hold the queue of requests that are queueing up

    public Monitor(int s) {
        requestQueue = new LinkedList<int[]>(); // use LinkedList because they're easy and better than arrays for this
                                                // application
        count = 0;
        size = s;
    }

    synchronized void enqueue(int[] request) throws InterruptedException {

        while (count == size) { // while queue full, wait
            wait();
        }

        requestQueue.add(request); // add request to queue
        count++;
        System.out.println("[P->M]: Produced request ID " + request[0] + " of length " + request[1] + " second(s) at time "
                + System.currentTimeMillis());

        if (count == 1) // queue empty, notify slave thread
            notify();
    }

    synchronized int[] dequeue() throws InterruptedException {

        while (count == 0) { // while queue fill, wait
            wait();
        }

        int[] newRequest = requestQueue.peek(); // peak at last request in queue and steal its personal information and
                                                // identity ha ha ha

        System.out.println("[C->M]: Processing request ID " + newRequest[0] + " for " + newRequest[1]
                + " second(s) at time " + System.currentTimeMillis());
        requestQueue.remove(); // remove requst from queue
        count--;

        if (count == (size - 1)) // queue empty, notify master thread
            notify();
            
        return newRequest;
    }
}