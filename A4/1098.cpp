#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

template<class P1, class P2>
ostream& operator <<(ostream& os, const pair<P1, P2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<class T>
ostream& operator <<(ostream& os, const vector<T>& v) {
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

int row, col;

void recurse(pair<int, int> start, bitset<64>& visited, vector<pair<int, int>>& path) {
    int x = start.first;
    int y = start.second;

    visited[8 * x + y] = true;
    if (x + 1 < row && !visited[8 * (x + 1) + y]) { // Checking right tile
        auto newpath = path;
        newpath.push_back(start); // Add current tile to the path
        recurse( make_pair(x + 1, y), visited, newpath );
    }
    if (x - 1 >= 0 && !visited[8 * (x - 1) + y]) { // Checking left tile
        auto newpath = path;
        newpath.push_back(start); // Add current tile to the path
        recurse( make_pair(x - 1, y), visited, newpath );
    }
    if (y + 1 < col && !visited[8 * x + y + 1]) { // Checking top tile
        auto newpath = path;
        newpath.push_back(start); // Add current tile to the path
        recurse( make_pair(x, y + 1), visited, newpath );
    }
    if (y - 1 >= 0 && !visited[8 * x + y - 1]) { // Checking bottom tile
        auto newpath = path;
        newpath.push_back(start); // Add current tile to the path
        recurse( make_pair(x, y + 1), visited, newpath );
    }

    // cout << path.back() << endl;
    if (path.size() > 0 && path.back() == make_pair(0, 1)) {
        cout << path << endl;
    }
    
}

int main() {
    pair<int, int> p1, p2, p3;

    bitset<64> visited(0);

    while (cin.peek() != EOF) {
        scanf("%d %d\n", &row, &col);
        if (row == 0 && col == 0) {
            break;
        }

        int x1, y1, x2, y2, x3, y3;
        scanf("%d %d %d %d %d %d\n", &x1, &y1, &x2, &y2, &x3, &y3);
        
        p1 = make_pair(x1, y1);
        p2 = make_pair(x2, y2);
        p3 = make_pair(x3, y3);

        vector<pair<int, int>> path;
        recurse(make_pair(0, 0), visited, path);
    }
    return 0;
}