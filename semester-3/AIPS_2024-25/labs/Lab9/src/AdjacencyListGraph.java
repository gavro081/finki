import java.util.*;

class AdjacencyListGraph<T> {
    private Map<T, Set<T>> adjacencyList;

    public AdjacencyListGraph() {
        this.adjacencyList = new HashMap<>();
    }

    public void addVertex(T vertex) {
        adjacencyList.putIfAbsent(vertex, new HashSet<>());
    }

    public void removeVertex(T vertex) {
        for (Set<T> neighbors : adjacencyList.values()) {
            neighbors.remove(vertex);
        }
        adjacencyList.remove(vertex);
    }

    public void addEdge(T source, T destination) {
        addVertex(source);
        addVertex(destination);
        adjacencyList.get(source).add(destination);
        adjacencyList.get(destination).add(source); // undirected
    }

    public void removeEdge(T source, T destination) {
        if (adjacencyList.containsKey(source))
            adjacencyList.get(source).remove(destination);
        if (adjacencyList.containsKey(destination))
            adjacencyList.get(destination).remove(source); // undirected
    }

    public Set<T> getNeighbors(T vertex) {
        return adjacencyList.getOrDefault(vertex, new HashSet<>());
    }

    // dfs rekurzivno
    public void DFS(T startVertex) {
        Set<T> visited = new HashSet<>();
        DFS_helper(startVertex, visited);
    }

    private void DFS_helper(T vertex, Set<T> visited) {
        visited.add(vertex);
        System.out.println(vertex + " ");

        for (T neighbor : getNeighbors(vertex)) {
            if (!visited.contains(neighbor))
                DFS_helper(neighbor, visited);
        }
    }

    // nerekurziven DFS so pomos na stack
    public void DFSNonRecursive(T startVertex) {
        Set<T> visited = new HashSet<>();
        Stack<T> stack = new Stack<>();

        stack.push(startVertex);

        while (!stack.isEmpty()) {
            T vertex = stack.pop();
            if (!visited.contains(vertex)) {
                visited.add(vertex);
                System.out.println(vertex + " ");
                for (T neighbor : getNeighbors(vertex))
                    if (!visited.contains(neighbor))
                        stack.push(neighbor);
            }
        }
    }

    // nerekurziven BFS
    public void BFS(T startVertex) {
        Set<T> visited = new HashSet<>();
        Queue<T> queue = new LinkedList<>();

        visited.add(startVertex);
        queue.add(startVertex);

        while (!queue.isEmpty()) {
            T vertex = queue.poll();
            System.out.println(vertex + " ");

            for (T neighbor : getNeighbors(vertex)) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
    }
}
