
/* Created by Peter Tan  @peterjtan
 * Date: 2018-01-29
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;


template<class T>
ostream& operator <<(ostream& os, const vector<T>& v) {
    os << "[ ";
    for (const auto& i : v) {
        os << i << ' ';
    }
    os << " ]" << endl;
    return os;
}

template<class T1, class T2>
ostream& operator <<(ostream& os, const set<T1, T2>& v) {
    os << "[ ";
    for (const auto& i : v) {
        os << i << ' ';
    }
    os << " ]" << endl;
    return os;
}


/*
 * SuffixArray related functions are adapted from Stanford ACM codebook
 */
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



// ----------

int main() {

    string row;
    getline(cin, row);
    int totalCase = stoi(row);

    for (int caseNum = 0; caseNum < totalCase; ++caseNum) {

        getline(cin, row);

        SuffixArray sa(row);

        auto sort_set = [](const string& s1, const string& s2) {
            if (s1.length() == s2.length()) {
                return s1 < s2;
            } else {
                return s1.length() > s2.length();
            }
        };
        set<string, decltype(sort_set)> repeated_str_set(sort_set);

        
        for (unsigned int i = 0; i < row.length(); ++i)
            for (unsigned int j = i + 1; j < row.length(); ++j) {
                int lcp = sa.LongestCommonPrefix(i, j);
                // cout << lcp << endl;
                if (lcp != 0) {
                    string prefix = row.substr(i, lcp);
                    repeated_str_set.insert(prefix);
                }
            }
        // cout << repeated_str_set << endl;

        bool printed = false;
        for (const auto& str : repeated_str_set) {
            // cout << str << endl;
            int str_pos = -1, how_many = 0;
            do {
                // cout << str_pos << endl;
                str_pos = row.find(str, str_pos + 1);
                if (str_pos != string::npos && str_pos != -1) 
                    how_many++;
            } while (str_pos != string::npos);

            if (how_many >= 2) {
                cout << str  << " " << how_many << endl;
                printed = true;
                break;
            }
        }
        if (!printed)
            cout << "No repetitions found!" << endl;
    
    }


    return 0;
}