#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

struct SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;

  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++) 
	    M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++) 
	    P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
    }    
  }

  vector<int> GetSuffixArray() { return P.back(); }

  // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
	i += 1 << k;
	j += 1 << k;
	len += 1 << k;
      }
    }
    return len;
  }
};

vector<int> v;

int rank[1004], height[1004]; 
void getHeight(int n) {
    char s[] = "abcdefg.bcdefgh";  
    int i, j, k = 0;  
    for(i = 0; i < n; i++) rank[v[i]] = i;  
    for(i = 0; i < n; i++) {  
        if(k) k--;  
        int j = v[rank[i]-1];  
        while(s[i+k] == s[j+k]) k++;  
        height[rank[i]] = k; 
        cout << height [rank[i]];
    }  
} 

int ta[110005], h[110005];

void build_h(char* str) {
    int i, j, k;
    for(i = 0; i < 15; i++)  ta[v[i]] = i;
    for(i = 0; i < 15; i++) {
        if(ta[i] == 0) {
            h[ta[i]] = 0;
            continue;
        }
        if(i == 0 || h[v[i-1]] <= 1)
            k = 0;
        else
            k = h[ta[i-1]]-1;
        while(str[v[ta[i]-1]+k] == str[v[ta[i]]+k])
            k++;
        h[ta[i]] = k;
    }

    for (int i = 0; i < 15; i++) {
        cout << h[i] << " "; 
    }
} 



string strg;
int main() {
    int split1 = 7;
    int split2 = 15;
    strg = "abcdefg.bcdefgh";

    int n = strg.length(); 
     
    // declaring character array
    char s[n+1]; 
     
    // copying the contents of the 
    // string to char array
    strcpy(s, strg.c_str()); 

    SuffixArray suffix(s);
    v = suffix.GetSuffixArray();

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
        
        printf("%.*s\n", 15, s + i);
        
    }

    // build_h(s);

    getHeight(15);
    

    // cout<< suffix.LongestCommonPrefix(split1+1, split2+1);
}

