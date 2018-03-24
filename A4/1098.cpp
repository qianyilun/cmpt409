#include <iostream>
#include <cmath>

using namespace std;

enum Direction {
    Top, Right, Bottom, Left
};

bool visited[8][8];
// The following are used to store the 1~3 checkpoints and (0, 1) being the final point to reach
int cp1_x, cp1_y, cp2_x, cp2_y, cp3_x, cp3_y, cp4_x, cp4_y, finalcp_x = 0, finalcp_y = 1;
int row, col;
int totalsteps;

inline int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

inline bool checkCondition(int x, int y, Direction d) {
    // If within grid range, we need to check neighbour to prevent disconnection
    // If the next move results in disconnection, we don't need to continue, we just need to stop right at this move
    if (x >= 0 && x < row && y >= 0 && y < col) {
        switch (d) {
        case Bottom:
            // If at the very bottom row, check whether left and right neighbour has been visited or not
            return x == 0 && y > 0 && y < col - 1 ? (visited[x][y - 1] || visited[x][y + 1]) : true;
        case Top:
            // If at the very top row, check whether left and right neighbour has been visited or not
            return x == row - 1 && y > 0 && y < col - 1 ? (visited[x][y - 1] || visited[x][y + 1]) : true;
        case Left:
            // If at the very left column, check whether top and bottom neighbour has been visited or not
            return y == 0 && x > 0 && x < row - 1 ? (visited[x - 1][y] || visited[x + 1][y]) : true;
        case Right:
            // If at the very right column, check whether top and bottom neighbour has been visited or not
            return y == col - 1 && x > 0 && x < row - 1 ? (visited[x - 1][y] || visited[x + 1][y]) : true;
        }
    } else {
        return false;
    }
}

int dfs(int step, int i, int j) {
    // /* Prunning */
    // If we haven't reached the specified steps for checkpoints but checkpoints have been visited, stop.
    if (step < totalsteps/4 && visited[cp1_x][cp1_y]) return 0;
    if (step < totalsteps/2 && visited[cp2_x][cp2_y]) return 0;
    if (step < 3*totalsteps/4 && visited[cp3_x][cp3_y]) return 0;

    // If we are currently at the specified steps for checkpoints but the tile we are current at is not the checkpoint, stop.
    if (totalsteps/4 == step && (i != cp1_x || j != cp1_y)) return 0;
    if (totalsteps/2 == step && (i != cp2_x || j != cp2_y)) return 0;
    if (3*totalsteps/4 == step && (i != cp3_x || j != cp3_y)) return 0;
    if (totalsteps == step && (i != finalcp_x || j != finalcp_y)) return 0;

    // If we haven't reached the specified steps for checkpoints but the required steps for reaching checkpoints are too far, stop.
    if (step < totalsteps/4 && manhattan(i, j, cp1_x, cp1_y) > totalsteps/4 - step) return 0;
    if (step < totalsteps/2 && manhattan(i, j, cp2_x, cp2_y) > totalsteps/2 - step) return 0;
    if (step < 3*totalsteps/4 && manhattan(i, j, cp3_x, cp3_y) > 3*totalsteps/4 - step) return 0;

    if (totalsteps == step && i == finalcp_x && j == finalcp_y) return 1;

    int soln = 0;
    // Visit bottom
    if (checkCondition(i - 1, j, Bottom) && !visited[i - 1][j]) {
        visited[i - 1][j] = true;
        soln += dfs(step + 1, i - 1, j);
        visited[i - 1][j] = false;
    }
    // Visit top
    if (checkCondition(i + 1, j, Top) && !visited[i + 1][j]) {
        visited[i + 1][j] = true;
        soln += dfs(step + 1, i + 1, j);
        visited[i + 1][j] = false;
    }
    // Visit left
    if (checkCondition(i, j - 1, Left) && !visited[i][j - 1]) {
        visited[i][j - 1] = true;
        soln += dfs(step + 1, i, j - 1);
        visited[i][j - 1] = false;
    }
    // Visit right
    if (checkCondition(i, j + 1, Right) && !visited[i][j + 1]) {
        visited[i][j + 1] = true;
        soln += dfs(step + 1, i, j + 1);
        visited[i][j + 1] = false;
    }
    return soln;
}

int main() {
    int cases = 1;
    while (cin.peek() != EOF) {
    scanf("%d %d\n", &row, &col);
    if (row == 0 && col == 0)
        return 0;

    totalsteps = row * col;

    scanf("%d %d %d %d %d %d\n", &cp1_x, &cp1_y, &cp2_x, &cp2_y, &cp3_x, &cp3_y);

    // Clear out the visited table
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            visited[i][j] = 0;
        }
    }

    visited[0][0] = true;
    cout << "Case " << cases++ << ": " << dfs(1, 0, 0) << endl;
    }
}