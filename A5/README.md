# 10054 The Necklace

## Set up

It was written in **C++ 11**. Run by command

``g++ -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE``

It has been accepted by Uva.

## Algorithm Overview

Assume we can treat each beads as an undirected edge by connecting two vertices. Then this  question is able to convert to a typical question of printing the Euler tour. An *Euler path* is defined as a path in a graph which vists *each edge* of the graph *exactly once*. An *Euler tour* is an Euler path which starts and ends on the same vertex. In this case, if it is a valid necklace, then colors should be marked exactly once and the first value and last value have the same value. According to our textbook "Competitive Programming 3", to check if a connected undirected graph has an Euler tour, we need to check if all its vertices have even degrees. It can be done in *O(|V| + |E|)*.

---



# 10147 Highways

## Set up

It was written in **C++ 11**. Run by command

``g++ -std=c++11 -lm -lcrypt -O2 -pipe -DONLINE_JUDGE``

It has been accepted by Uva.

**Graph building and MST algorithm was copied from code book**

## Algorithm Overview

* Built a graph
* **For existing highways, distance(cost) is 0**
* Find MST
  * Use kruskal

## Trick

* Use inline for calculating distance
* skip "sqrt" in distance since we are only comparing distance, sqrt is useless

---

