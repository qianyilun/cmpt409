import java.util.*;

/**
 * Created by yilunq on 12/01/18.
 */
class Node {
    String name;
    List<Node> neighbors;
    public Node(String name) {
        this.name = name;
        neighbors = new ArrayList<Node>();
    }
}
public class ErdosNumber {
    public static void main(String[] args) {
        List<String> input = new ArrayList<>();
        String v1 = "A,B,Erdos";
        String v2 = "Erdos,C";
        String v3 = "A,D";
        String v4 = "E, F";
        input.add(v1);
        input.add(v2);
        input.add(v3);
        input.add(v4);

        System.out.println(new ErdosNumber().findErdosNumber());
    }

    private int findErdosNumber() {
        List<String> nameList = new ArrayList<String>();
        nameList.add("A");

        List<String> paperDatabase = new ArrayList<>();
        paperDatabase.add("A");
        paperDatabase.add("B");
        paperDatabase.add("Erodos");

        // 1. initial graph
        Map<String, Set<String>> graph = initialGraph(nameList, paperDatabase);

        // 2. bfs
        Queue<String> queue = new LinkedList<>();
        queue.offer("A");

        int edrosNumber = 0;

        while (!queue.isEmpty()) {
            edrosNumber++;

            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String head = queue.poll();

                for (String neighbor : graph.get(head)) {
                    if (neighbor.equals("Erodos")) {
                        return edrosNumber;
                    }
                }
            }
        }
        return -1;
    }

    private Map<String, Set<String>> initialGraph(List<String> nameList, List<String> paperDatabase) {
        Map<String, Set<String>> graph = new HashMap<>();

        // add other's names to its Set
        for (String name : nameList) {
            graph.put(name, new HashSet<String>());
            for (String author : paperDatabase) {
                if (!author.equals(name)) {
                    graph.get(name).add(author);
                }
            }
        }
        return graph;
    }
}
