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