import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Lab9 {
    static int solve(AdjacencyListGraph<Integer> graph, Set<Integer> vertices){
        Set<Integer> visited = new HashSet<>();
        int ctr = 0;
        for (int vertex : vertices){
            if (!visited.contains(vertex)) {
                dfs(vertex, graph, visited);
                ctr++;
            }
        }
        return ctr;
    }

    static public void dfs(int node, AdjacencyListGraph<Integer> graph, Set<Integer>visited) {
        visited.add(node);
        for (int neighbor: graph.getNeighbors(node)){
            if (!visited.contains(neighbor)) dfs(neighbor, graph, visited);
        }
    }
    public static void main(String[] args) {
        AdjacencyListGraph<Integer> graph = new AdjacencyListGraph<>();
        Scanner in = new Scanner(System.in);
        Set<Integer> vertices = new HashSet<>();
        int n = in.nextInt();
        int m = in.nextInt();
        for (int i = 0; i < m; i++) {
            int v1 = in.nextInt();
            int v2 = in.nextInt();
            graph.addVertex(v1);
            graph.addVertex(v2);
            graph.addEdge(v1, v2);
            vertices.add(v1);
            vertices.add(v2);
        }
        int r = in.nextInt();
        graph.removeVertex(r);
        vertices.remove(r);
        System.out.println(solve(graph, vertices));
    }
}