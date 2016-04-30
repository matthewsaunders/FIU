package hw5;

import java.util.ArrayList;
import java.util.Stack;
import java.lang.reflect.Array;
import java.util.LinkedList; // to simulate a queue

public class BinaryNode<T> 
{
    
    // create an empty node
    public BinaryNode() 
    {
        this(null, null, null);
    }
    
    // create a node with given value and children
    public BinaryNode(T theElement, BinaryNode<T> lt, BinaryNode<T> rt)
    {
        element = theElement;
        left = lt;
        right = rt;
    }
    
    // return the element
    public T getElement()
    {
        return element;
    }
    
    // return the left child
    public BinaryNode<T> getLeft()
    {
        return left;
    }
    
    // return the right child
    public BinaryNode<T> getRight()
    {
        return right;
    }
    
    // set the element to a given value
    // @param x is the new value
    public void setElement( T x)
    {
        element = x;
    }
    
    // set the left child
    // @param t is the left child
    public void setLeft(BinaryNode<T> t)
    {
        left = t;
    }
    
    // set the right child
    // @param t is the right child
    public void setRight(BinaryNode<T> t)
    {
        right = t;
    }
    
    // @return the size of the subtree at node t 
    public static <T> int size( BinaryNode<T> t)
    {
        if ( t == null)
            return 0;
        else
            return 1 + size(t.left) + size(t.right);
    }
    
    // @return the height of the subtree of node t
    public static <T> int height( BinaryNode<T> t)
    {
        if (t == null)
            return -1;
        else 
            return 1 + Math.max(height(t.left), height(t.right));
    }

    // find if an item occurs in the tree
    // @param inq is the inquiry
    public BinaryNode<T> find(T inq)
    {
        if (element.equals(inq))
            return this;
        BinaryNode<T> out = null;
        if ( left != null)
        {
            out = left.find(inq);
        }    
        if ( out != null)
            return out;
        else if ( right != null)
            out = right.find(inq);
        return out;
    }    
    
    // create a duplicate tree
    // @return the root of the duplicate tree
    public BinaryNode<T> duplicate()
    {
        BinaryNode<T> root = new BinaryNode<T>(element,null,null);
        if ( left != null)
            // create a duplicate tree for the left subtree
            root.left = left.duplicate();
        if (right != null)
            root.right = right.duplicate();
        return root;
    }
    
    
    // print the tree elements in preorder
    public void printPreOrder()
    {
        System.out.print(element + ", ");
        if (left != null)
            left.printPreOrder();
        if (right != null)
            right.printPreOrder();
    }
    
   
    // print the tree elements in postorder // iterativeInorder
    public void iterativePreOrder()
    {
      
        Stack<BinaryNode<T>> s = new Stack();
        BinaryNode<T> current = this;
        while (current != null || !s.empty())
        {
            if (current != null)
            {
                System.out.println(current.element);
                // process it, put it in the stack, and go left
                s.push(current);
                current = current.left;
            }
            else // pop the stack and go right
            {
                current = s.pop();
                current = current.right;
            }
        }    
    }
   
   
        
    // print in post order
    public void printPostOrder()
    {
        if (left != null)
            left.printPostOrder();
        if (right != null)
            right.printPostOrder();
        System.out.println(element);
    }
   
    
    // print the tree elements in inorder
    public void printInOrder()
    {
        if (left != null)
            left.printInOrder();
        System.out.print(element + " ");
        if (right != null)
            right.printInOrder();
    }
   
    // the fields
    private T element;
    private BinaryNode<T> left;
    private BinaryNode<T> right;
}
