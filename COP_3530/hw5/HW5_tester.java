package hw5;

public class HW5_tester {
    public static void main(String [ ] args){
        System.out.println("HW #5 Tester");
    
        System.out.println("-----------------------------------\n");
        System.out.println("Let's create a tree...\n");        
        System.out.println("              1");
        System.out.println("            /   \\");
        System.out.println("          2       3");
        System.out.println("        /  \\     /  \\");
        System.out.println("      4	   5     6   7");
        System.out.println("    / \\	        /     \\");
        System.out.println("   8   9       10     11");
        System.out.println("         \\             /");
        System.out.println("          12          13");
        System.out.println("          /");
        System.out.println("         14");
    
        BinaryNode<String> n14 = new BinaryNode<>("14", null, null);
        BinaryNode<String> n13 = new BinaryNode<>("13", null, null);
        BinaryNode<String> n12 = new BinaryNode<>("12", n14, null);
        BinaryNode<String> n11 = new BinaryNode<>("11", n13, null);
        BinaryNode<String> n10 = new BinaryNode<>("10", null, null);
        BinaryNode<String> n9 = new BinaryNode<>("9", null, n12);
        BinaryNode<String> n8 = new BinaryNode<>("8", null, null);
        BinaryNode<String> n7 = new BinaryNode<>("7", null, n11);
        BinaryNode<String> n6 = new BinaryNode<>("6", n10, null);
        BinaryNode<String> n5 = new BinaryNode<>("5", null, null);
        BinaryNode<String> n4 = new BinaryNode<>("4", n8, n9);
        BinaryNode<String> n3 = new BinaryNode<>("3", n6, n7);
        BinaryNode<String> n2 = new BinaryNode<>("2", n4, n5);
        BinaryNode<String> n1 = new BinaryNode<>("1", n2, n3);
        
        System.out.println("Creating a new BinaryTree...");
        BinaryTree tree = new BinaryTree(n1);
        System.out.println("...size of BinaryTree:");
        System.out.println("\tExpected:\t14");
        System.out.println("\tActual:\t\t" + tree.size());
        
        System.out.println("\nInorder traversal of tree...");
        tree.printInOrder();
        System.out.println("");
        
        /*
        Test the get method
        */
        System.out.println("\n\n\nTesting get() method:");
        try{
            System.out.println("...get(0):\t");
            System.out.println("\tExpected:\t8");
            System.out.println("\tActual:\t\t" + tree.get(0));

            System.out.println("...get(1):\t");
            System.out.println("\tExpected:\t4");
            System.out.println("\tActual:\t\t" + tree.get(1));

            System.out.println("...get(2):\t");
            System.out.println("\tExpected:\t9");
            System.out.println("\tActual:\t\t" + tree.get(2));

            System.out.println("...get(3):\t");
            System.out.println("\tExpected:\t14");
            System.out.println("\tActual:\t\t" + tree.get(3));

            System.out.println("...get(4):\t");
            System.out.println("\tExpected:\t12");
            System.out.println("\tActual:\t\t" + tree.get(4));

            System.out.println("...get(5):\t");
            System.out.println("\tExpected:\t2");
            System.out.println("\tActual:\t\t" + tree.get(5));
            
            System.out.println("...get(6):\t");
            System.out.println("\tExpected:\t5");
            System.out.println("\tActual:\t\t" + tree.get(6));

            System.out.println("...get(7):\t");
            System.out.println("\tExpected:\t1");
            System.out.println("\tActual:\t\t" + tree.get(7));

            System.out.println("...get(8):\t");
            System.out.println("\tExpected:\t10");
            System.out.println("\tActual:\t\t" + tree.get(8));
            
            System.out.println("...get(9):\t");
            System.out.println("\tExpected:\t6");
            System.out.println("\tActual:\t\t" + tree.get(9));

            System.out.println("...get(10):\t");
            System.out.println("\tExpected:\t3");
            System.out.println("\tActual:\t\t" + tree.get(10));

            System.out.println("...get(11):\t");
            System.out.println("\tExpected:\t7");
            System.out.println("\tActual:\t\t" + tree.get(11));
            
            System.out.println("...get(12):\t");
            System.out.println("\tExpected:\t13");
            System.out.println("\tActual:\t\t" + tree.get(12));

            System.out.println("...get(13):\t");
            System.out.println("\tExpected:\t11");
            System.out.println("\tActual:\t\t" + tree.get(13));

        }catch(Exception e){
            System.out.println("get() Failed: " + e.toString());
        }
        
        /*
        Test insert method
        */
        System.out.println("\n\n\nTesting add() method:");
        try{

            System.out.println("\n...add(1):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            tree.add(1, "add0");
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nNew size is " + tree.size());
            
            System.out.println("\n...add(4):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            tree.add(4, "add4");
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nNew size is " + tree.size());
            
            System.out.println("\n...add(16):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            tree.add(16, "add16");
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nNew size is " + tree.size());
            
            System.out.println("\n...add(11):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            tree.add(11, "add11");
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nNew size is " + tree.size());
            
        }catch(Exception e){
            System.out.println("...add() Failed: " + e.toString());
        }
        
        /*
        Test delete method
        */
        System.out.println("\n\n\nTesting remove() method:");
        try{
            String element;
            
            System.out.println("\n...remove(0):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            element = (String)tree.remove(0);
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nRemoved element " + element);
            System.out.println("New size is " + tree.size());
            
            System.out.println("\n...remove(3):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            element = (String)tree.remove(3);
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nRemoved element " + element);
            System.out.println("New size is " + tree.size());
            
            System.out.println("\n...remove(9):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            element = (String)tree.remove(9);
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nRemoved element " + element);
            System.out.println("New size is " + tree.size());
            
            System.out.println("\n...remove(14):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            element = (String)tree.remove(14);
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nRemoved element " + element);
            System.out.println("New size is " + tree.size());
            
            System.out.println("\n...remove(7):\t");
            System.out.print("before: ");
            tree.printInOrder();
            System.out.println("");
            element = (String)tree.remove(7);
            System.out.print("after: ");
            tree.printInOrder();
            System.out.println("\nRemoved element " + element);
            System.out.println("New size is " + tree.size());
            
        }catch(Exception e){
            System.out.println("...remove() Failed: " + e.toString());
        }
        
    }
}
