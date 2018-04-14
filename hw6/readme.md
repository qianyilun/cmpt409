* lego
* prefix goodness
* QuantumTeleporters
* TennisProbability
* ZurchTrees



# Problem Bejeweled

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed





---

# Problem Binary

## (a) how to store data

1. Preprocess an array A to store the range of K with different length binary number ( more on part(b) )

## (b) Description methodology

* DP with 1d array

1. Preprocess an array A where A[i] stores the first digit number of value 2^i

   * ex.
     * A looks like [1 2 6 18 50 …..]
     * i = 2, A[2] = 6, indicate value 4 (2^2) 's first digit number is 6
     * 0 1 10 11 100, =>  $4_{10}$ = $100_2$ , where 1 in $100_2$ in the $6_{th}$ digit in binary sequence
   * Base case:
     * A[0] = 1, A[1] = 2
   * State function
     * $A[x] = (2^x - 2^{x-1})x + A[x-1]$
     * ex. x=3
       * A[3] = $(2^3-2^2)*3 + A[2] = 18$, where A[2] = 6
   * Stop allocate A until A[n] >= max k = 10^9

2. Recover

   * ex. input k = 30
   * Search first element in A that A[i] > k, in this case A[3] = 18, A[4] = 50, i = 4
   * k falls between 3 and 4 (i -1 to i)
     * between $18_{th}$ digit and $50_{th}$ digit are all 4 digits number
     * 1000, 1001, 1010, ………. ,1111, there are
       * $(50-18)/4 = 8$
       * $(A[i] - A[i-1])/i$  decimal numbers
       * $30_{th}$ digits falls in (30-18)/4 + 1= $4_{th}$ decimal numbers
         * **To sum up**, input k falls into{$2^{i-1} + (k-A[i-1])/i​$ }th decimal number
       * Then print the according bit in binary

   ​

## (c) Pseudocode if needed

```matlab
% Init array
i = 2; % iterator
A[0] = 1, A[1] = 2
while element in A < 10^9
	A[i] = (2^i - 2^(i-1)i + A[i-1];
	i++
end while

% read each k
for each input k
	find first element in A larger than k;
	j = index of this element;
	k falls into decimal value D = 2^(j-1) + (k-A[j-1])/j;
	D_b = binary of D;
	print according bit;
end for

```

---

# Problem CitySlickers

## (a) how to store data
By reading the input, generate a adjacency matrix to present each edge and weight.

## (b) Description methodology
1. Store the graph
2. Treat weights of mountain as 1 and others as 0
  * Now, it becomes a question to find the shortest path of a weighted undirect graph. Weights are either 0 or 1.
3. Using Dijkstra’s shortest path algorithm to find the solution

## (c) Pseudocode if needed
The implementation of Dijkstra's algorithm codebook can be found below.

https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

---



# Problem Cutting Pizza

## (a) how to store data

No data store in this question

## (b) Description methodology

* Draw a circle inside with r = dignonal of square
* We have A B C D areas as follow:
  * ![image-20180410172254359](https://ws2.sinaimg.cn/large/006tKfTcgy1fq8epycs3gj30ue0uqwhl.jpg)
* Denote
  * $S_{oc}$  = area of outer circle
  * $S_{ic}$  = area of inner circle
  * $S_{sq}$ = area of small square
* We concluded 3 equations:
  * $A+2B+C = 1/4 S_{oc}$
  * B+D = A       (from question)
  * D = 1/4$S_{ic} - 1/2S_{sq}$
* D, C are known, the only unknown in 3 equations is B, which we can easily solve
* $B = 1/12S_{oc} - 1/6S_{ic}-1/4S_{sq}$
* FInal Area = B+D = $1/12S_{oc} + 1/12 S_{ic}-1/4S_{sq}$

## (c) Implementation:

Solve equation with X and `double pi = acos(-1)`

---

# Problem DoingLaundry

sort by drying time, dp

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem LinkingLogos

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem Longshot

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem PrefixGoodness

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem CuttQuantumTeleporters

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem TennisProbability

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed

---

# Problem ZurchTrees

## (a) how to store data

## (b) Description methodology

## (c) Pseudocode if needed
