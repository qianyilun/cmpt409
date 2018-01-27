
/* Created by Peter Tan  @peterjtan
 * Date: 2018-01-26
 */

#include <algorithm>
#include <cctype>  // std::tolower
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


template<class T>
T toLowercase(T str) {
    transform(str.begin(), str.end(), str.begin(), 
        [](unsigned char c) { return tolower(c); }
    );
    return str;
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

        // Processing data matrix dimension: eg. 8 11
        int rowNum = stoi( row.substr(0, row.find_first_of(' ')) ), 
            colNum = stoi( row.substr(row.find_first_of(' ') + 1, string::npos) );
        // cout << rowNum << " " << colNum;
        vector<vector<char>> data;

        for (int i = 0; i < rowNum; ++i) { // Reading data matrix
            getline(cin, row);
            data.push_back( toLowercase(vector<char>(row.begin(), row.end())) );
        }

        cout << data << endl;


        getline(cin, row);
        int testWordNum = row[0] - '0';

        vector<SuffixArray> testWords;
        for (int i = 0; i < testWordNum; ++i) {
            getline(cin, row);
            testWords.push_back(SuffixArray( toLowercase(row) ));
        }


        // For each test word, loop through each element in data matrix to find a match
        for (const auto& word : testWords) {
            vector<int> wordSA = word.GetSuffixArray();
            
            for (int r = 0; r < rowNum; ++r) {
                for (int c = 0; c < colNum; ++c) {

                    cout << "r = " << r << ", c = " << c << endl;

                    string horizontal_right = "", horizontal_left = "";
                    for (int i = c; i < colNum; ++i)
                        horizontal_right += data[r][i];

                    for (int i = c; i >= 0; --i)
                        horizontal_left += data[r][i]; 

                    string vertical_up = "", vertical_down = "";
                    for (int i = r; i >= 0; --i)
                        vertical_up += data[i][c];

                    for (int i = r; i < rowNum; ++i)
                        vertical_down += data[i][c];

                    string diagonal_up = "", diagonal_down = "";
                    for (int i = r, j = c; i >=0 && j >= 0; --i, --j)
                        diagonal_up += data[i][j];

                    for (int i = r, j = c; i < rowNum && j < colNum; ++i, ++j)
                        diagonal_down += data[i][j];

                    // cout << "horizontal_left = " << horizontal_left << ", horizontal_right = " << horizontal_right << endl
                    //      << "vertical_up = " << vertical_up << ", vertical_down = " << vertical_down << endl
                    //      << "diagonal_up = " << diagonal_up << ", diagonal_down = " << diagonal_down << endl << endl;

                }
            }
        }
    

    }


    return 0;
}