
/* Created by Peter Tan  @peterjtan
 * Date: 2018-01-26
 */

#include <algorithm>
#include <cctype>  // std::tolower
#include <iostream>
#include <map>
#include <sstream> // std::stringstream
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

    vector<int> sortedSA;

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

    vector<int> GetSuffixArray() { 
        if (sortedSA.size() == 0) {
            vector<pair<int, int>> temp;
            for (unsigned int i = 0; i < P.back().size(); ++i) {
                temp.push_back( make_pair(i, P.back()[i]) );
            }
            sort(temp.begin(), temp.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
                return p1.second < p2.second;
            });
            for (const auto& pair : temp) {
                sortedSA.push_back(pair.first);
            }
        }
        return sortedSA;
    }

    bool is_exact_match(string input, string& succeeded_word) {
        cout << endl;
        return binary_search(input, succeeded_word, 0, P.back().size() - 1);
    }

    bool binary_search(string input, string& succeeded_word, int begin, int end) {
        int mid = (begin + end) / 2;
        int str_ind = GetSuffixArray()[mid];
        // eg. waldorf.bam -> waldorf
        string suffix = s.substr(str_ind, string::npos);
        string word = suffix.substr(0, suffix.find_first_of('.'));
        string input_withSizeOfWord = input.substr(0, word.length());
        cout << "mid: " << mid << ", begin: " << begin << ", end: " << end << endl;
        cout << "input: " << input_withSizeOfWord << endl << "word: " << word << endl;
        
        // If found a match, make sure it is not a substring of the original word by
        // testing the whether ".word." is in the original string or not
        if ( input_withSizeOfWord == word ) {
            size_t pos = s.find("." + input_withSizeOfWord + ".");
            if (pos == string::npos) {
                return false;
            } else {
                succeeded_word = input_withSizeOfWord;
                return true;
            }
        } else if (input_withSizeOfWord < word && abs(begin - end) > 1) {
            return binary_search(input, succeeded_word, 0, mid);
        } else if (input_withSizeOfWord > word && abs(begin - end) > 1) {
            return binary_search(input, succeeded_word, mid + 1, end);
        } else {
            return false;
        }
    }


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
        cout << rowNum << " " << colNum;
        vector<vector<char>> data;

        for (int i = 0; i < rowNum; ++i) { // Reading data matrix
            getline(cin, row);
            data.push_back( toLowercase(vector<char>(row.begin(), row.end())) );
        }


        getline(cin, row);
        int testWordNum = row[0] - '0';

        // In order to output results in order as the test words are inputted, we need to use a vector to 
        // store the test word input order.
        vector<string> testWord_vector;
        string testWord_str = "";
        
        for (int i = 0; i < testWordNum; ++i) {
            getline(cin, row);
            testWord_str += "." + toLowercase(row);
            testWord_vector.push_back(toLowercase(row));
        }
        testWord_str += ".";

        SuffixArray sa(testWord_str);
        cout << sa.s << endl;
        cout << sa.GetSuffixArray() << endl;
        map<string, string> result_map;


        // Loop through each element in data matrix and do binary search in suffix array to find a match
            
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

                cout << "horizontal_left = " << horizontal_left << ", horizontal_right = " << horizontal_right << endl
                     << "vertical_up = " << vertical_up << ", vertical_down = " << vertical_down << endl
                     << "diagonal_up = " << diagonal_up << ", diagonal_down = " << diagonal_down << endl << endl;
                string succeeded_word = "";
                if (
                    sa.is_exact_match(horizontal_right, succeeded_word) ||
                    sa.is_exact_match(horizontal_left, succeeded_word) ||
                    sa.is_exact_match(vertical_down, succeeded_word) ||
                    sa.is_exact_match(vertical_up, succeeded_word) ||
                    sa.is_exact_match(diagonal_down, succeeded_word) ||
                    sa.is_exact_match(diagonal_up, succeeded_word)
                ) {
                    stringstream ss;
                    ss << r + 1 << " " << c + 1;

                    // Processing outputs
                    result_map[succeeded_word] = ss.str();
                }

            }
        }


        for (const auto& i : testWord_vector) {
            cout << result_map[i] << endl;
        }


        if (caseNum + 1 < totalCase) {
            cout << endl;
        }

    
    }


    return 0;
}