#include <cstdio>
#include <iostream>

int main() {

    int row, col;
    pair<int, int> p1, p2, p3;

    bool **visited;

    while (cin.peek() != EOF) {
        scanf("%d %d\n", &row, &col);
        int x1, y1, x2, y2, x3, y3;
        scanf("%d %d %d %d %d %d\n", &x1, &y1, &x2, &y2, &x3, &y3);
        p1 = make_pair(x1, y1);
        p2 = make_pair(x2, y2);
        p3 = make_pair(x3, y3);

        visited = new bool[row][col]();
        visited[0][0] = true;
    }
    return 0;
}