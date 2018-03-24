#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
//map<pair<string, string>>
const int MAXN = 201;
const int INF = 0x3f3f3f3f;
int n,m, cost[MAXN];
int dp[MAXN][MAXN];
bool root[MAXN];
map<string, int> c2id;// map country name to id
vector<int> input[MAXN];
int dfs(int u){
    memset(dp, 0x3f,sizeof(dp));// set all entries to INF
    // for(int i = 1; i <= n; i ++)
    //     dp[u][i] = INF;
    dp[u][0] = 0;
    int child = 1;
    for(int i = 0; i < input[u].size(); i++) {
        int v = input[u][i];
        child += dfs(v);
        for(int j = n; j >= 0; j --) {
            for(int k = 0; k <= j; k ++) {
                dp[u][j] = min(dp[u][j], dp[u][j-k]+dp[v][k]);
            }
        }
    }
    dp[u][child] = min(dp[u][child], cost[u]);
    return child;
}
int main(){
  while (cin.peek() != EOF) {
    scanf("%d %d\n", &n, &m);
    //cout <<  "n = "<<to_string(n)<<endl;
    // clear c2id and input for each test case
    c2id.clear();
    for(int i = 0; i <= n; i ++)
      input[i].clear();
    int countryId = 1;
    memset(root, 1, sizeof(root));

    // start reading test case
    for (int i = 1; i <= n+1 ; i++){
      string line, element;
      getline(cin, line);
      if (line == "#"){
        continue;
      }
      //cout << "Reading line"<<to_string(countryId)<<" : "<<line<< endl;
      stringstream ss(line);
      // a counter for each line
      // count = 1 -> Root country
      // count = 2 -> cost
      int count = 1;
      int rootId;
      while (getline(ss, element, ' ')) {
        if (count == 1){// root node
          if(c2id.find(element) == c2id.end()){
            c2id[element] = countryId++;
            rootId = c2id.find(element)->second;
            count +=1;
            continue;
          }
        }
        else if (count ==2){// # of diamonds
          int diamond = stoi(element);
          cost[rootId] = diamond;
          count +=1;
          continue;
        }
        if(c2id.find(element) == c2id.end())
          c2id[element] = countryId++;
        int v = c2id.find(element)->second;
        root[v] = false;
        input[rootId].push_back(v);
        //cout << element<< endl;
        count +=1;
      }
    }
    for(int i = 1; i <= n; i ++){
      if(root[i]){
          input[0].push_back(i);
        }
    }

    cost[0] = INF;
    // DFS to fill tree
    dfs(0);
    // get result
    int result = INF;
    for (int i = m; i<=n;i++){
      result=min(result,dp[0][i]);
    }
    //cout << "Result!!!!!!!!"<<result << endl;
    cout << result << endl;
  }
}
