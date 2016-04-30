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
import java.util.NoSuchElementException;

public class Tester2 {

    public static void main(String[] args) {
        System.out.println("Testing Queues");
        System.out.println("==============\n\n\n");

        System.out.println("We form a queue with the names Papa Bill, Mark,"
                + " Ali Baba.");

        CircularQueue<String> profs = new CircularQueue<String>();
        profs.add("Papa Bill");
        profs.add("Mark");
        profs.add("Ali Baba");

        System.out.println("We add the names Shrek, Jeff the Chef, Hex");
        profs.add("Shrek");
        profs.add("Jeff the Chef");
        profs.add("Hex");

        System.out.println("The queue has " + profs.getSize() + " persons.");

        System.out.println("We delete 4 names.");
        for (int i = 1; i <= 4; i++) {
            System.out.println("The delete name is " + profs.remove());
        }
        System.out.println("The name on top is " + profs.getFirst());
        System.out.println("We delete 2 more names.");
        for (int i = 1; i <= 1; i++) {
            System.out.println("The delete name is " + profs.remove());
        }
        System.out.println("Now, isEmpty() is " + profs.isEmpty());

        System.out.println("We add the names Shrek, Jeff the Chef, Hex");
        profs.add("Shrek");
        profs.add("Jeff the Chef");
        profs.add("Hex");
        
        
        System.out.println("We try to remove a name.");
        try {
            String name = profs.remove();
            System.out.println("The delete name is " + name);
        } catch (NoSuchElementException e) {
            System.out.println("We get a NoSuchElementException");
        }
    }   // end main
//System.out.println("After f: " + f + "\tr: " + r + "\tsize: " + getSize());
}
