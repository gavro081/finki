import java.util.Scanner;

public class Lab8 {

    static int dfs(BNode<Integer>node, int val){
        if (node == null) return 0;
        if (node.info < val) {
            return 1 + dfs(node.left, val) + dfs(node.right, val);
        }

        return dfs(node.left, val);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String line = "";
        BinarySearchTree<Integer> tree = new BinarySearchTree<>();
        int n = in.nextInt();
        int q = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n + q; i++) {
            line = in.nextLine();
            String[] parts = line.split(" ");
            if (line.startsWith("i")){
                tree.insert(Integer.parseInt(parts[1]));
            }
            else {
                System.out.println(dfs(tree.getRoot(), Integer.parseInt(parts[1])));
            }
        }
    }
}