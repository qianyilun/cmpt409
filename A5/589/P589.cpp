#include <cstdio>
#include <iostream>
#include <tuple> // std::tie
#include <vector>
#include <queue>
using namespace std;

static const char man_move_tbl[] = "nswe";
static const char box_move_tbl[] = "NSWE";
static const int move_vertical[] = {-1, 1, 0, 0}, move_horizontal[] = {0, 0, -1, 1};


struct State {
  int man, box;
  string path;
  State(int m, int b, const string& p) : man(m), box(b), path(p) { }
};

struct Range {
  int lower, upper;
  Range(int l, int u) : lower(l), upper(u) { }
  bool operator()(int x) const { return lower <= x && x < upper; }
};

pair<bool, string> bfs_man(const vector<string>& maze, int start, int goal, int box) {
  int R = maze.size();
  int C = maze[0].size();
  Range row_range(0, R), col_range(0, C);

  queue<pair<string, int>> q;
  q.push(make_pair("", start));
  vector<vector<bool>> visited(R, vector<bool>(C, false));
  visited[start/C][start%C] = true;
  
  while (!q.empty()) {
    int ind; string path;
    tie(path, ind) = q.front();
    
    q.pop();
    if (ind == goal) {
        return make_pair(true, path);
    }
    for (int d = 0; d < 4; d++) {
      int i = (ind / C) + move_vertical[d];
      int j = (ind % C) + move_horizontal[d];
      if (row_range(i) && col_range(j) && i*C+j != box && maze[i][j] != '#' && !visited[i][j]) {
        visited[i][j] = true;
        q.push(make_pair(path + man_move_tbl[d], i*C+j));
      }
    }
  }
  return make_pair(false, "");
}


string bfs_box(const vector<string>& maze, int start, int goal, int box) {
  int R = maze.size();
  int C = maze[0].size();
  Range row_range(0, R), col_range(0, C);

  queue<State> q;
  q.push(State(start, box, ""));
  vector<vector<bool>> visited(R, vector<bool>(C, false));
  visited[box/C][box%C] = true;

  while (!q.empty()) {
    State s = q.front();
    q.pop();
    if (s.box == goal) {
      return s.path;
    }
    for (int d = 0; d < 4; d++) {
      int i = (s.box / C) + move_vertical[d];
      int j = (s.box % C) + move_horizontal[d];
      int k = (s.box / C) - move_vertical[d];
      int l = (s.box % C) - move_horizontal[d];

      if (row_range(i) && col_range(j) && 
          row_range(k) && col_range(l) && 
          maze[i][j] != '#' && maze[k][l] != '#' && !visited[i][j]) {
        
        bool can_move_man;
        string path;
        tie(can_move_man, path) = bfs_man(maze, s.man, k*C+l, s.box);

        if (can_move_man) {
          visited[i][j] = true;
          q.push(State(s.box, i*C+j, s.path + path + box_move_tbl[d]));
        }

      }
    }
  }
  return "Impossible.";
}


int main() {
  int r, c;
  int cases = 1;
  while (true) {
    scanf("%d %d\n", &r, &c);
    if (r == 0 && c == 0) {
        break;
    }

    vector<string> maze(r);
    int start, goal, box;

    for (int i = 0; i < r; i++) {
      getline(cin, maze[i]);

      for (int j = 0; j < c; j++) {
        int ind = i * c + j;
        if (maze[i][j] == 'S') {
          start = ind;
          maze[i][j] = '.';
        } else if (maze[i][j] == 'T') {
          goal = ind;
          maze[i][j] = '.';
        } else if (maze[i][j] == 'B') {
          box = ind;
          maze[i][j] = '.';
        }
      }
    }

    cout << "Maze #" << cases << endl;
    cout << bfs_box(maze, start, goal, box) << endl;
    cout << endl;

    ++cases;
  }

  return 0;
}