#include "graph.h"
#include <algorithm>

namespace graph_algorithms 
{

/* parameters :
 * 		graph g, the graph on which we apply fill 
 * 		monAdjSetP, map that contains all the monotonely adj sets for each node of the graph g 
 * 
 * return : 
 *		map that contains the new monotonely adj sets for each node, after fill algorithm is 
 *		applyed
 *
 * 	pseudo-code: 
 *
 * 		The fill algorithm can be used on graph with an order already set, and it will compute
 * 		the fill-in set of this graph.
 *
 * 		1. loop over the order (from 1 to n-1) and get the current vertex v
 *         1.a get the node with minimum oder among the monotonely adj nodes of v (called m) 
 *         2.a add all the nodes in the monAdjSet of v to the monAdjSet of m 
 *  
 *  	In oder to make fill fast, the dup loop is added in this implementation. This loop is 
 *  	responsible for deleting all the duplicates in the monAdjSets so that they will not 
 *  	contains to many redundant elements
 *
 *  Complexity:
 *  	n is the number of nodes 
 *  	e' is the total number of edges of the elimination graph of g (g*)
 *
 *  	time complexity: O(n+e')
 */
void fill(Graph& g, std::unordered_map<int, std::vector<int>> monAdjSetP)
{
	// begin
	auto monAdjSet = std::move(monAdjSetP);

	int numNodes = g.getNodeNumber();
	std::vector<bool> test(numNodes, false);

	// loop
	int k, v, size;
	for(int i=0; i<numNodes-1; ++i)
	{
		k = numNodes;
		// get the next node based on the order alpha of g
		v = g.getVertex(i); 

		// dup 
		auto& monAdjSetV = monAdjSet[v];
		for (int j=0; j<monAdjSetV.size(); ++j)
		{
			int w = monAdjSetV[j];
			int wOrder = g.getOrder(w);
			
			if (test[wOrder]) 	
			{
				std::swap(monAdjSetV[j], monAdjSetV.back());
				monAdjSetV.pop_back();
				--j;
			}
			else
			{
				test[wOrder] = true;
				k = std::min(k, wOrder);
			}
		}

		// get the node that corresponds to the order k
		// m is the node with minimum order among the monotonely adj nodes of v
		int m = g.getVertex(k);
		auto& monAdjSetM = monAdjSet[m];

		// add 
		size = monAdjSetV.size();
		for (int j=0; j<size; ++j)
		{
			int w = monAdjSetV[j];
			// reset the test vector
			test[g.getOrder(w)] = false;

			// add w to the monotonely adj set of m, the one with the minimum order
			// lemma 4 page 11
			if (w != m) 
			{
				monAdjSetM.push_back(w);
			}
		}

		// at this point monAdjSet of the current v will never be accessed again 
		// since all the next vertices have an order which is greater than v
		g.addFillInEdges(v, std::move(monAdjSetV));
	}
}
} // namespace graph_algorithms
