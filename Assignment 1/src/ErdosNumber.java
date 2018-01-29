import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

/**
 * Created by yilunq on 12/01/18.
 *
 * Sample Input
 * 1
 * 4 3
 * Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factor matrices
 * Erdos, P., Reisig, W.: Stuttering in petri nets
 * Smith, M.N., Chen, X.: First oder derivates in structured programming
 * Jablonski, T., Hsueh, Z.: Selfstabilizing data structures
 * Smith, M.N.
 * Hsueh, Z.
 * Chen, X.
 * Sample Output
 * Scenario 1
 * Smith, M.N. 1
 * Hsueh, Z. infinity
 * Chen, X. 2
 */

public class ErdosNumber {
    public static void main(String[] args) throws IOException {
        Map<String, Set<String>> graph = new HashMap<>();

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine().trim();
        int scenarios = Integer.parseInt(line);
        for(int scenario = 0; scenario < scenarios; ++scenario) {
            System.out.println("Scenario " + (scenario + 1));
            String input = br.readLine().trim();
            while (input.length() == 0) {
                input = br.readLine().trim();
            }
            String[] parts = input.split("\\s+");
            int P = Integer.parseInt(parts[0].trim());
            int N = Integer.parseInt(parts[1].trim());

            for(int p = 0; p < P; ++p) {
                parts = br.readLine().trim().split("\\.[,\\:]");
                for (int i = 0; i < parts.length; i++) {
                    parts[i] = parts[i].trim() + ".";
                }

                initialGraph(graph, parts);
            }

            String[] inputNames = new String[N];
            for(int n = 0; n < N; ++n) {
                inputNames[n] = br.readLine().trim();
            }

            Map<String,Integer> result = bfs(graph);

            for (String name : inputNames) {
                if (result.get(name) == null) {
                    System.out.println(name + " infinity");
                } else {
                    System.out.println(name + " "+ result.get(name));
                }
            }
        }
    }

    private static Map<String,Integer> bfs(Map<String, Set<String>> graph) {
        Map<String, Integer> result = new HashMap<>();
        result.put("Erdos, P.", 0);

        Queue<String> queue = new LinkedList<>();
        queue.offer("Erdos, P.");
        int edrosNumber = 0;

        Set<String> visited = new HashSet<>();

        while (!queue.isEmpty()) {
            edrosNumber++;
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String head = queue.poll();
                visited.add(head);
                if (graph.get(head) == null) {
                    break;
                }

                for (String neighbor : graph.get(head)) {
                    if (result.containsKey((neighbor))) {
                        continue;
                    } else {
                        queue.offer(neighbor);
                        result.put(neighbor, edrosNumber);
                    }
                }
            }
        }
        return result;
    }

    private static void initialGraph(Map<String, Set<String>> graph,
                                     String[] papers) {
        // add other's names to its Set
        for (String author : papers) {
            if (!graph.containsKey(author)) {
                graph.put(author, new HashSet<String>());
            }
        }

        for (int i = 0; i < papers.length; i++) {
            for (int j = 0; j < papers.length; j++) {
                if (i != j) {
                    graph.get(papers[i]).add(papers[j]);
                }
            }
        }
    }
}
