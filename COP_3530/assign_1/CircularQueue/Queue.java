/* COURSE      : COP 3530
 * Section     : U03
 * Semester    : Fall 2014
 * Instructor  : Alex Pelin
 * Author      : Matthew Saunders
 * Assignment #: 1
 * Due date    : September 18th, 2014
 * Description : Insert a 2-3 line description of the assignment
 *
 *                                      
 */

package CircularQueue;

public interface Queue<AnyType> {

    // add an item
    void add(AnyType item);
    // remove an item, throw NoSuchElementException if the queue is empty
    AnyType remove();
    // get the first element without removing it
    // throw NoSuchElementException if the queue is empty
    AnyType getFirst();
    // get the size
    int getSize();
    // check if the queue is empty
    boolean isEmpty();
    // empty the queue
    void clear();
}
