import java.util.*;

/**
 * Created by yilunq on 12/01/18.
 */
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
        nameList.add("D");

        List<String> paperDatabase = new ArrayList<>();
        paperDatabase.add("A");
        paperDatabase.add("B");
        paperDatabase.add("Erodos");

        String[] papers = new String[]{"A, B, Erodos", "Erodos, C", "A, D", "E, F"};

        // 1. initial graph
        Map<String, Set<String>> graph = new HashMap<>();
        for (int i = 0; i < papers.length; i++) {
            initialGraph(graph, papers[i]);
        }

        System.out.println(graph);


        // 2. bfs
        Queue<String> queue = new LinkedList<>();
        queue.offer("D");

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
                    queue.offer(neighbor);
                }
            }
        }
        return -1;
    }

    private void initialGraph(Map<String, Set<String>> graph,
                              String paper) {
        // parse paper database
        String[] authors = paper.split(", ");
//        System.out.println(Arrays.toString(authors));

        // add other's names to its Set
        for (String author : authors) {
            if (!graph.containsKey(author)) {
                graph.put(author, new HashSet<String>());
            }
        }


        for (int i = 0; i < authors.length; i++) {
            for (int j = 0; j < authors.length; j++) {
                if (i != j) {
                    graph.get(authors[i]).add(authors[j]);
                }
            }
        }


//        for (String name : nameList) {
//            if (!graph.containsKey(name)) {
//                graph.put(name, new HashSet<String>());
//            }
//            for (String author : authors) {
//                if (!author.equals(name)) {
//                    graph.get(name).add(author);
//                }
//            }
//        }
    }
}
