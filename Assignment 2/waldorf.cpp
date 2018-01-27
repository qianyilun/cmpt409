
/* Created by Peter Tan  @peterjtan
 * Date: 2018-01-26
 */

#include <algorithm>
#include <iostream>
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

    vector<int> GetSuffixArray() const { return P.back(); }
};


// ----------

int main() {

	string row;
	getline(cin, row);
	int totalCase = row[0] - '0';

	for (int caseNum = 0; caseNum < totalCase; ++caseNum) {

		getline(cin, row);  // Removed the empty line at the beginning of each case
		getline(cin, row);

		int rowNum = row[0] - '0'; // Processing data matrix dimension: eg. 8 11
		vector<vector<char>> data;

		for (int i = 0; i < rowNum; ++i) { // Reading data matrix
			getline(cin, row);
			data.push_back( vector<char>(row.begin(), row.end()) );
		}

		getline(cin, row);
		int testWordNum = row[0] - '0';

		vector<SuffixArray> testWords;
		for (int i = 0; i < testWordNum; ++i) {
			getline(cin, row);
			testWords.push_back(SuffixArray(row));
		}

		for (const auto& i : testWords) {
            vector<int> SA = i.GetSuffixArray();
			cout << SA << endl;
		}
	}


	return 0;
}