#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define MAX_INT 99999
#define MAX_K 1001
#define MAX_N 5001
// void printTable(int M[5001][1001]){
//   // for (int* element : M) {
//   //   cout << *element;
//   // }//print out memo table
//   cout << "diao";
// }
int main(){
  int T ,K, N;
  int chopsticks[MAX_N];
  // scanf("%d",&T);
  cin>>T;
  //while (T--){
  for (int j = 0; j < T; j++){
    // scanf("%d %d", &K, &N);
    cin>>K;
    cin>>N;
    K+=8;
    // cout << "N:" << N << endl;
    // cout << "K:" << K << endl;
    // read all chopsticks' length into an array
    // cout<<"chopsticks:";
    for (int chopstick = N; chopstick > 0; chopstick--){
        // scanf("%d", &chopsticks[chopstick]);
        cin >> chopsticks[chopstick];
        // cout<<chopsticks[chopstick]<<" ";
    }
    // cout << endl;
    // int M[MAX_N][MAX_K];


    int M[N+1][K+1];
    //memset(M,MAX_INT, sizeof M); //More than a byte, can't use memset
    //print out memo table

    // first column (people 0) are all zero
    for (int i = 0; i<N+1;i++){
      M[i][0] = 0;
    }
    for (int i = 0; i<K+1;i++){
      M[0][i] = MAX_INT;
    }
    for (int people = 1; people <=K; people++){
      for (int chop = 1; chop <=N; chop++){
        // Don't take chop => M[chop][people] = M[chop-1][people]
        // Take chop => take chop & chop -1 =>
        // M[chop][people] = M[chop-2][people] + badness(chop -1, chop)
        if ( people*3 > chop){
          M[chop][people] = MAX_INT;
          continue; // Have to satisfy chop >= people*3
        }

        M[chop][people] = min(M[chop-1][people], M[chop-2][people-1]+(int)pow(chopsticks[chop]-chopsticks[chop-1],2));
        // cout << "M[chop-1][people]"<<M[chop-1][people]<<endl;
        // cout << "M[chop-2][people-1]"<<M[chop-2][people-1]<<endl;
        // cout << "(chopsticks[chop]-chopsticks[chop-1])^2"<<to_string((int)pow(chopsticks[chop]-chopsticks[chop-1],2))<<endl;
        // cout << "Updating ("<<chop<<","<<people<<") to"<<M[chop][people]<<endl;
      }
    }
    //printTable(M);
    // cout <<"Answer:"<< M[N-2][K]<< endl;// TODO how to solve this
    cout << M[N][K]<<endl;

  }
  return 0;
}
