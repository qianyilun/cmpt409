
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
        // cout << endl;
        vector<int> sa = GetSuffixArray();
        
        // For binary search, ind[0]: left index, ind[1]: right index
        vector<int> ind = { 0, (int) P.back().size() - 1 };
        
        while (ind[0] + 1 < ind[1]) {
            int mid = (ind[0] + ind[1]) / 2;
            int str_ind = sa[mid];

            string suffix = s.substr(str_ind, string::npos);
            string word = suffix.substr(0, suffix.find_first_of('.'));

            // cout << "mid: " << mid << ", begin: " << ind[0] << ", end: " << ind[1] << endl;
            // cout << "input: " << input << " word: " << word << endl;

            if (word == "") {
                ind[0] = mid;
            } else if (input == word) {
                succeeded_word = input;
                return true;
            } else if (input < word) {
                ind[1] = mid;
            } else if (input > word) {
                ind[0] = mid;
            }
        }

        // left ind and right ind are adjacent now. Need to check whether the 
        // 2 strings pointed by left/right ind consist of what we are looking for.
        vector<string> words;
        for (int i = ind[0]; i <= ind[1]; ++i) {
            int str_ind = sa[i];

            string suffix = s.substr(str_ind, string::npos);
            string word = suffix.substr(0, suffix.find_first_of('.'));
            words.push_back(word);
        }
        sort(words.begin(), words.end(), greater<string>());

        // cout << "words: " << words << endl;

        for (const auto& i : words) {
            if (input.substr(0, i.length()) == i) {
                // cout << "trimmed: " << input.substr(0, i.length()) << " word: " << i << endl;
                succeeded_word = input.substr(0, i.length());
                return true;
            }
        }

        return false;
    }

};


void record_result(int r, int c, map<string, string>& result_map, const string& succeeded_word) {
    stringstream ss;
    ss << r + 1 << " " << c + 1;
    // cout << "Found: " << r + 1 << " " << c + 1 << endl;

    // Processing outputs
    if (result_map[succeeded_word] == "") {
        result_map[succeeded_word] = ss.str();
    }
}


// ----------

int main() {

    string row;
    getline(cin, row);
    int totalCase = stoi(row);

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


        getline(cin, row);
        int testWordNum = stoi(row);

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
        // cout << sa.s << endl;
        // cout << sa.GetSuffixArray() << endl;
        map<string, string> result_map;


        // Loop through each element in data matrix and do binary search in suffix array to find a match
            
        for (int r = 0; r < rowNum; ++r) {
            for (int c = 0; c < colNum; ++c) {

                // cout << "r = " << r << ", c = " << c << endl;

                string current_ch = ""; current_ch += data[r][c];
                if (testWord_str.find("." + current_ch + ".") != string::npos) {
                    record_result(r, c, result_map, current_ch);
                }

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

                string diagonal_leftup = "", diagonal_rightdown = "";
                for (int i = r, j = c; i >=0 && j >= 0; --i, --j)
                    diagonal_leftup += data[i][j];

                for (int i = r, j = c; i < rowNum && j < colNum; ++i, ++j)
                    diagonal_rightdown += data[i][j];

                string diagonal_rightup = "", diagonal_leftdown = "";
                for (int i = r, j = c; i >=0 && j < colNum; --i, ++j)
                    diagonal_rightup += data[i][j];

                for (int i = r, j = c; i < rowNum && j >= 0; ++i, --j)
                    diagonal_leftdown += data[i][j];

                // cout << "horizontal_left = " << horizontal_left << ", horizontal_right = " << horizontal_right << endl
                //      << "vertical_up = " << vertical_up << ", vertical_down = " << vertical_down << endl
                //      << "diagonal_leftup = " << diagonal_leftup << ", diagonal_rightdown = " << diagonal_rightdown << endl 
                //      << "diagonal_rightup = " << diagonal_rightup << ", diagonal_leftdown = " << diagonal_leftdown << endl 
                //      << endl;
                
                string succeeded_word = "";
                if (sa.is_exact_match(horizontal_right, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(horizontal_left, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(vertical_down, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(vertical_up, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(diagonal_rightdown, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(diagonal_leftup, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(diagonal_leftdown, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);
                
                if (sa.is_exact_match(diagonal_rightup, succeeded_word) && !result_map.count(succeeded_word))
                    record_result(r, c, result_map, succeeded_word);

            }
        }

        // cout << "result: " << endl;
        for (const auto& i : testWord_vector) {
            // cout << i << " " << result_map[i] << endl;
            cout << result_map[i] << endl;
        }


        if (caseNum + 1 < totalCase) {
            cout << endl;
        }

    
    }


    return 0;
}