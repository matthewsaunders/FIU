/* COURSE      : COP 3530
 * Section     : U03
 * Semester    : Fall 2014
 * Instructor  : Alex Pelin
 * Author      : Matthew Saunders
 * Assignment #: 1
 * Due date    : September 18th, 2014
 * Description : The CircularQueue class creates a queue structure on an array
 *              of generics.  If the queue grows larger than the array, a new 
 *              array of the twice the current arrays size is made and all 
 *              elements are copied over.  If the start of the queue is not the 
 *              first element of the array, the queue will circle around and 
 *              fill the empty elements in the front of the array.                                     
 */

package CircularQueue;
import java.util.NoSuchElementException;

public class CircularQueue<AnyType> implements Queue<AnyType> {

    //instance variables
    private AnyType[] arr;    //queue of generic type
    private int f;      //front of queue
    private int r;      //rear of queue
    private static final int INIT_SIZE = 3;  //initial size of queue

    /**
     * Default constructor
     */
    public CircularQueue() {
        this(INIT_SIZE);
    }

    /**
     * Constructor using a user specified initial size
     *
     * @param size initial size of queue
     */
    public CircularQueue(int size) {
        arr = (AnyType[]) new Object[size];
        this.f = -1;
        this.r = -1;
    }

    /**
     * Add an item to the end of the queue. If the queue is full, the queue size
     * is doubled before the item is added.
     *
     * @param item being added to the queue
     */
    public void add(AnyType item) {
        //queue is full
        if (f == (r + 1) % arr.length) {
            //make new queue with double the size
            AnyType[] newArr = (AnyType[]) new Object[2 * arr.length];

            int numItems = getSize();
            for (int i = 0; i <= numItems; i++) {
                //copy queue element
                newArr[i] = arr[f++];
                if (f == arr.length) {
                    f = 0;
                }
            }
            f = 0;
            r = arr.length - 1;
            this.arr = newArr;
        }
        else if(r == arr.length - 1){
            r = -1;
        }
        //add new element
        arr[++r] = item;

        //initialize f to front of queue if new/empty queue
        if (f < 0) {
            f = 0;
        }
    }

    /**
     * Remove the element from the queue.
     *
     * @return element being removed
     */
    public AnyType remove() {
        //There are no elements in the queue
        if(isEmpty()){
            throw new NoSuchElementException();
        }
        
        //get first item in queue and move front of queue
        AnyType item = getFirst();
        if(f == r){
            f = -1;
            r = -1;
        }else{
            f++;
        }
        //if front of queue is past end of array, start at beginning
        if(f == arr.length){
            f = 0;
        }
        
        return item;
    }

    /**
     * Get the element stored at the front position in the queue.
     *
     * @return front element in queue
     */
    public AnyType getFirst() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        return arr[f];
    }

    /**
     * Calculate the size of (number of elements in) the queue.
     *
     * @return number of elements in queue
     */
    public int getSize() {
        //determine how to calculate size based on f and r positions
        if (f == -1 && r == -1) {
            return 0;
        } else if (r >= f) {
            return r - f + 1;
        } else {
            return arr.length - f + r + 1;
        }
    }

    /**
     * Test if the queue is empty or if it has elements in it. Return true if
     * empty.
     *
     * @return true if empty
     */
    public boolean isEmpty() {
        if (f == -1 && r == -1) {
            return true;
        }
        return false;
    }

    /**
     * Clear the queue of all elements.
     */
    public void clear() {
        this.f = -1;
        this.r = -1;
    }

    /**
     * Print image of CircularQueue instance variables to stdout
     */
    public void display(){
        System.out.println("CircularQueue");
        System.out.println("f: " + f + ", r: " + r + ", queue size: " + arr.length);
        System.out.print("contents: [");
        for(int i = 0; i < arr.length; i++){
            System.out.print(arr[i]);
            if(i == arr.length - 1){
                System.out.print("]\n");
            }else{
                System.out.print(", ");
            }
        }
    }
}
