/* COURSE      : COP 3530
 * Section     : U03
 * Semester    : Fall 2014
 * Instructor  : Alex Pelin
 * Author      : Matthew Saunders
 * Assignment #: 2
 * Due date    : October 2, 2014
 * Description : The Assignment2 class consists of methods #4, 5, 6, 7, 8 from 
 *              the homework assignment 2.  A summary of each method:
 *              4 - Eliminates duplicate methods in a generic LinkedList.
 *              5 - Sorts a generic LinkedList.
 *              6 - Determines if a string is a grandpa string or not
 *              7 - Finds element in generic array using binary search.
 *              8 - Sorts a generic array.
 */

package assign2;

import java.util.Arrays;
import java.util.LinkedList;

public class Assignment2_Tester {
    
    public static void main(String [ ] args){
        //Assignment2 a = new Assignment2();
        
        //test method 4
        testMethod4();
        
        //test method 5
        testMethod5();
        
        //test method 6
        testMethod6();
        
        //test method 7
        testMethod7();
        
        //test method 8
        testMethod8();
    }
    
    private static void testMethod4(){
        LinkedList<String> ll = new LinkedList<>();
        ll.add("Ricky");
        ll.add("Bobby");
        ll.add("Baby");
        ll.add("Jesus");
        ll.add("Baby");
        ll.add("Jesus");
        ll.add("Baby");
        
        System.out.println("---------------------------------------------------------------");
        System.out.println("\t\t\tTest method 4");
        System.out.println("---------------------------------------------------------------\n");
        System.out.println("...before method call:\n\t"+ll);
        System.out.println("...Calling method");
        
        Assignment2.eliminateDuplicates(ll);
        
        System.out.println("...after method call:\n\t"+ll);
        System.out.println("\n---------------------------------------------------------------");
        System.out.println("---------------------------------------------------------------\n");
        return;
    }
    
    private static void testMethod5(){
        LinkedList<myNumber> ll = new LinkedList<>();
        ll.add(new myNumber(57));
        ll.add(new myNumber(245));
        ll.add(new myNumber(6));
        ll.add(new myNumber(14));
        ll.add(new myNumber(95));
        ll.add(new myNumber(73));
        ll.add(new myNumber(1));
        
        System.out.println("---------------------------------------------------------------");
        System.out.println("\t\t\tTest method 5");
        System.out.println("---------------------------------------------------------------\n");
        System.out.println("...before method call:\n\t"+ll);
        System.out.println("...Calling method");
        
        Assignment2.sort(ll);
        
        System.out.println("...after method call:\n\t"+ll);
        System.out.println("\n---------------------------------------------------------------");
        System.out.println("---------------------------------------------------------------\n");
        return;
    }
    
    private static void testMethod6(){
        String a = "ab";
        String b = "bca";
        String c = "SaS";
        String d = "UbV";
        String e = "SaaS";
        String f = "bV";
        String g = "abaab";
        String h = "abaabbab";
        
        System.out.println("---------------------------------------------------------------");
        System.out.println("\t\t\tTest method 6");
        System.out.println("---------------------------------------------------------------\n");
        System.out.println("...Calling method");
        
        System.out.println("...isGrandpa("+a+"):\t"+Assignment2.isGrandpa(a));
        System.out.println("...isGrandpa("+b+"):\t"+Assignment2.isGrandpa(b));
        System.out.println("...isGrandpa("+c+"):\t"+Assignment2.isGrandpa(c));
        System.out.println("...isGrandpa("+d+"):\t"+Assignment2.isGrandpa(d));
        System.out.println("...isGrandpa("+e+"):\t"+Assignment2.isGrandpa(e));
        System.out.println("...isGrandpa("+f+"):\t"+Assignment2.isGrandpa(f));
        System.out.println("...isGrandpa("+g+"):\t"+Assignment2.isGrandpa(g));
        System.out.println("...isGrandpa("+h+"):\t"+Assignment2.isGrandpa(h));
        System.out.println("\n---------------------------------------------------------------");
        System.out.println("---------------------------------------------------------------\n");
        return;
    }
    
    private static void testMethod7(){
        myNumber[] a = new myNumber[7];
        a[0] = new myNumber(0);
        a[1] = new myNumber(1);
        a[2] = new myNumber(9);
        a[3] = new myNumber(14);
        a[4] = new myNumber(26);
        a[5] = new myNumber(73);
        a[6] = new myNumber(156);

        myNumber aFALSE = new myNumber(75);
        myNumber aTRUE = new myNumber(73);
        
        System.out.println("---------------------------------------------------------------");
        System.out.println("\t\t\tTest method 7");
        System.out.println("---------------------------------------------------------------\n");
        System.out.println("...a before method call:\n\t"+Arrays.toString(a));
        System.out.println("...Calling method");
        
        int low = 0;
        int high = a.length-1;
        
        System.out.println("...aFalse:\t"+Assignment2.find(a, aFALSE, low, high)+"\texpected: " + -1);
        System.out.println("...aTrue:\t"+Assignment2.find(a, aTRUE, low, high)+"\texpected: " + 5);
        
        System.out.println("\n---------------------------------------------------------------");
        System.out.println("---------------------------------------------------------------\n");
        return;
    }
    
    private static void testMethod8(){
        myNumber[] a = new myNumber[7];
        a[0] = new myNumber(57);
        a[1] = new myNumber(245);
        a[2] = new myNumber(6);
        a[3] = new myNumber(14);
        a[4] = new myNumber(95);
        a[5] = new myNumber(73);
        a[6] = new myNumber(1);
        
        System.out.println("---------------------------------------------------------------");
        System.out.println("\t\t\tTest method 8");
        System.out.println("---------------------------------------------------------------\n");
        System.out.println("...a before method call:\n\t"+Arrays.toString(a));
        System.out.println("...Calling method");
        
        Assignment2.sort(a);
        
        System.out.println("...LinkedList after method call:\n\t"+Arrays.toString(a));
        System.out.println("\n---------------------------------------------------------------");
        System.out.println("---------------------------------------------------------------\n");
        return;
    }
    
    public static class myNumber implements Comparable<myNumber>{

        private int num;

        public myNumber(int x){
            num = x;
        }

        public void setNum(int x){
            num = x;
        }

        public int getNum(){
            return num;
        }

        @Override
        public int compareTo (myNumber other){
            return (num - other.getNum());
        }
        
        public String toString(){
            return "" + num;
        }
    }
    
}

