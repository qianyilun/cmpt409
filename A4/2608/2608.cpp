// 16:28
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool validPerm(int* clock, int n, int maxSum){
  if (clock[n-1]+clock[n]+ clock[1] > maxSum){
    return false;
  }
  for (int i = 1; i <=n-2){
      if (clock[i]+clock[i+1]+clock[i+2] > maxSum){
        return false;
      }
  }
  return true;
}


int dfs(int* clock, int* isVisited, int n, int maxSum, int total){
  for (int i = 1 ; i <= n ; i++ ){
    if (!isVisited[i]){
      isVisited[i] = 1;
      total = dfs(clock,isVisited,n,maxSum,total);
      isVisited[i] = 0;
    }
  }
  if (validPerm(clock, n, maxSum)){
    return total+1; // increment counter if permutation <is valid
  }
  else{
    return total;
  }
}

int perm(int n, int maxSum){
  // build array
  int clock[n+1];
  int isVisited[n+1];
  int total =0;
  memset(isVisited,0,sizeof isVisited);
  // DFS
  // Fix 1 on top of clock, fix three elements on the top
  clock[1] = 1;
  isVisited[1] = 1;
  // clock[1] = 1 < clock[n]< clock[2]
  for (int i = 2; i <= n-1; i++){//clock[n]
    clock[n] = i;
    for (int j = i+1; j <=n;j++){//clock[2]
      clock[2] = j;
      if (i + j +1 < maxSum){
        isVisited[i] = 1;
        isVisited[j] = 1;
        total = total + dfs(clock,isVisited,n,maxSum,0);
      }
    }
  }
  return total;
}

int main(){
  int t;
  cin >> t; // Read the first number
  for (int i = 0 ; i < t; i++){
    int n,maxSum;
    cin >> n >> maxSum; // This syntax would skip the space in the line
    int p = perm(n, maxSum);
    cout <<"Permutation size:    " << n<<endl;
    cout <<"Maximum triplet sum: " << maxSum<<endl;
    cout <<"Valid permutations:  " << p<<endl;
  }
}
