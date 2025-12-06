import javax.swing.tree.TreeNode;
import java.sql.SQLOutput;
import java.util.HashMap;
import java.util.Scanner;

public class Lab7 {

    static int solve(BTree<String> tree, BNode<String> node){
        if (node == null || (node.left == null && node.right == null)) return 0;
        if (node.left != null && node.right != null) return 1 + solve(tree, node.left) + solve(tree,node.right);
        return solve(tree, node.left) + solve(tree,node.right);
    }

    public static void main(String[] args) {
        BTree<String> tree = new BTree<>();
        HashMap<String, BNode<String>> table = new HashMap<>();
        Scanner in = new Scanner(System.in);
        String line = in.nextLine();
        int n = Integer.parseInt(line.split(" ")[0]);
        int q = Integer.parseInt(line.split(" ")[1]);
        for (int i = 0; i < n + q; i++) {
            line = in.nextLine();
            String []parts = line.split(" ");
            if (line.startsWith("root")){
                tree.makeRoot(parts[1]);
                table.put(parts[1], tree.root);
            }
            else if (line.startsWith("add")){
                BNode<String> parent = table.get(parts[1]);
                int a = parts[3].equals("LEFT") ? 1 : 2;
                BNode<String> child = tree.addChild(parent,a, parts[2]);
                table.put(parts[2], child);
            }
            else if (line.startsWith("ask")){
                System.out.println(solve(tree, table.get(parts[1])));
            }
        }

    }
}