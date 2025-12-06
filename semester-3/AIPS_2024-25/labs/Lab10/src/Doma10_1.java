import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class Doma10_1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        HashMap<String, Integer> vertices = new HashMap<>();
        int n = in.nextInt();
        AdjacencyMatrixGraph<String> graph = new AdjacencyMatrixGraph<>(n);
        in.nextLine();
        for (int i = 0; i < n; i++) {
            String s = in.nextLine();
            graph.addVertex(i, s);
            vertices.put(s, i);
        }
        int m = in.nextInt();
        in.nextLine();
        for (int i = 0; i < m; i++) {
            String []parts = in.nextLine().split(" ");
            graph.addEdge(vertices.get(parts[0]), vertices.get(parts[1]), Integer.parseInt((parts[2])));
        }

        List<Edge> path = graph.kruskal();
        int ans = 0;
        for (Edge e : path){
            ans += e.getWeight();
        }
        System.out.println(ans);
    }
}