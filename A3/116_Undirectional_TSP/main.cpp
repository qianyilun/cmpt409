
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

pair<int, vector<int>> handle_memoization(int new_row, int new_col);



template<class T>
ostream& operator <<(ostream& os, vector<T> v) {
    os << "[ ";
    for (auto i = v.begin(); i != v.end(); ++i) {
        os << *i;
        if (i != v.end() - 1) {
            os << ", ";
        }
    }
    os << " ]";
    return os;
}

static int row, col;
static vector<vector<int>> data;

// Key: the coordinate (x, y) of grid data
// Value: stores the total weight starting from (x, y) to the right, and the corresponding path in vector<int>
static map< pair<int, int>, pair<int, vector<int>> >  memoization;


pair<int, vector<int>> get_min(int r, int c) {
    if (c < 0) {
        return make_pair(0, vector<int> {});
    } else {
        int new_row_east = r;
        int new_row_northeast = (r - 1 < 0) ? row - 1 : r - 1;
        int new_row_southeast = (r + 1 >= row) ? 0 : r + 1;

        int new_col = c - 1;

        vector<pair<int, vector<int>>> result;
        
        result.push_back( handle_memoization(new_row_northeast, new_col) );
        result.push_back( handle_memoization(new_row_east, new_col) );
        result.push_back( handle_memoization(new_row_southeast, new_col) );

        auto min_it = min_element(result.begin(), result.end());

        vector<int> second = min_it->second;
        second.push_back(r);
        return make_pair(data[r][c] + min_it->first, second);


        // char buffer[512];
        // sprintf(buffer, "c = %d,   r = %d, weight = %d\n", new_col, new_row_northeast, northeast);
        // sprintf(buffer + strlen(buffer), "\t r = %d, weight = %d\n", new_row_east, east);
        // sprintf(buffer + strlen(buffer), "\t r = %d, weight = %d\n", new_row_southeast, southeast);
        // sprintf(buffer + strlen(buffer), "Return data[%d][%d]: %d + %d", r, c, data[r][c], min({ northeast, east, southeast }));

        // cout << buffer << endl;

        // return data[r][c] + min_it->first;
    }
}

pair<int, vector<int>> handle_memoization(int new_row, int new_col) {
    if (memoization.find(make_pair(new_row, new_col)) == memoization.end()) {
        auto p = get_min(new_row, new_col);
        memoization[make_pair(new_row, new_col)] = p;
        return p;
    } else {
        return memoization[make_pair(new_row, new_col)];
    }
}


int main()
{
    while (cin.peek() != EOF) {
        scanf("%d %d\n", &row, &col);

        // Handling input
        for (int i = 0; i < row; ++i) {
            data.push_back(vector<int>(col));
        }

        string line, token;
        int i = 0, j = 0;
        while (i < row) {
            getline(cin, line);
            stringstream ss(line);

            while (getline(ss, token, ' ')) {
                data[i][j] = stoi(token);
                ++j;
                if (j >= col) {
                    ++i;
                    j = 0;
                }
            }
        }

        vector<pair<int, vector<int>>> result;
        for (int i = 0; i < row; ++i) {
            result.push_back( get_min(i, col - 1) );
        }

        int value;
        vector<int> path;
        tie(value, path) = *min_element(result.begin(), result.end());

        for (auto i = path.begin(); i != path.end(); ++i) {
            cout << *i + 1;
            if (i != path.end() - 1) {
                cout << " ";
            } else {
                cout << endl;
            }
        }

        cout << value << endl;

        data.clear();
        memoization.clear();
    }

    return 0;
}