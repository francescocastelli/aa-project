# AA-PROJECT

This repository is part of the project for the  Advance Algorithm and Parallel Programming course at Polimi. 

## Goal
Implementation and benchmark in C++ of algorithms FILL, LEXM and LEXP from the paper [Algorithmic aspects of vertex elimination on graphs](https://epubs.siam.org/doi/10.1137/0205021) by Donald J. Rose and R. Endre Tarjan.

## Abstract 
The paper considers graph elimination process and provide two new algorithms for finding elimination orders: 

 - LEXM: finds minimal elimination ordering in O(n*e) time, where n is the number of nodes and e is the number of edges.
 - LEXP: finds perfect elimination ordering, if any exists, in O(n+e) time.

The paper also provide a new linear-time algorithm (FILL) to calculate the fill-in produced by any elimination ordering. 
The graphs are always supposed to be **undirected** and **connected**.

## Elimination process on ordered graphs
For an ordered graph the **elimination process** is the sequence of **v-elimination graph** G<sub>v</sub> defined recursively starting from the original graph G and repeated for n-1 times. The node that is eliminated in each step is chosen based on the order of the graph. 

A **v-elimination graph** G<sub>v</sub> of G is obtained from G by: 

 1.  Adding edges so that all the vertices adjacent to v are pairwise adjacent
 2.  Deleting v and its incident edges

and so this means that the elimination process may add new edges to the graph at each step. 
The set of edges that is added in the whole elimination process is called the **fill-in set** of G<sub>$\alpha$</sub> (written F(G<sub>$\alpha$</sub>)).
The **fill-in set** is strictly related to the graph and the order $\alpha$. 

The **elimination graph** G<sup>*</sup><sub>$\alpha$</sub> is defined starting from graph G and adding the edges present in the fill-in set F(G<sub>$\alpha$</sub>)

G<sup>*</sup><sub>$\alpha$</sub> = ( V, E U F(G<sub>$\alpha$</sub>) ) 

## Elimination orderings
An ordering $\alpha$ is:
 -  a **perfect elimination ordering** of G if the fill-in set of G<sub>$\alpha$</sub> is empty, so during the elimination process the nodes are eliminated following an order that does not introduce any new edges. An ordered graph with a perfect elimination order is called a **perfect elimination graph**.
 - a **minimal ordering** of G if no other ordering $\beta$ satisfies F(G<sub>$\beta$</sub>) C F(G<sub>$\alpha$</sub>).

If a graph is a perfect elimination graph, any minimal ordering is perfect.

**In order to make the elimination process efficient ( reduce the amount of work to be done ), we would like to find an elimination ordering which minimizes the fill-in.** 
The final goal of the paper is to find minimal ordering for any graph and perfect elimination ordering for any perfect elimination graph in reasonable time. This is done using a **lexicographical ordering scheme**, which is a special type of breadth-first search (BFS).

## Lexicographic search
In this kind of search scheme the vertices of the graph are numbered from n to 1. Each vertex has an associated **label**, consisting of a set of numbers selected from {1, ..., n}, ordered in **decreasing** order.
We can define precedence between labels L<sub>1</sub> = {p<sub>1</sub>, ..., p<sub>k</sub>} and  L<sub>2</sub> = {q<sub>1</sub>, ..., q<sub>l</sub>}

 - **L<sub>1</sub> < L<sub>2</sub>** if, for some j, p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., j-1 and p<sub>j</sub> < q<sub>j</sub>, or if p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., j-1  and k < l.
 - **L<sub>1</sub> == L<sub>2</sub>** if k == l and p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., k.

### LEXM and minimal orderings 
This algorithm constructs an ordering $\alpha$ for an unordered graph G. Any order generated with LEXM is called a **lexicographic ordering** and we can prove that **any lexicographic ordering is also a minimal ordering**.


## Perfect elimination order

Alpha is a perfect elimination order for a graph G if the fill-in set for G_alpha is empty.
v ->- w and v ->- x ----> w --- x or w == x

So a perfect elimination order defines the order in which we can eliminate verteces from a graph without adding new edges in the elimination process.

## Minimal elimination order 

An ordering alpha is a minimal elimination order of G if no other ordering beta satisfies F(G_alpha) include in F(G_beta), where the containment is proper.

If a graph is a perfect elimination graph any minimal order is perfect.

## 	BFS and perfect orderings

A BFS applyed to a graph G as the effect of generating a spanning tree of G and to partition the verticies of G into levels.

Each edge joins two vertices on the same level or on adjacent levels. Consider alpha a perfect elimination order for G, a vertex v joined to a vertex w with level(w) = level(v) +1 and to a vertex u with level(u) = level(v) - 1 then alpha^-1(v) > min(alpha^-1(u), alpha^-1(w)), since {u, w} is not an edge of G (because they are not on adjacent levels). This means that for sure v should be eliminated after one of the other two verteces and this also strongly suggest that any perfect elimination order is consistent with the partial ordering of by levels.

The problem is that computing a perfect elimination order with BFS became really complex.

## Lexicograpich search: minimal ordering (lexm)

Special type of BFS.

The verteces of the graph are numbered from n to 1 and during the search each vertex has an associated label. A label is a set of numbers selected from {1 ... n}, ordered in decresing order.

The order is defined using the labels (since we can define when a label L1 is greater or less than a label L2, page 14).

Any order generated by lexm is called a lexicographic ordering. Lexm attenpts to find not only perfect ordering but also minimal ones.

