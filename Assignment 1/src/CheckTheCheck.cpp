
/*  Created by Peter Tan  @peterjtan
 *  Date: 2018-01-17
 */


#include <algorithm>
#include <iostream>
#include <string>
#include <tuple> // std::tie
#include <utility>
#include <vector>
using namespace std;


class Board {
public:
    vector<vector<char>> data;
    int line;
    pair<int, int> white_king; // <row, column> of the king's location
    pair<int, int> black_king; // <row, column> of the king's location

    Board() : data(), line(0) { }
    bool empty();
    friend ostream& operator <<(ostream&, const Board&);
    void find_kings();
    bool check_rbqk(int);
};


bool Board::empty() {
    return all_of(data.begin(), data.end(), [](const vector<char>& row) {
        return all_of(row.begin(), row.end(), [](const char& elem) {
            return elem == '.';
        });
    });
}

// Overload << operator for printing Board object
ostream& operator <<(ostream& os, const Board& b) {
    os << "Board: " << endl
       << "-------------------" << endl;
    for (const auto& row : b.data) {
        for (const auto& elem : row) {
            os << elem << ' ';
        }
        os << endl;
    }
    os << "-------------------" << endl;

    os << "White king: (" << b.white_king.first << ", " << b.white_king.second << ")" << endl
       << "Black king: (" << b.black_king.first << ", " << b.black_king.second << ")" << endl;
    return os;
}


void Board::find_kings() {
    for (unsigned int i = 0; i < data.size(); ++i) {
        for (unsigned int j = 0; j < data[i].size(); ++j) {
            
            // Detect white king location
            if (data[i][j] == 'K') {
                white_king = make_pair(i, j);
            }
            // Detect black king location
            else if (data[i][j] == 'k') {
                black_king = make_pair(i, j);
            }
        }
    }
}


// Param which_king: 0 -- White king
//                   1 -- Black king
// The bool variable "guarded" will be updated if we see a self piece along the way
bool is_under_check(int character, int which_king, bool& guarded) {
    if (character == '.') {
        // cout << endl;
        return false;
    }

    int offset = (which_king == 0) ? 'a' : 'A';

    int diff = character - offset;
    // cout << " diff: " << diff << " result: " << (diff >= 0 && diff <= 25) << " guarded: " << guarded << endl;
    
    if (diff >= 0 && diff <= 25 && !guarded)
        return true;
    else {
        guarded = true;
        return false;
    }
}


// Param: 0 -- White king
//        1 -- Black king
// The function will check if there is oponnet's (r)ook, (b)ishop, (q)ueen, (k)ing nearby.
bool Board::check_rbqk(int which_king) {
    int row, col;
    if (which_king == 0) {
        tie(row, col) = white_king;
    } else {
        tie(row, col) = black_king;
    }

    int i, r, c;
    bool guarded;
    // Checking row...
    for (i = col - 1, guarded = false; i >= 0; --i) {
        // cout << "row: " << row << " col: " << i << " char: " << data[row][i];
        if (is_under_check(data[row][i], which_king, guarded)) return true;
    }
    for (i = col + 1, guarded = false; i < 8; ++i) {
        // cout << "row: " << row << " col: " << i << " char: " << data[row][i];
        if (is_under_check(data[row][i], which_king, guarded)) return true;
    }

    // Checking column...
    for (i = row - 1, guarded = false; i >= 0; --i) {
        // cout << "row: " << i << " col: " << col << " char: " << data[i][col];
        if (is_under_check(data[i][col], which_king, guarded)) return true;
    }
    for (i = row + 1, guarded = false; i < 8; ++i) {
        // cout << "row: " << i << " col: " << col << " char: " << data[i][col];
        if (is_under_check(data[i][col], which_king, guarded)) return true;
    }

    // Checking left-right diagonal...
    for (r = row - 1, c = col - 1, guarded = false; r >= 0 && c >= 0; --r, --c) {
        // cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_under_check(data[r][c], which_king, guarded)) return true;
    }
    for (r = row + 1, c = col + 1, guarded = false; r < 8 && c < 8; ++r, ++c) {
        // cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_under_check(data[r][c], which_king, guarded)) return true;
    }

    // Checking right-left diagonal...
    for (r = row - 1, c = col + 1, guarded = false; r >= 0 && c < 8; --r, ++c) {
        // cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_under_check(data[r][c], which_king, guarded)) return true;
    }
    for (r = row + 1, c = col - 1, guarded = false; r < 8 && c >= 0; ++r, --c) {
        // cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_under_check(data[r][c], which_king, guarded)) return true;
    }


    return false;
}





int main() {

    string line;
    Board *b = new Board();
    int gameNum = 0;
    while (true) {

        getline(cin, line);
        if (line != "") {
            b->data.push_back(vector<char>(line.begin(), line.end()));
            b->line++;
        }
        else {

            // We've read an empty board, the program should terminate.
            if (b->line == 8 && b->empty()) {
                break;
            }

            // Detect king' locations
            b->find_kings();

            // cout << *b << endl;

            gameNum++;
            cout << "Game #" << gameNum << ": ";

            // Do comparison
            if (b->check_rbqk(1)) {
                cout << "black king is in check." << endl;
            } else if (b->check_rbqk(0)) {
                cout << "white king is in check." << endl;
            } else {
                cout << "no king is in check." << endl;
            }

            // Do clean up
            Board *temp = b;
            b = new Board();
            delete temp;
        }
    }

    delete b;

    return 0;
}