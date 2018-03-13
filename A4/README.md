# Tug-of-War

## Set up

It was written in **C++ 11**. Run by command

``g++ -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE``

It has been accepted by Uva.

## Algorithm Overview

* It is not able to enumerate all possible solution since the test cases are two large.
* According to the lecture note, we need to design a dynamic programming to store the valid ways to make sum-weight j. j = 1,2,...,W/2, where W is the total weight of all the persons. 
* Binay mentioned in the email, we can use bitmask to solve this question. 
    > If the kth bit of bitmask DP[j] is on, it represents that k number weights are needed to make sum j. We need to use long long integer to store the mask.
* In addition, DP[0] should be initialized as 1 since there should be only 1 way to allocate the person who has weight 0. 
    > Initially, DP[0] = 1LL to indicate that 0 number of weights need to make sum weight 0.
* Build DP[i,j] function and see the details below.
    * Please note, in DP building process, "i" is outer loop index which is between 0 to the number of people, "j" is inner loop index which is counting down from total-weight to i-th weight.
 * After that, your nested loop to find out the total weights in the left team and right team. Left team should be the minimum weight and right team should be the maximum weight. And inner loop only need to loop from 0 to middle-weight instead of entire weight.
    > The turned-on bits of bitmask of DP[j] indicate the number of weights needed to make sum-weight j. We then look for the ceil(n/2) bit of the bitmask of DP[j] for j = W/2,(W/2) − 1, .....

## Data Structure and Data Type
* The recuirsive definition of DP[j], when i-th person is being considered.
``` DP[j] = DP[j] ∨ (DP[j − weight[i]] << 1LL) ```
* ```vector<int>``` to store all persons' weight.
* ```long long``` as DP array type.
