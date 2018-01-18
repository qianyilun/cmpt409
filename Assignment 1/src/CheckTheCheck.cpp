
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
    bool check_board(int);
    bool is_under_check(int which_king, int& blocked, 
                        int king_row, int king_col, int piece_row, int piece_col);
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
bool Board::is_under_check(int which_king, int& blocked, 
                    int king_row, int king_col, int piece_row, int piece_col) {

    // Account for vector index out of bound
    if (piece_row < 0 || piece_row > 7 || piece_col < 0 || piece_col > 7) {
        return false;
    }
    
    char character = data[piece_row][piece_col];
    // cout << "king: " << which_king << " row: " << piece_row << " col: " << piece_col << " char: " << character;

    if (character == '.') {
        // cout << endl;
        return false;
    }

    int offset = (which_king == 0) ? 'a' : 'A';

    int diff = character - offset;
    
    // cout << " diff: " << diff << " result: " << (diff >= 0 && diff <= 25) << " blocked: " << blocked << endl;
    
    if (diff >= 0 && diff <= 25 && (character == 'n' || character == 'N')) {
        return true;
    }
    else if (diff >= 0 && diff <= 25 && blocked == 0) {
        if ( (character == 'k' || character == 'K') && 
             (abs(king_col - piece_col) > 1 || abs(king_row - piece_row) > 1) ) {
            blocked = 1;
            return false;
        }
        else if ( (character == 'p' || character == 'P') &&
             (abs(king_col - piece_col) > 1 || abs(king_row - piece_row) > 1) ) {
            blocked = 1;
            return false;
        }
        else if ( (character == 'p' && which_king == 0) && 
             (abs(piece_col - king_col) != 1 || piece_row - king_row == 1 || piece_row - king_row == 0) ) {
            blocked = 1;
            return false;
        }
        else if ( (character == 'P' && which_king == 1) && 
             (abs(piece_col - king_col) != 1 || piece_row - king_row == -1 || piece_row - king_row == 0) ) {
            blocked = 1;
            return false;
        }
        else if ( (character == 'b' || character == 'B') && 
             (abs(king_col - piece_col) == 0 || abs(king_row - piece_row) == 0) ) {
            blocked = 1;
            return false;
        }
        else if ( (character == 'r' || character == 'R') && 
             (abs(king_col - piece_col) != 0 && abs(king_row - piece_row) != 0) ) {
            blocked = 1;
            return false;
        }
        
        return true;
    }
    else {
        blocked = 1;
        return false;
    }
}


// Param: 0 -- White king
//        1 -- Black king
// The function will check if there is oponnet's (r)ook, (b)ishop, (q)ueen, (k)ing nearby.
bool Board::check_board(int which_king) {
    int row, col;
    if (which_king == 0) {
        tie(row, col) = white_king;
    } else {
        tie(row, col) = black_king;
    }

    int blocked = -1;
    bool knight_result =
           is_under_check(which_king, blocked, row, col, row + 1, col - 2) ||
           is_under_check(which_king, blocked, row, col, row - 1, col - 2) ||
           is_under_check(which_king, blocked, row, col, row + 1, col + 2) ||
           is_under_check(which_king, blocked, row, col, row - 1, col + 2) ||
           is_under_check(which_king, blocked, row, col, row + 2, col - 1) ||
           is_under_check(which_king, blocked, row, col, row - 2, col - 1) ||
           is_under_check(which_king, blocked, row, col, row + 2, col + 1) ||
           is_under_check(which_king, blocked, row, col, row - 2, col + 1);
    if (knight_result) 
        return true;

    int i, r, c;

    // Checking row...
    for (i = col - 1, blocked = 0; i >= 0 && !blocked; --i) {
        if (is_under_check(which_king, blocked, row, col, row, i)) return true;
    }
    for (i = col + 1, blocked = 0; i < 8 && !blocked; ++i) {
        if (is_under_check(which_king, blocked, row, col, row, i)) return true;
    }

    // Checking column...
    for (i = row - 1, blocked = 0; i >= 0 && !blocked; --i) {
        if (is_under_check(which_king, blocked, row, col, i, col)) return true;
    }
    for (i = row + 1, blocked = 0; i < 8 && !blocked; ++i) {
        if (is_under_check(which_king, blocked, row, col, i, col)) return true;
    }

    // Checking left-right diagonal...
    for (r = row - 1, c = col - 1, blocked = 0; r >= 0 && c >= 0 && !blocked; --r, --c) {
        if (is_under_check(which_king, blocked, row, col, r, c)) return true;
    }
    for (r = row + 1, c = col + 1, blocked = 0; r < 8 && c < 8 && !blocked; ++r, ++c) {
        if (is_under_check(which_king, blocked, row, col, r, c)) return true;
    }

    // Checking right-left diagonal...
    for (r = row - 1, c = col + 1, blocked = 0; r >= 0 && c < 8 && !blocked; --r, ++c) {
        if (is_under_check(which_king, blocked, row, col, r, c)) return true;
    }
    for (r = row + 1, c = col - 1, blocked = 0; r < 8 && c >= 0 && !blocked; ++r, --c) {
        if (is_under_check(which_king, blocked, row, col, r, c)) return true;
    }


    // Checking knight...
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
            if (b->check_board(1)) {
                cout << "black king is in check." << endl;
            } else if (b->check_board(0)) {
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