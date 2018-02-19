using namespace std;
int main(){
  int T,K, N;
  int chopsticks[320001];
  scanf("%d",&T);
  while (T--){
    scanf("%d %d", &K, &N);
    chopsticks[N+1];
    // read all chopsticks' length into an array
    for (int chopstick = 1; chopstick <= N; chopstciks++){
        scanf("%d", &chopsticks[chopstick]);
    }
    int memo[N+1][K+8+1];
    //memset(memo, 0, sizeof memo); More than a byte, can't use memset
    //for (int element : memo) cout << element;//print out memo table
    for (int people = 1; people <=K+8; people++){
      for (int chop = 1; chop <=N; chop++){
        // Don't take chop => M[chop][people] = M[chop-1][people]
        // Take chop => take chop & chop -1 =>
        // M[chop][people] = M[chop-2][people] + badness(chop -1, chop)
        M[chop][people] = min(M[chop-1][people], );
      }
    }
  }
}
