
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

int get_min(int r, int c) {
    if (c == col - 1) {
        return data[r][c];
    } else if (c > col - 1) {
        return 0;
    } else {
        int new_row_east = r;
        int new_row_northeast = (r - 1 < 0) ? row - 1 : r - 1;
        int new_row_southeast = (r + 1 >= row) ? 0 : r + 1;

        int new_col = c + 1;

        int east = get_min(new_row_east, new_col);
        int northeast = get_min(new_row_northeast, new_col);
        int southeast = get_min(new_row_southeast, new_col);

        // char buffer[512];
        // sprintf(buffer, "c = %d,   r = %d, weight = %d\n", new_col, new_row_northeast, northeast);
        // sprintf(buffer + strlen(buffer), "\t r = %d, weight = %d\n", new_row_east, east);
        // sprintf(buffer + strlen(buffer), "\t r = %d, weight = %d\n", new_row_southeast, southeast);
        // sprintf(buffer + strlen(buffer), "Return data[%d][%d]: %d + %d", r, c, data[r][c], min({ northeast, east, southeast }));

        // cout << buffer << endl;

        return data[r][c] + min({ northeast, east, southeast });
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
        for (int i = 0; i < row; ++i) {
            getline(cin, line);
            stringstream ss(line);

            for (int j = 0; j < col; ++j) {
                getline(ss, token, ' ');
                data[i][j] = stoi(token);
            }
        }

        vector<int> result;
        for (int i = 0; i < row; ++i) {
            result.push_back( get_min(i, 0) );
        }

        cout << *min_element(result.begin(), result.end()) << endl;

    }

    return 0;
}