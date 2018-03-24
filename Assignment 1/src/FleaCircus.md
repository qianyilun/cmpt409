##Set up

It was written in **C++ 5.3**. Run by command

```g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE FleaCircus.cpp```

## Algorithm overview

1. Build a graph
2. DFS to get the path between two nodes
3. If the path length is even number, they meet. If not, they jump forever.

## Implementation detail

### Graph

Graph is implemented by an array of vector.

Each element in the array represents one node. Each element in vector represents the connected nodes. 

ex. a is connected with b,c,d, then g[a] is a vector has b, c, d

### DFS

DFS(start, end, parent), which call itself recursion.

The para parent is to prevent it search back.

### Path

ex. two nodes are 8,1

If we get path 854 - (1), where length = 3, then they jump forever between 5 and 4.

If we get path 8542 - (1), where length = 4, then they meet at 4.

