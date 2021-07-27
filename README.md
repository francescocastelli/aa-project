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
The set of edges that is added in the whole elimination process is called the **fill-in set** of G<sub>α</sub> (written F(G<sub>α</sub>)).
The **fill-in set** is strictly related to the graph and the order α. 

The **elimination graph** G<sup>*</sup><sub>α</sub> is defined starting from graph G and adding the edges present in the fill-in set F(G<sub>α</sub>)

G<sup>*</sup><sub>α</sub> = ( V, E U F(G<sub>α</sub>) ) 

## Elimination orderings
An ordering α is:
 -  a **perfect elimination ordering** of G if the fill-in set of G<sub>α</sub> is empty, so during the elimination process the nodes are eliminated following an order that does not introduce any new edges. An ordered graph with a perfect elimination order is called a **perfect elimination graph**.
 - a **minimal ordering** of G if no other ordering β satisfies F(G<sub>β</sub>) C F(G<sub>α</sub>).

If a graph is a perfect elimination graph, any minimal ordering is perfect.

**In order to make the elimination process efficient ( reduce the amount of work to be done ), we would like to find an elimination ordering which minimizes the fill-in.** 
The final goal of the paper is to find minimal ordering for any graph and perfect elimination ordering for any perfect elimination graph in reasonable time. This is done using a **lexicographical ordering scheme**, which is a special type of breadth-first search (BFS).

## Lexicographic search
In this kind of search scheme the vertices of the graph are numbered from n to 1. Each vertex has an associated **label**, consisting of a set of numbers selected from {1, ..., n}, ordered in **decreasing** order.
We can define precedence between labels L<sub>1</sub> = {p<sub>1</sub>, ..., p<sub>k</sub>} and  L<sub>2</sub> = {q<sub>1</sub>, ..., q<sub>l</sub>}

 - **L<sub>1</sub> < L<sub>2</sub>** if, for some j, p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., j-1 and p<sub>j</sub> < q<sub>j</sub>, or if p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., j-1  and k < l.
 - **L<sub>1</sub> == L<sub>2</sub>** if k == l and p<sub>i</sub> == q<sub>i</sub> for i = 1, ..., k.

### LEXM and minimal orderings

This algorithm constructs an ordering α for an unordered graph G. Any order generated with LEXM is called a **lexicographic ordering** and can be proved that **any lexicographic ordering is also a minimal ordering**.

Pseudo-algorithm: 

 1.  Assign the empty label to all nodes
 2. For i = n step -1 until 1
	 2a. Select an unnumbered vertex with largest label 
	 2b. Assign to v the order i
	 2c. Update (see below)

The algorithm starts by setting to all the vertices the empty label. Then it iterates from n to 1 (this defines the order) and select the current vertex v as the one with the largest label among the vertices with no order yet assigned. The current loop step defines the order of the vertex v, and then we perform the update operation. 

#### Update:
  The update goal is to find all the vertices **w** such that there is a **chain** between the current vertex v and w itself with the current properties: 
  

 - **All the vertices of the chain are unnumbered** 
 - **All the vertices of the chain have a label which is less than the label of w**
 
 and **add** the order of v to the **label of w**.

This condition is necessary since we are trying to find minimal ordering, not just perfect ones, and so there may be fill-in edges. From Lemma 6, pag. 16, we know that if α is a lexicographical ordering of G, then in the elimination graph the label of a vertex correspond to the order of the vertices in its monotonely adjacent set. The goal of update is to add the order of v to all the w connected with the previously defined chain, and so adding v to the monotonely adjacent set of w in the final elimination graph.

#### Implementation
The idea is to associate to each vertex v an integer number l(v) that represent its label, such that l(v) == l(w) means that v and w have the same label and l(v) < l(w) means that the label of v is less than the label of w. These integer are number between 1 and k, where k is the number of distinct labels.
The unnumbered vertices are kept in labels order, and at each step we select the vertex with highest label. 
First the search goes through the adjacent set of the current selected vertex, and update their labels since they met the condition of update. Then we extend the search to second highest label, and so on.

#### Asymptotic analysis
In the implementation of LEXM we are sure that each vertex is examined only once per search, leading to a searching time of O(e). The search is execute for n times, thus:

**Time complexity**: O( n * e ), where n is the number of nodes and e is the number of edges of G.
**Space complexity**: O( n + e )

### LEXP and perfect orderings
This algorithm will generate a perfect ordering $\alpha$ for a graph G, if G has any perfect orderings. Otherwise is not guaranteed that $\alpha$ will be even minimal. 

Pseudo-algorithm: 

 1. Assign the empty label to all nodes
 2. For i = n step -1 until 1\
	 2a. Select an unnumbered vertex with largest label\ 
	 2b. Assign to v the order i\
	 2c. Update2 (see below)\

A very efficient implementation can be found by modifying the update statement of LEXM by observing that if G is perfect and $\alpha$ is a lexicographical ordering, then the **fill-in set of G is empty,** and by Lemma 6, pag. 18, we know that the labels of a vertex in the final graph can be simply found from the monotonely adjacent set of the vertex itself. 

#### Update2:
Since we assume that the graph has a perfect elimination order, we can also assume that no fill-in edges are present. Thus update became really simple: 
**For each unnumbered vertex w adjacent to v, add the order of v to label of w**

#### Implementation

#### Asymptotic analysis

**Time complexity**: O( n + e ), where n is the number of nodes and e is the number of edges of G.\
**Space complexity**: O( n + e )

### FILL

Algorithm FILL can be used to compute the fill-in edges of a graph, given a particular ordering.

Pseudo-algorithm: 

 1. For i = 1 step 1 until n-1:\ 
	 2a. Select the current vertex v based on the order\ 
	 2b. Selected the vertex m(v) with the minimum order among the monotonely adjacent set of v\
	 2c. For all w that are monotonely adjacent to v and different from m(v):\
		 3.a Add w to the monotonely adjacent set of m(v)\

This algorithm correctly computes the edges of the perfect elimination graph thanks to Lemma 4, pag. 11
#### Lemma 4


#### Implementation
The only thing that we have to ensure in order to make the implementation of FILL efficient is that the monotely adjacent list of a vertex should not contains too many redundant elements. This is done by looping through the adjacent set of v when computing the minimum and deleting duplicates.

#### Asymptotic analysis

Each time we execute statement 2.c, we are sure that the monotonely adjacent list of v is free of redundancies, thus the number of vertices added by statement 3.a is bounded by the size of the monotonely adjacent set of v. The total number of additions over all iterations of the loop is thus bounded by the number of edges of the final graph G<sup>*</sup>, leading to this complexities:

**Time complexity**: O( n + e' ), where n is the number of nodes and e' is the number of edges of G<sup>*</sup>.\
**Space complexity**: O( n + e' )
