
/*  Created by Peter Tan  @peterjtan
 *  Date: 2018-01-12
 */


// Define DEBUG to show debugging console ouputs.
// Define RELEASE to omit debugging console ouputs.
#define RELEASE


#include <bitset>
#include <iostream>
#include <map>
#include <stdexcept>
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


template<size_t n>
bitset<n> reverse_bits(bitset<n> input) {
    bitset<n> result = 0;
    for (int i = n - 1; i >= 0; --i) {
        result[0 - (i - n)] = input[i];
    }
    return result;
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

    // return a std::tuple which contains black and white vectors.
    return make_tuple(black, white);
}


bitset<64> construct_bit_representation(const vector<string>& pokerHands) {
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
    }

#ifdef DEBUG 
    cout << endl;
    cout << "Highest card: " << highest_card << endl;

    // === Print bit representation of each suit ===

    for (const auto& kv : suit_map) {
        cout << kv.second << " ";
    }
    cout << endl;
#endif


    // === Count max same value and # of pairs ===
    int max_same_value = 0;
    int pair_count = 0;

    // Used to store the card which appears the most and the second-most in the hand
    int max_same_value_card = 0;
    int second_max_same_value_card = 0;

    for (int i = 0; i < 13; i++) {
        int sum = suit_map['C'][i] + suit_map['D'][i] + suit_map['H'][i] + suit_map['S'][i];
        
        if (sum > max_same_value) {
            max_same_value = sum;
            second_max_same_value_card = max_same_value_card;
            max_same_value_card = 0 - (i - 14);
        }

        if (sum > 1) {
            ++pair_count;
            second_max_same_value_card = 0 - (i - 14);
        }
    }

    // There is no appear most and 2nd-most card since no same value in the hand
    if (pair_count == 0) {
        max_same_value_card = 0;
        second_max_same_value_card = 0;
    }

#ifdef DEBUG
    cout << "Max same value: " << max_same_value << endl;
    cout << "Appear-most card: " << max_same_value_card << endl;
    cout << "Appear 2nd-most card: " << second_max_same_value_card << endl;
    cout << "Pair count: " << pair_count << endl;
#endif


    // === Count max same suit ===
    int max_same_suit = 0;
    for (const auto& kv : suit_map) {
        int num_bits_set = (int) kv.second.count();
        max_same_suit = (num_bits_set > max_same_suit) ? num_bits_set : max_same_suit;
    }

#ifdef DEBUG
    cout << "Max same suit: " << max_same_suit << endl;
#endif


    // === Count max consecutive cards ===
    int max_consecutive = 0;

    bitset<13> or_of_all_suits = 0;
    for (const auto& kv : suit_map) {
        or_of_all_suits |= kv.second;
    }
    // cout << or_of_all_suits << endl;
    for (unsigned int i = 0; i < or_of_all_suits.size(); ++i) {
        if (max_consecutive == 0 && or_of_all_suits[i] != or_of_all_suits[i - 1]) {
            ++max_consecutive;
        } else if (or_of_all_suits[i] != 0 && or_of_all_suits[i] == or_of_all_suits[i - 1]) {
            ++max_consecutive;
        }
    }

#ifdef DEBUG
    cout << "Max consecutive: " << max_consecutive << endl;
#endif


    // === Setting ranking information ===
    bitset<12> info = 0;
    // 0000 0000 0000
    // The first 4-bit stores rank code; 
    // second 4-bit stores decision card value; 
    // third 4-bit stores secondary decision card value;

    int rank_code = 0;

    // Decision card value will help determine win/lose of both hands are the same rank.
    // The value can be highest_card, max_same_value_card.
    int decision_card_value = 0;
    
    // Straight flush
    if (max_consecutive == 5 && max_same_suit == 5) {
        rank_code = 8;
        decision_card_value = highest_card;
    } 
    // 4 of a kind
    else if (max_same_value == 4) {
        rank_code = 7;
        decision_card_value = max_same_value_card;
    }
    // Full house
    else if (max_same_value == 3 && pair_count == 2) {
        rank_code = 6;
        decision_card_value = max_same_value_card;
    }
    // Flush
    else if (max_same_suit == 5) {
        rank_code = 5;
    }
    // Straight
    else if (max_consecutive == 5) {
        rank_code = 4;
        decision_card_value = highest_card;
    }
    // 3 of a kind
    else if (max_same_value == 3) {
        rank_code = 3;
        decision_card_value = max_same_value_card;
    }
    // 2 pairs
    else if (max_same_value == 2 && pair_count == 2) {
        rank_code = 2;
        decision_card_value = max_same_value_card;
        // Keep the secondary decision value (value of the other pair) in info bit
        info|= bitset<12>(second_max_same_value_card);
    }
    // 1 pair
    else if (max_same_value == 2) {
        rank_code = 1;
        decision_card_value = max_same_value_card;
    } 
    // High Card
    else {
        decision_card_value = highest_card;
    }

    // Setting rank code in info bitset
    info |= bitset<12>(rank_code) << 8;

    // Setting decition card value in info bitset
    info |= bitset<12>(decision_card_value) << 4;

#ifdef DEBUG
    cout << "Poker Hand Info: " << info << endl;
#endif

    int offset = 52;
    bitset<64> result = bitset<64>(info.to_ullong()) << offset;

    for (const auto& kv : suit_map) {
        offset -= 13;
        result |= bitset<64>(kv.second.to_ullong()) << offset;
    }
    return result;
}


int compare(const bitset<64>& a, const bitset<64>& b) {
    uint16_t info_code_a = (a >> 52).to_ulong(),
             info_code_b = (b >> 52).to_ulong();

#ifdef DEBUG
    cout << endl;
    cout << "Info code: " << bitset<16>(info_code_a) << " " << bitset<16>(info_code_b) << endl;
#endif
    
    if (info_code_a < info_code_b) {
        return -1;
    } else if (info_code_a > info_code_b) {
        return 1;
    } else if (info_code_a == info_code_b) {
        
        int rank_code = info_code_a >> 8;
        switch ( rank_code ) {

            case 8: // Intentionally fall over -- Straight Flush
            case 7: // Intentionally fall over -- 4 of a kind
            case 6: // Intentionally fall over -- Full house
            case 4: // Intentionally fall over -- Straight
            case 3: // Intentionally fall over -- 3 of a kind
                return 0;

            case 5: // -- Flush
            case 2: // -- 2 pairs
            case 1: // -- Pair
            case 0: // -- High Card
                // Since the code is 16-bit long, need to be careful about shifting.
                uint16_t decision_code = (info_code_a & 0x00F0) >> 4, /* 0000 0000 1111 0000 */
                         second_decision_code = info_code_a & 0x000F; /* 0000 0000 0000 1111 */


                bitset<13> or_a = 0, or_b = 0;
                for (int i = 0; i < 13; ++i) {
                    or_a |= (a[i] | a[i + 13] | a[i + 26] | a[i + 39]) << i;
                    or_b |= (b[i] | b[i + 13] | b[i + 26] | b[i + 39]) << i;
                }

#ifdef DEBUG
                cout << "Decision code: " << decision_code << endl
                     << "Second decision code: " << second_decision_code << endl
                     << "or_a: " << or_a << " or_b: " << or_b << endl;
#endif


                // Don't do anything to High Card
                if (rank_code != 0 && rank_code != 5) {
                    or_a[0 - (decision_code - 14)] = 0;
                    or_b[0 - (decision_code - 14)] = 0;
                }

                // 2 pairs
                if (rank_code == 2) {
                    or_a[0 - (second_decision_code - 14)] = 0;
                    or_b[0 - (second_decision_code - 14)] = 0;
                }

                or_a = reverse_bits(or_a);
                or_b = reverse_bits(or_b);

#ifdef DEBUG
                cout << "Changed or_a: " << or_a << " or_b: " << or_b << endl;
#endif

                // We are using the most significant bit in bitset as our least signifiant bit
                uint32_t or_a_int = or_a.to_ulong(), or_b_int = or_b.to_ulong();
                
                if (or_a_int < or_b_int) {
                    return -1;
                } else if (or_a_int > or_b_int) {
                    return 1;
                } else if (or_a_int == or_b_int) {
                    return 0;
                }

        }

    }

    return -2;
}



int main() {

    string input_line;
    getline(cin, input_line);

    while (!input_line.empty()) {
        vector<string> black, white;
        tie(black, white) = split(input_line, ' ');

#ifdef DEBUG
        cout << "Black: " << black << endl 
             << "White: " << white << endl;
#endif

        bitset<64> black_bit = construct_bit_representation(black);
        bitset<64> white_bit = construct_bit_representation(white);

        int result = compare(black_bit, white_bit);
        switch (result) {
            case -1: cout << "White wins." << endl; break;
            case 0:  cout << "Tie."        << endl; break;
            case 1:  cout << "Black wins." << endl; break;
            default: 
                throw logic_error("Comparison result '" + to_string(result) + "' is unexpected. ");
        }

        getline(cin, input_line);
    }

    return 0;
}