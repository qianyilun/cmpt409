
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


bool is_oponnet(int character, int offset) {
    int diff = character - offset;
    cout << " diff: " << diff << " result: " << (diff >= 0 && diff <= 25) << endl;
    return (diff >= 0 && diff <= 25);
}


// Param: 0 -- White king
//        1 -- Black king
// The function will check if there is oponnet's (r)ook, (b)ishop, (q)ueen, (k)ing nearby.
bool Board::check_rbqk(int which_king) {
    int row, col, offset;
    if (which_king == 0) {
        tie(row, col) = white_king;
        offset = 'a';
    } else {
        tie(row, col) = black_king;
        offset = 'A';
    }

    // Checking row...
    for (int i = 0; i < col; ++i) {
        cout << "row: " << row << " col: " << i << " char: " << data[row][i];
        if (is_oponnet(data[row][i], offset)) return true;
    }
    for (int i = col + 1; i < 8; ++i) {
        cout << "row: " << row << " col: " << i << " char: " << data[row][i];
        if (is_oponnet(data[row][i], offset)) return true;
    }

    // Checking column...
    for (int i = 0; i < row; ++i) {
        cout << "row: " << i << " col: " << col << " char: " << data[i][col];
        if (is_oponnet(data[i][col], offset)) return true;
    }
    for (int i = row + 1; i < 8; ++i) {
        cout << "row: " << i << " col: " << col << " char: " << data[i][col];
        if (is_oponnet(data[i][col], offset)) return true;
    }

    // Checking left-right diagonal...
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_oponnet(data[r][c], offset)) return true;
    }
    for (int r = row + 1, c = col + 1; r < 8 && c < 8; ++r, ++c) {
        cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_oponnet(data[r][c], offset)) return true;
    }

    // Checking right-left diagonal...
    for (int r = row - 1, c = col + 1; r >= 0 && c < 8; --r, ++c) {
        cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_oponnet(data[r][c], offset)) return true;
    }
    for (int r = row + 1, c = col - 1; r < 8 && c >= 0; ++r, --c) {
        cout << "row: " << r << " col: " << c << " char: " << data[r][c];
        if (is_oponnet(data[r][c], offset)) return true;
    }


    return false;
}





int main() {

    string line;
    Board *b = new Board();
    while (true) {

        getline(cin, line);

        b->data.push_back(vector<char>(line.begin(), line.end()));
        b->line++;

        // We've read an empty board, the program should terminate.
        if (b->line == 8 && b->empty()) {
            break;
        }

        // Empty line indicates end of board
        if ( line.empty() ) {

            // Detect king' locations
            b->find_kings();

            cout << *b << endl;

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