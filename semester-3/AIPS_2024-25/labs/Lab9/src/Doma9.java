import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Doma9 {
    static int ctr = 0;
    static Set<Integer> visited = new HashSet<>();
    static int solve(int startVertex, int targetSum, AdjacencyListGraph<Integer> graph, int currsum){
        currsum += startVertex;
        if (currsum == targetSum) ctr++;
        if (currsum > targetSum) return -1;
//        visited.add(startVertex);
        for (int neighbor : graph.getNeighbors(startVertex)){
//            if (!visited.contains(neighbor))
            solve(neighbor, targetSum, graph, currsum);
        }
        return ctr;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        AdjacencyListGraph<Integer> graph = new AdjacencyListGraph<>();
        int n = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n; i++) {
            String line = in.nextLine();
            String []parts = line.split(" ");
            int p1 = Integer.parseInt(parts[0]);
            int p2 = Integer.parseInt(parts[1]);
            graph.addEdge(p1, p2);
        }
        int startVertex = in.nextInt();
        int targetSum = in.nextInt();
        System.out.println(solve(startVertex, targetSum, graph, 0));
    }
}