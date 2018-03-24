// uva p1314
// Suffix array construction code is copied from stanford codebook
// Author: Andy Zhang - hiandyzhang@outlook.com

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

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
      for (int i = 0; i < L; i++){M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);}
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++){P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;}
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

//return hidden password for an suffix array
int hiddenPassword(SuffixArray suffix){
		vector<pair<int,int>> sorted_v_pair;
		vector<int> v = suffix.GetSuffixArray();
		for (int i = 0; i < suffix.L;i++){
			// ex. i=>0123456,  v[i]=>0516234,  sorted_v_pair=> <0,0><1,2><2,4><3,5><4,6><5,1><6,3>
			sorted_v_pair.push_back(make_pair(v[i],i));
		}
		sort(sorted_v_pair.begin(), sorted_v_pair.end(), [](pair<int, int> p1, pair<int, int> p2){return p1.first < p2.first;});
		for (int i = 0; i< suffix.L;i++){
			// ex. looping i = 0123456, sorted_v_pair.second = 0245613
			int index = sorted_v_pair[i].second;//index in string
			if (i+1 ==suffix.L){
				if (index > suffix.L/2-1){return index-suffix.L/2;}
				else{return index;}
			}
			int next_index = sorted_v_pair[i+1].second;//next sorted array's starting index in string
			if (index< suffix.L/2+1){
				if (next_index < suffix.L/2+1 && suffix.s.substr(index,suffix.L/2) == suffix.s.substr(next_index,suffix.L/2)){
					continue;
				}
				else{
					// if (index > suffix.L/2-1){return index-suffix.L/2;}
					// else{return index;}
					return index;
				}
			}
		}
		exit(0);
};

int main() {
	// string ln;
	// getline(cin,ln);
	// // int lineNumber = ln - "0";
	// int lineNumber = stoi(ln);
	// if (lineNumber<5 || lineNumber>100000){exit(0);}
	// //cout << "lineNumber" << lineNumber;
	// for (int j = 0 ; j < lineNumber; j++){
	// 	string str;
	// 	getline(cin, str);
	// 	//cout << "str = "<< str;
	// 	stringstream ss(str);
	// 	string substr;
	// 	getline(ss,substr,' ');
	// 	getline(ss,substr,' ');

	// 	substr = substr + substr;
	// 	SuffixArray suffix(substr);
	// 	cout << hiddenPassword(suffix) << "\n";
	// }

	// there is string size limit in getline() for uva's judge
	int t; cin >> t;
	for (int i = 0 ; i < t; i++){
		string str;
		int n;
		cin >> n >> str;
		str = str + str;
		SuffixArray suffix(str);
		cout << hiddenPassword(suffix) << endl;
	}
};

