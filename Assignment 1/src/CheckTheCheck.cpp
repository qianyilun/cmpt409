
/*  Created by Peter Tan  @peterjtan
 *  Date: 2018-01-17
 */


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Board {
public:
    vector<vector<char>> data;
    int line;

    Board() : data(), line(0) { }
    bool empty();
    friend ostream& operator <<(ostream&, const Board&);
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
    return os;
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

            // Do comparison
            cout << *b << endl;

            // Do clean up
            Board *temp = b;
            b = new Board();
            delete temp;
        }
    }

    delete b;

    return 0;
}