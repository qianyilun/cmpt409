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
	map<char, bitset<13>> suit_map {{'C', 0}, {'D', 0}, {'H', 0}, {'S', 0}};
	
	// Used to store the highest value of a card in the poker hand
	int highest_card = 0;

	for (const auto& i : pokerHands) {
		// cout << i[0] << endl;
		int card_value = i[0] - '0'; // Converting from char to int
		// cout << card_value << endl;
		
		// If the card value is not 2~9, map T, J, Q, K, A to 10~14
		if ( !(card_value >= 2 && card_value <= 9) ) {
			switch(i[0]) {
				case 'T': card_value = 10; break;
				case 'J': card_value = 11; break;
				case 'Q': card_value = 12; break;
				case 'K': card_value = 13; break;
				case 'A': card_value = 14; break;
			}
		}

		// Store the card in bit representation
		int ind = 0 - (card_value - 2 - 12);
		suit_map[ i[1] ][ind] = 1;


		highest_card = (card_value > highest_card) ? card_value : highest_card;


		// switch (i[1]) {
		// 	case 'C': suit_map['C'] |= 1 << ( 0 - (card_value - 14) ); break;
		// 	case 'D': suit_map['D'] |= 1 << ( 0 - (card_value - 14) ); break;
		// 	case 'H': suit_map['H'] |= 1 << ( 0 - (card_value - 14) ); break;
		// 	case 'S': suit_map['S'] |= 1 << ( 0 - (card_value - 14) ); break;
		// 	default: break;
		// }

	}

	// === Print bit representation of each suit ===

	for (const auto& kv : suit_map) {
		cout << kv.second << " ";
	}
	cout << endl;


	// === Count max same value and # of pairs ===
	int max_same_value = 0;
	int pair_count = 0;

	for (int i = 0; i < 13; i++) {
		int sum = suit_map['C'][i] + suit_map['D'][i] + suit_map['H'][i] + suit_map['S'][i];
		
		max_same_value = (sum > max_same_value) ? sum : max_same_value;
		if (sum > 1) {
			++pair_count;
		}
	}
	cout << "Max same value: " << max_same_value << endl;
	cout << "Pair count: " << pair_count << endl;


	// === Count max same suit ===
	int max_same_suit = 0;
	for (const auto& kv : suit_map) {
		int num_bits_set = (int) kv.second.count();
		max_same_suit = (num_bits_set > max_same_suit) ? num_bits_set : max_same_suit;
	}
	// cout << "Max same suit: " << max_same_suit << endl;

	cout << "Highest card: " << highest_card << endl;


	// === Count max consecutive cards ===
	int max_consecutive = 0;

	bitset<13> or_of_all_suits = 0;
	for (const auto& kv : suit_map) {
		or_of_all_suits |= kv.second;
	}
	// cout << or_of_all_suits << endl;
	for (unsigned int i = 1; i < or_of_all_suits.size(); ++i) {
		if (max_consecutive == 0 && or_of_all_suits[i] != or_of_all_suits[i - 1]) {
			++max_consecutive;
		} else if (or_of_all_suits[i] != 0 && or_of_all_suits[i] == or_of_all_suits[i - 1]) {
			++max_consecutive;
		}
	}
	// cout << "Max consecutive: " << max_consecutive << endl;

	return -1;
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