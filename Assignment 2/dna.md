GATTACA
=============

### How to run
The program is written in C++ 11 standard and tested and built under Ubuntu with GCC 5.4.
``` g++ -std=c++11 -Wall -Wextra dna.cpp ```

### How does the program work?

* For each case, read in the string and build the suffix array.
* Using the suffix array, we are able to find the Longest Common Prefix for the string for i = 0 to length of the given string.
* Now we already know the longest repeated part of the string. We now need to find how many times this string is repeated.
    * In order to achieve this, I used the built-in function `string::find`. Every time I am able to find the longest repeated string, I will increment a counter. 
* After calculated how many times it has been repeated, we are ready to print out the result.

### Data Structure

1. Suffix array implementation is modified from Stanford ACM codebook and make use of the Longest Common Prefix function defined in the data structure.
2. A custom sorted set is used to keep track of which is the longest repeated string. This is done by using a lambda function like this: 
```
auto sort_set = [](const string& s1, const string& s2) {
    if (s1.length() == s2.length()) {
        return s1 < s2;
    } else {
        return s1.length() > s2.length();
    }
};
```
  * Once an element is inserted into the set, we sort it using the length in descending order. If 2 elements in the set have the same length, we will sort alphabetically. This guarentees that the first element in the set is what we want.
