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

import java.util.LinkedList;
import java.util.List;

public class Assignment2 {

    /**
     * METHOD 4 Method that deletes all duplicate items from list. Use the
     * equals method to check for duplications.
     *
     * @param <T> type of object in linked list
     * @param list linked list that contain duplicates
     */
    public static <T> void eliminateDuplicates(LinkedList<T> list) {
        int listSize = list.size();

        for (int i = 0; i < listSize; i++) {
            T element = list.get(i);
            int listSize2 = listSize - i;

            for (int j = i + 1; j < listSize; j++) {
                T element2 = list.get(j);
                if (element.equals(element2)) {
                    list.remove(j);
                    listSize--;
                }
            }
        }
    }

    /**
     * METHOD 5 Sorts list in the increasing order of compareTo. Does not use
     * the Collections class. Makes recursive call to insert to order the
     * LinkedList using the insertion sort algorithm.
     *
     * @param <T> type of object in linked list
     * @param list linked list to be sorted
     */
    public static <T extends Comparable<? super T>> void sort(LinkedList<T> list) {
        if (list.size() > 1) {
            //remove an item and recursively sort it through insertion
            T item = list.remove(0);
            sort(list);
            insert(item, list);
        }
    }

    /**
     * METHOD 5 Method recursively inserts an element into a LinkedList in
     * order.
     *
     * @param <T> type of object in linked list
     * @param item item being inserted to list
     * @param list linked list to be sorted
     */
    public static <T extends Comparable<? super T>> void insert(T item, LinkedList<T> list) {

        if (list.isEmpty() || item.compareTo(list.get(0)) <= 0) {
            //recurssion base case
            list.add(0, item);
        } else {
            //remove the first element and insert item recuresively
            T first = list.remove(0);
            insert(item, list);
            list.add(0, first);
        }
    }

    /**
     * METHOD 6 We define the Grandpa strings as follows:
     *
     * 1. ab is a Grandpa string.
     *
     * 2. bca is a Grandpa string.
     *
     * 3. If S is a Grandpa string, so is SaS.
     *
     * 4. If U and V are Grandpa strings, so is UbV.
     *
     * Here a, b, c are constants and S,U,V are variables. In these rules, the
     * same letter represents the same string. So, if S = ab, rule 3 tells us
     * that abaab is a Grandpa string. In rule 4, U and V represent Grandpa
     * strings, but they may be different.
     *
     * @param in a String to test if it is a Grandpa string
     * @return true if S is a Grandpa string and false otherwise
     */
public static boolean isGrandpa(String in) {

        String S = "";

        if (in.length() <= 1) {
            return false;
        }
        if (in.equals("ab")) {
            return true;
        }
        if (in.length() == 3) {
            if (in.charAt(1) == 'a') {
                if (in.charAt(0) == 'a' || in.charAt(0) == 'b' || in.charAt(0) == 'S' || in.charAt(0) == 'T' || in.charAt(0) == 'U') {
                    return in.charAt(0) == in.charAt(2);
                }
                return false;
            }
            if (in.charAt(1) == 'c') {
                if (in.charAt(0) == 'a' || in.charAt(0) == 'b') {
                    return (in.charAt(2) == 'a' || in.charAt(2) == 'b');
                }
            }
            if (in.charAt(1) == 'b') {
                if (in.charAt(0) == 'S' || in.charAt(0) == 'U' || in.charAt(0) == 'V') {
                    return (in.charAt(2) == 'S' || in.charAt(2) == 'U' || in.charAt(2) == 'V');
                }
            }
        }
        if (in.length() >= 5 && isGrandpa(in.substring(0, 2)) && in.substring(0, 2).equals(in.substring(3, 5))) {
            if (in.length() > 5) {
                return isGrandpa("S" + in.substring(2, 3) + "S" + in.substring(5));
            }
            return true;
        }

        return false;
    }


    /**
     * METHOD 7 Returns an index where x occurs in the array a, or -1 if x is
     * not in a. Assume that a is sorted in increasing order. Use the binary
     * search method.
     *
     * @param <T> type of object in array
     * @param a array of items being searched for x
     * @param x item being searched for in list
     * @param low low boundary of binary search
     * @param high high boundary of binary search
     * @return index of item x if it exists in list, -1 if x does not exist in
     * list
     */
    public static <T extends Comparable< ? super T>> int find(T[] a, T x, int low, int high) {

        if (high < low) {     //item is not in array
            return -1;
        } else {              //check if item is in array
            int mid = (high + low) / 2;

            if (x.compareTo(a[mid]) < 0) {
                return find(a, x, low, mid - 1);
            } else if (x.compareTo(a[mid]) > 0) {
                return find(a, x, mid + 1, high);
            } else {
                return mid;
            }
        }
    }

    /**
     * METHOD 8 Sorts the array a in increasing order. The method must be a
     * short recursive program. Do not use the methods quicksort, merge sort, or
     * the Arrays class. Method uses bubble sort algorithm.
     *
     * @param <T>
     * @param a
     */
    
    public static <T extends Comparable< ? super T>> void sort(T[] a) {
        sort(a, 0);
    }

    /**
     * METHOD 8
     *
     * @param <T> type of object in array
     * @param a array of items being sorted
     * @param initVal how many times has the algorithm run already
     */
    private static <T extends Comparable< ? super T>> void sort(T[] a, int initVal) {

        T tmp; //used as temporary storage when switching values in array

        //bubble biggest element to end
        for (int i = 1; i < a.length; i++) {
            if (a[i - 1].compareTo(a[i]) > 0) {
                tmp = a[i - 1];
                a[i - 1] = a[i];
                a[i] = tmp;
            }
        }

        //recursive call to sort remainder of list
        if (initVal < a.length) {
            sort(a, ++initVal);
        }
    }
}
