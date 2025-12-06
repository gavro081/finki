import java.util.Scanner;

public class InorderSuccessor {
    static void inorderSuccessor(BNode<Integer> node){
        if (node == null) return;
        inorderSuccessor(node.left);
        System.out.println(node.info);
        inorderSuccessor(node.right);
    }
    public static void main(String[] args) {;
        BinarySearchTree<Integer> tree = new BinarySearchTree<>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            tree.insert(in.nextInt());
        }

        inorderSuccessor(tree.getRoot());
    }
}