#include <bitset>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
using namespace std;


// Overload << operator for printing a vector<string> object
ostream& operator <<(ostream& os, const vector<string>& input) {
	os << "[ ";
	for (auto i = input.begin(); i != input.end(); i++) {
		os << "'" << *i << "'";
		if (i != input.end() - 1) {
			os << ", ";
		}
	}
	os << " ]";
	return os;
}


// Split the input line into 2 vectors for black and white containing their poker hands
tuple<vector<string>, vector<string>> split(const string& input, char delimit) {
	istringstream ss(input);
	string temp;
	vector<string> black, white;
	int i = 0;
	while (i < 5 && getline(ss, temp, delimit)) {
		black.push_back(temp);
		++i;
	}
	while (getline(ss, temp, delimit)) {
		white.push_back(temp);
	}

	// return a std::pair which contains black and white vectors.
	return make_tuple(black, white);
}


uint64_t construct_bit_representation(const vector<string>& pokerHands) {

}


int main() {

	string input_line;
	getline(cin, input_line);

	while (!input_line.empty()) {
		vector<string> black, white;
		tie(black, white) = split(input_line, ' ');

		cout << "Black: " << black << endl 
		     << "White: " << white << endl;

		construct_bit_representation(black);
		construct_bit_representation(white);

		getline(cin, input_line);
	}

	return 0;
}