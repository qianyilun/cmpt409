# 10271 chopsticks

## Set up

It was written in **C++ 11**. Run by command

``g++ -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE``

It has been accepted by Uva.

# Observation

* In a set {A,B,C}, A,B must be adajent (assuming all chopsticks are sorted by length)

# Algorithm overview



* Build a preprocessing map M\[chop][people], in where we store badness in M
  * If we first fix variable people, for each chopstick, there are two subproblem:
    * chopstick is in the optimal solution
      * Then we take chopstick i and i-1
      * M\[chop][people] = min{M\[chop-1][people],M\[chop-2][people] + badness(chop -1, chop)}
    * Chopstick is not in the optimal solution
      * Total badness = the previous entry
      * M\[chop][people] = M\[chop-1][people]
* To satifsy the existence of C, chop >= people*3

# Thought process about finding C

* To determine whether there is a C is tricky.
  * For some test case M\[N][K] is solution but for some are M\[N-2][K]
  * It's hard to deal with the last couple chopsticks to satify the C condition
  * In another word existing C is not guaranteed.
* Finally we figure out that we can sort chopsticks in decent order
  * In this way a C for each set/people is guaranteed.


# 10069

## Set up

It was written in Java 1.9. Compile by command
``javac Main.java``.

Then run by command ``java Main``.

It has been accepted by Uva.

# Observation

The question is to find the same subsequence in a given sequence. As we can see, it is not necessary for
indices of sequence to ensure all letters are continously, but must be in the increasing order to
consist to the subsequence.


In addition, the question is to count the number of occurrences and which indicates it is high possibility to
use dynamic programming to decrease the complexity.

# Algorithm overview

I treat X as a "sequence", and Z as a "subsequence".

Since the length of sequence is less than 10,000,the regular int type cannot hold such long indices of
sequence. Therefore, a object of Java, BigInteger, can hold this requirement. There are two arguments in input strings. We need to have a 2D BigInteger array to hold these two arguments. And the size of 2D array depends on the size of given sequence and subsequence.

Then, we step into this question. We need to compare sequence and subsequence letter by letter, and use dynamic programming to save time. When the letter of sequence is equal to the letter of subsequence, we need to add its previous result of sequence and previous result of subsequence, and save the result to 2D array. Otherwise, update current result as the previous result of sequence.

Formally,

`` if X[i] == Z[j], dp[i][j] = dp[i-1][j] + dp[i-1][j-1];``

`` if X[i] != Z[j], dp[i][j] = dp[i-1][j];``


# Data structure and Speical library

* Static 2D array of BigInteger
* BigInteger object and its methods and fields
  * BigInteger.One;
  * BigInteger.Zero;
  * BigInteger	add(BigInteger val);
