import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Graph {
    private int max_v; // # of vertices
    int result = 0;
    ArrayList<Integer>[] adjList;
    List<List<Integer>> pathsResultList;

    public Graph(int vertices) {
        this.max_v = vertices;
        adjList = new ArrayList[max_v];

        for (int i = 0; i < vertices; ++i) {
            adjList[i] = new ArrayList<>();
        }
        
        pathsResultList = new ArrayList<>();
    }

    public void addEdge(int u, int v) {
        adjList[u].add(v);
        adjList[v].add(u);
    }

    // Prints all paths from
    // 's' to 'd'
    public void printAllPaths(int s, int d) 
    {
        boolean[] isVisited = new boolean[max_v];
        ArrayList<Integer> pathList = new ArrayList<>();
         
        //add source to path[]
        pathList.add(s);
         
        //Call recursive utility
        constructAllPathsUtil(s, d, isVisited, pathList);
        
//        Collections.sort(pathsResultList, new Comparator<List<Integer>>() {
//        	@Override
//        	public int compare(List<Integer> a, List<Integer> b) {
//        		
//        	}
//		});
        
        
        for (List<Integer> path : pathsResultList) {
        	StringBuilder sb = new StringBuilder();
        	for (int v : path) {
        		sb.append(v);
        		sb.append(" ");
        	}
        	System.out.println(sb.toString().trim());
        }
    }
    
    

    private void constructAllPathsUtil(Integer u, Integer d, boolean[] isVisited, List<Integer> localPathList) {
         
        // Mark the current node
        isVisited[u] = true;
         
        if (u.equals(d)) {
        	result++;
            pathsResultList.add(new ArrayList<Integer>(localPathList));
        }
         
        // Recur for all the vertices
        // adjacent to current vertex
        for (Integer i : adjList[u]) 
        {
            if (!isVisited[i])
            {
                // store current node 
                localPathList.add(i);
                constructAllPathsUtil(i, d, isVisited, localPathList);
                 
                // remove current node
                localPathList.remove(i);
            }
        }
         
        // Mark the current node
        isVisited[u] = false;
    }
    
    public boolean IsConnected(int dest) {
    	Queue<Integer> q = new LinkedList<>();
    	
    	boolean[] isVisited = new boolean[max_v + 1];
    	
    	isVisited[1] = true;
    	q.add(1);
    	
    	while (!q.isEmpty()) {
    		int front = q.poll();
    		if (front == dest) {
    			return true;
    		}
    		
    		for (int i = 0; i < adjList[front].size(); ++i) {
    			int elem = adjList[front].get(i);
    			if ( !isVisited[elem] ) {
    				isVisited[elem] = true;
    				q.add(elem);
    			}
    		}
    	}
    	return false;
    }

}


public class P208 {

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String line;
        
        int cases = 0;
        while (true) {
        	try {
        		cases++;
        		int dest = Integer.parseInt(br.readLine());
        		Graph g = new Graph(21);
		        while ((line = br.readLine()) != null) {
		        	if (line.equals("0 0")) {
		        		break;
		        	}
		        	String[] line_split = line.split(" ");
		        	g.addEdge(Integer.parseInt(line_split[0]), Integer.parseInt(line_split[1]));
		        }
		        
		        for (List<Integer> l : g.adjList) {
		        	Collections.sort(l);
		        }
		        
		        System.out.printf("CASE %d:\n", cases);
		        if (g.IsConnected(dest)) {
		        	g.printAllPaths(1, dest);
		        }
		        
		        System.out.printf("There are %d routes from the firestation to streetcorner %d.\n", g.result, dest);
        	
        	} catch(Exception e) {
//        		e.printStackTrace();
        		System.exit(0);
        	}
        }
    }
}