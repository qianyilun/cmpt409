Where's Waldorf?
=============

### How to run
Tested and built under Ubuntu with GCC 5.4.
``` g++ -std=c++11 -Wall -Wextra PokerHands.cpp ```

### How does the program work?

* First, read in all inputs and constuct a data matrix consisting of the puzzle that we need to work on.
* For the words we need to find, we need to concatenate them with the character `.`. For example, if the test words are `Waldorf`, `Bambi`, `Betty`, we would need to turn these words into `.Waldorf.Bambi.Betty.`.
* Next, we would need to build a suffix array based on the resulted string of the previous step. The code for constructing such data structure is adapted from Stanford ACM Codebook. 
* On top of that data structure, I've written some code to do **binary seach on the suffix array** to find whether a given string is an exact match in the suffix array. For example, `Betty` is an exact match of the constructed string whereas `Bet` is not. In order to compute this, basically I need to find whether `"." + the_given_string + "."` is in the suffix array or not.
* When the proram runs, it will loop through each position for each row and for each column. During each position, the program will construct 8 strings from that position. They are `horizontal_right`, `horizontal_left`, `vertical_up`, `vertical_down`, `diagonal_right-up`, `diagonal_left-down`, `diagonal_left-up` and `diagonal_right-down`. They represent the 8 directions where a given position can reach. For each direction string, we need to call `is_exact_match()` to find whether such string can be exactly found in the suffix array. If yes, we will record the string that can be found from this location and the coordinate of the location.
* In the end, the program will output the locations that has been recorded previously and from where the given test words can be found.
