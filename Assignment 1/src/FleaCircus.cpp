
// FleaCircus

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
const int N = 5000;
int position1, position2, path[N],pathCounter;
vector<int> g[N];
bool dfs(int x, int y,int parent){
  /**
  depth first search that starts with x and terminate at y
  **/

  path[pathCounter++] = x;
  if (x == y) return true;
  for (int i = 0; i < g[x].size(); i++){
    int current = g[x][i]; // go through every connected node

    //if two nodes are connected, they are connecter two ways, so skip one of them
    if (parent == current) continue;
    if (dfs(current,y, x)) return true;
  }
  //Two nodes are not connected, move back path counter return false
  pathCounter--;
  return false;
}
int main(){
  int n;
  // Problem says: "The input file contains multiple test cases"
  // So, while we are reading the input, we can test when we've run out of input
  while(cin >> n && n) {
      // start to read (n-1) line of connectivity information
      for(int i = 1; i <= n; i++){
        g[i].clear();
      }
      for(int i = 1; i < n; i++) {
          int a, b;
          cin >> a >> b;
          g[a].push_back(b);
          g[b].push_back(a);
          // todo: a and b are connected, keep them somewhere
      }

      // in the (n+1)'th line we have the number of starting positions
      int l;
      cin >> l;

      // start to read l lines of pairs of positions
      for(int i = 1; i <= l; i++) {
        pathCounter = 0;
        cin >> position1 >> position2;
        // now you have connectivity information
        // and two positions
        // todo: implement your code to check to print appropriate message
        dfs(position1,position2,-1);
        if (pathCounter % 2) printf("The fleas meet at %d.\n", path[pathCounter / 2]);
        else {
          // jump forever
          int node1 = path[pathCounter / 2 - 1], node2 = path[pathCounter / 2];
          if (node1 > node2) swap(node1, node2);
          printf("The fleas jump forever between %d and %d.\n", node1, node2);
        }
      }
  }

  return 0;
}
