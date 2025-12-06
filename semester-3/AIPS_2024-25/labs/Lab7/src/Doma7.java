import java.util.HashMap;
import java.util.Scanner;


public class Doma7 {
    static public int count(SLLTree<Integer> tree, Tree.Node<Integer> root){
        int ctr = 0;
        if (tree.childCount(root) == 0) return 1;
        for (Tree.Node<Integer> child : tree.childrenNodes(root)){
            ctr += count(tree, child);
        }
        return ctr;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        SLLTree<Integer> tree = new SLLTree<>();
        HashMap<Integer, Tree.Node<Integer>> table = new HashMap<>();
        int n = in.nextInt(); // functions
        int q = in.nextInt(); // questions
        in.nextLine();
        String line;
        while (n > 0 || q > 0){
            line = in.nextLine();
            String []info = line.split(" ");
            if (line.startsWith("root")){
                tree.makeRoot(Integer.parseInt(info[1]));
                table.put(Integer.parseInt(info[1]), tree.root);
                n--;
            } else if (line.startsWith("add")){
                int index = Integer.parseInt(info[2]);
                SLLTree.Node<Integer> parent = table.get(Integer.parseInt(info[1]));
                Tree.Node<Integer> child = tree.addChild(parent, index);
                table.put(index, child);
                n--;
            } else {
                Tree.Node<Integer> node = table.get(Integer.parseInt(info[1]));
                System.out.println(count(tree, node));
                q--;
            }
        }
    }
}