#include "graph.h"
#include <algorithm>

namespace graph_algorithms 
{

std::map<int, std::vector<int>> fill(const Graph& g, std::map<int, std::vector<int>> monAdjSetP)
{
	// begin
	auto monAdjSet = std::move(monAdjSetP);

	int numNodes = g.getNodeNumber();
	std::vector<bool> test(numNodes, false);
	auto nodes = std::move(g.getNodeList());

	// loop
	int k, v, size;
	for(int i=0; i<numNodes-1; ++i)
	{
		k = numNodes;
		// get the next node based on the order alpha of g
		v = g.getVertex(i); 

		// dup 
		for (int j=0; j<monAdjSet[v].size(); ++j)
		{
			int w = monAdjSet[v][j];
			int wOrder = g.getOrder(w);
			
			if (test[wOrder]) 	
			{
				std::swap(monAdjSet[v][j], monAdjSet[v].back());
				monAdjSet[v].pop_back();
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

		// add 
		size = monAdjSet[v].size();
		for (int j=0; j<size; ++j)
		{
			int w = monAdjSet[v][j];
			// reset the test vector
			test[g.getOrder(w)] = false;

			// add w to the monotonely adj set of m, the one with the minimum order
			// lemma 4 page 11
			if (w != m) 
			{
				monAdjSet[m].push_back(w);
			}
		}
	}
	
	return monAdjSet;
}
} // namespace graph_algorithms
