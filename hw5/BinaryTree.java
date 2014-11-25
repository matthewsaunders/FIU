package hw5;

import java.util.NoSuchElementException;
import java.util.Stack;

public class BinaryTree<T> {

    /**
     * Creates an empty binary tree
     */
    public BinaryTree() {
        root = null;
    }

    // create a binary tree with a given root value
    public BinaryTree(T rootItem) {
        root = new BinaryNode(rootItem, null, null);
        size = 1;
    }

    public BinaryTree(BinaryNode<T> node) {
        root = node;
        size = BinaryNode.size(node);
    }

    // @return the root of the tree
    public BinaryNode<T> getRoot() {
        return root;
    }

    // @return the size of the tree
    public int size() {
        return size;
    }

    // @return the the height of the tree
    public int height() {
        return BinaryNode.height(root);
    }

    // print the tree in preorder
    public void printPreOrder() {
        if (root != null) {
            root.printPreOrder();
        }
    }

    // print the tree in postorder
    public void printPostOrder() {
        if (root != null) {
            root.printPostOrder();
        }
    }

    // print the tree in inorder
    public void printInOrder() {
        if (root != null) {
            root.printInOrder();
        }
    }

    // empty the tree
    public void makeEmpty() {
        root = null;
        size = 0;
    }

    // check if the tree is empty
    public boolean isEmpty() {
        return root == null;
    }

    // forms a new tree from rootItem t1 and t2 
    // does not allow t1 and t2 to be the same
    public void merge(T rootItem, BinaryTree<T> t1, BinaryTree<T> t2) {
        if (t1.root == t2.root && t1.root != null) {
            throw new IllegalArgumentException();
        }

        // allocate new node
        root = new BinaryNode<T>(rootItem, t1.root, t2.root);
        size = t1.size() + t2.size() + 1;
        // ensures that every node is in one tree
        if (this != t1) {
            t1.root = null;
        }
        if (this != t2) {
            t2.root = null;
        }
    }

    public T get(int i) {
        //throw exception if index is greater than size or negative
        if (i > size - 1 || i < 0) {
            throw new NoSuchElementException("index " + i + " is out of bounds [0.." + size + "]");
        }

        Stack<BinaryNode<T>> s = new Stack();
        BinaryNode<T> current = root;

        while (current != null || !s.empty()) {
            if (current != null) {
                s.push(current);
                current = current.getLeft();
            } else // pop the stack and go right
            {
                current = s.pop();
                //if true, return this node
                if (i-- == 0) {
                    return current.getElement();
                }
                current = current.getRight();
            }
        }

        return current.getElement();
    }

    public void add(int i, T element) {
        //throw exception if index is greater than size or negative
        if (i > size || i < 1) {
            throw new IndexOutOfBoundsException("index " + i + " is out of bounds [0.." + size + "]");
        }

        Stack<BinaryNode<T>> s = new Stack();
        BinaryNode<T> current = root;
        boolean rightsubtree = false;
        i--;

        while (current != null || !s.empty()) {
            if (current != null) {
                s.push(current);
                current = current.getLeft();
            } else {
                current = s.pop();
                //if true, return this node
                if (i == 0) {
                    BinaryNode<T> node = new BinaryNode<>(element, null, null);

                    if (!rightsubtree) {
                        if (current.getRight() != null) { //go right once
                            current = current.getRight();
                        }
                        while (current.getLeft() != null) {
                            current = current.getLeft();
                        }
                        current.setLeft(node);
                    } else {
                        if (current.getLeft() != null && !current.getElement().equals(get(this.size() - 1))) { //go right once
                            current = current.getLeft();
                        }
                        while (current.getRight() != null) {
                            current = current.getRight();
                        }
                        current.setRight(node);
                    }
                    size++;
                    return;
                }
                current = current.getRight();
                if (current != null && current.equals(root.getRight())) {
                    rightsubtree = true;
                }
                i--;
            }
        }
    }

    public T remove(int i) {
        //throw exception if index is greater than size or negative
        if (i > size - 1 || i < 0) {
            throw new NoSuchElementException("index " + i + " is out of bounds [0.." + size + "]");
        }

        BinaryNode<T> node = root.find(get(i));
        BinaryNode<T> parent = null;
        BinaryNode<T> current = root;
        Stack<BinaryNode<T>> s = new Stack();
        boolean parentHasLeft = false;
        boolean parentHasRight = false;
        boolean nodeHasLeft = false;
        boolean nodeHasRight = false;
        boolean inRightSubtree = false;
        boolean childIsLeftNode = false;

        if (node.getLeft() != null) {
            nodeHasLeft = true;
        }
        if (node.getRight() != null) {
            nodeHasRight = true;
        }

        //removing root node
        if (node.equals(root)) {
            if (!nodeHasLeft && !nodeHasRight) {
                root = null;
            } else if (nodeHasLeft && !nodeHasRight) {
                root = root.getLeft();
            } else if (!nodeHasLeft && nodeHasRight) {
                root = root.getRight();
            } else {
                BinaryNode<T> temp = root;
                current = node.getLeft();
                while (current.getRight() != null) {
                    temp = current;
                    current = current.getRight();
                }

                //erase node before making it root
                if (temp.getLeft().equals(current)) {
                    temp.setLeft(null);
                } else {
                    temp.setRight(null);
                }
                
                //set left and right subtree of new root node
                current.setLeft(root.getLeft());
                current.setRight(root.getRight());
                root = current;
            }

        } else {
            //Get parent node in tree structure
            while ((current != null || !s.empty()) && parent == null) {

                if (current != null) {
                    s.push(current);
                    current = current.getLeft();
                } else {
                    current = s.pop();
                    if (current.equals(root.getRight())) {
                        inRightSubtree = true;
                    }
                    //if true, return this node
                    if ((current.getLeft() != null && current.getLeft().equals(node)) || (current.getRight() != null && current.getRight().equals(node))) {
                        if (current.getLeft() != null && current.getLeft().equals(node)) {
                            childIsLeftNode = true;
                        }
                        parent = current;
                    } else {
                        current = current.getRight();
                    }
                }
            }

            if (parent.getLeft() != null) {
                parentHasLeft = true;
            }
            if (parent.getRight() != null) {
                parentHasRight = true;
            }

            //leaf node
            if (!nodeHasLeft && !nodeHasRight) {
                if (childIsLeftNode) {
                    parent.setLeft(null);
                } else {
                    parent.setRight(null);
                }
            } //node has one child
            //true if child is left node
            else if (nodeHasLeft && !nodeHasRight) {
                parent.setLeft(node.getLeft());
            } //true if child is right node
            else if (!nodeHasLeft && nodeHasRight) {
                parent.setLeft(node.getLeft());
            }//node has two children
            else {
                current = node.getLeft();
                while (current.getRight() != null) {
                    current = current.getRight();
                }

                if (childIsLeftNode) {
                    parent.setLeft(current);
                } else {
                    parent.setRight(current);
                }
            }
        }

        size--;
        return node.getElement();
    }
    // https://www.youtube.com/watch?v=gcULXE7ViZw&noredirect=1

    private BinaryNode<T> root;
    private int size = 0;
}
