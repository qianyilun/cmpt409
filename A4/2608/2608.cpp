// 16:28
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
// build array
int n, maxSum, total;
int c[14];
bool isVisited[14];

void Dfs(int current){
  if (current == n){
    if (c[current]+c[current-1]+ c[current-2] <= maxSum){
      total = total + 1;// last triplet => this permutation is good
    }
    return;
  }
  for (int i = 2 ; i <= n ; i++ ){ // check all triplets
    if (!isVisited[i]){
        if (i +c[current-1]+ c[current-2] <= maxSum){
          isVisited[i] = true;
          c[current] = i;
          Dfs(current+1);
          isVisited[i] = false;
      }
      
    }
  }
}

void perm(){
  memset(isVisited,false,sizeof isVisited);
  // DFS
  // Fix 1 on top of c, fix three elements on the top
  total = 0;
  c[1] = 1;
  isVisited[1] = true;
  // c[1] = 1 < c[n]< c[2]
  for (int i = 2; i <= n-1; i++){//c[n]
    for (int j = i+1; j <=n;j++){//c[2]
      if (i + j +1 <= maxSum){
        c[n] = i;
        c[2] = j;
        isVisited[i] = true;
        isVisited[j] = true;
        Dfs(3);
        isVisited[i] = false;
        isVisited[j] = false;
      }
    }
  }
}

int main(){
  int t;
  cin >> t; // Read the first number
  for (int i = 0 ; i < t; i++){
    cin >> n >> maxSum; // This syntax would skip the space in the line
    perm();
    cout <<"Permutation size:    " << n<<endl;
    cout <<"Maximum triplet sum: " << maxSum<<endl;
    cout <<"Valid permutations:  " << total<<endl;
    if (i < t -1)
      cout << endl;
  }
  return 0;
}
