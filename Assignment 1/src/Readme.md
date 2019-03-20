# FleaCircus

## Set up

It was written in **C++ 5.3**. Run by command

```g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE FleaCircus.cpp```

## Algorithm overview

1. Build graph
2. DFS to get the path between two node
3. If the path length is even number, they meet. If not, they jump forever.

## Implementation detail

### Graph

Graph is implemented by an array of vector.

Each element in the array represents one node. Each element in vector represents the connected nodes. 

ex. a is connected with b,c,d, then g[a] is a vector has b, c, d

### DFS

DFS(start, end, parent), which call itself recursion.

### Path

ex. two nodes are 8,1

If we get path 854 - (1), where length = 3, then they jump forever between 5 and 4.

If we get path 8542 - (1), where length = 4, then they meet at 4.

------

------

<h1 id="poker-hands">Poker Hands</h1>
<h3 id="how-to-run">How to run</h3>
<p>Tested and built under Ubuntu with GCC 5.4. Command:
<code>g++ -std=c++11 -Wall -Wextra PokerHands.cpp</code></p>
<h3 id="steps-performed-in-the-program">Steps Performed in the Program</h3>
<ol>
<li>For each line read, split it into white and black poker hands.</li>
<li>For each poker hand with 5 cards, construct the bit representation using C++ STL library <code>bitset&lt;64&gt;</code>. There will be several maps to keep track of information when we are looping through the cards:
<ul>
<li><code>suit_count</code>: Keep track of # of cards in each suit in the poker hand.</li>
<li><code>value_count</code>: Keep track of # of cards with the same value in the poker hand.</li>
<li><code>highest_card</code>: A integer for keeping the highest value in the poker hand.</li>
<li><code>pair_count</code>: Keep track of # of pairs presented in the poker hand.</li>
</ul>
</li>
<li>There will be information bits like <code>0000 0000 0000</code> in the most significant bits part of the return value. The first 4 bits represent the ranking which is a binary number from 1~8 determined using the following criteria.</li>
</ol>

<table>
<thead>
<tr>
<th>Type</th>
<th align="center"># of Consecutive Value Cards</th>
<th align="center"># of Same Suit Cards</th>
<th align="center"># of Same Value Cards</th>
<th align="center"># of Pairs</th>
</tr>
</thead>
<tbody>
<tr>
<td>Straight flush</td>
<td align="center">5</td>
<td align="center">5</td>
<td align="center"></td>
<td align="center"></td>
</tr>
<tr>
<td>4 of a kind</td>
<td align="center"></td>
<td align="center"></td>
<td align="center">4</td>
<td align="center"></td>
</tr>
<tr>
<td>Full house</td>
<td align="center"></td>
<td align="center"></td>
<td align="center">3</td>
<td align="center">2</td>
</tr>
<tr>
<td>Flush</td>
<td align="center"></td>
<td align="center">5</td>
<td align="center"></td>
<td align="center"></td>
</tr>
<tr>
<td>Straight</td>
<td align="center">5</td>
<td align="center"></td>
<td align="center"></td>
<td align="center"></td>
</tr>
<tr>
<td>3 of a kind</td>
<td align="center"></td>
<td align="center"></td>
<td align="center">3</td>
<td align="center"></td>
</tr>
<tr>
<td>2 pairs</td>
<td align="center"></td>
<td align="center"></td>
<td align="center">2</td>
<td align="center">2</td>
</tr>
<tr>
<td>Pair</td>
<td align="center"></td>
<td align="center"></td>
<td align="center">2</td>
<td align="center"></td>
</tr>
</tbody>
</table><ol start="4">
<li>The second 4 bits represent the highest card. In case of the same ranking between the 2 poker hands, the highest card is used to determine who wins.</li>
<li>The will be further comparison if the highest card is the same as well. In this case, the program will construct the “or” bits with 4 suits (<span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>C</mi><mo>[</mo><mi>i</mi><mo>]</mo><mo>∣</mo><mi>D</mi><mo>[</mo><mi>i</mi><mo>]</mo><mo>∣</mo><mi>H</mi><mo>[</mo><mi>i</mi><mo>]</mo><mo>∣</mo><mi>S</mi><mo>[</mo><mi>i</mi><mo>]</mo><mo separator="true">,</mo><mi>i</mi><mo>=</mo><mn>1</mn><mo separator="true">,</mo><mi mathvariant="normal">.</mi><mi mathvariant="normal">.</mi><mi mathvariant="normal">.</mi><mo separator="true">,</mo><mn>1</mn><mn>3</mn></mrow><annotation encoding="application/x-tex">C[i] \mid D[i] \mid H[i] \mid S[i], i = 1, ..., 13</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="strut" style="height: 0.75em;"></span><span class="strut bottom" style="height: 1em; vertical-align: -0.25em;"></span><span class="base"><span class="mord mathit" style="margin-right: 0.07153em;">C</span><span class="mopen">[</span><span class="mord mathit">i</span><span class="mclose">]</span><span class="mrel">∣</span><span class="mord mathit" style="margin-right: 0.02778em;">D</span><span class="mopen">[</span><span class="mord mathit">i</span><span class="mclose">]</span><span class="mrel">∣</span><span class="mord mathit" style="margin-right: 0.08125em;">H</span><span class="mopen">[</span><span class="mord mathit">i</span><span class="mclose">]</span><span class="mrel">∣</span><span class="mord mathit" style="margin-right: 0.05764em;">S</span><span class="mopen">[</span><span class="mord mathit">i</span><span class="mclose">]</span><span class="mpunct">,</span><span class="mord mathit">i</span><span class="mrel">=</span><span class="mord mathrm">1</span><span class="mpunct">,</span><span class="mord mathrm">.</span><span class="mord mathrm">.</span><span class="mord mathrm">.</span><span class="mpunct">,</span><span class="mord mathrm">1</span><span class="mord mathrm">3</span></span></span></span></span>) which will tell us which value in the 13 values does the poker hand have and then compare the number. The poker hand which has the higher number of “or” bits will win.</li>
</ol>
<h1 id="check-the-check">Check the Check</h1>
<ol>
<li>Read console inputs and then build an 8x8 2-dimentional vector to store the information.</li>
<li>Find the coordinates of both white and black kings by going through the data structure.</li>
<li><strong>Starting from a king’s coordinate to the edge of the data structure</strong>, check horizontally, vertically and diagonally to see whether there is any piece along the way. If yes, then:
<ul>
<li>If the element is empty, ignore it and continue the search along the way.</li>
<li>If the first element we encountered belongs to the same team as the king (i.e. black king with black piece and vice versa), this means we are safe along this way. Set <code>blocked</code> to 1 to indicate this.</li>
<li>If the first element we encountered belongs to the oponnet  team as the king (i.e. black king with white piece and vice versa), we need to check this piece’s jumping. If it can reach the king in one legal move, the king will be under check.</li>
</ul>
</li>
<li>Knight’s jumping will be checked separately because it doesn’t follow any specific horizontal, vertical or diagonal move.</li>
</ol>
<h3 id="how-to-run-1">How to run</h3>
<p>Tested and built under Ubuntu with GCC 5.4. Command:
<code>g++ -std=c++11 -Wall -Wextra CheckTheCheck.cpp</code></p>
<h3 id="steps-performed-in-the-program-1">Steps Performed in the Program</h3>


------

# ErdosNumber

●     How to run

○     Compile: $ javac Main.java

○     Run: $ java Main

●     Data Structure

○     Used HashMap to save a graph

■     Key: (String) authors’ names

■     Value: (HashSet<String>)author’s connections

○     Used HashMap to save each author’serdos number

●     Algorithm Steps

○     Initial Graph by parsing string frominput - paper database

■     Use regular expression to parseauthor names

○     BFS to count erdos numbers for allauthors and save to HashMap

○     Use “for” loop to print out resultsthat saved on HashMap 

