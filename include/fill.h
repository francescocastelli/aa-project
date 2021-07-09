#include "graph.h"
#include <algorithm>

namespace graph_algorithms 
{

void fill(Graph &g)
{
	// begin
	int numNodes = g.getNodeNumber();
	std::vector<std::vector<int>> monAdjSets(numNodes);
	std::vector<bool> test(numNodes, false);

	// make a copy of the monAdjSets for every node
	auto nodes = g.getNodeList();
	for (auto const& n: nodes)
	{
		monAdjSets[n] = g.getMonAdjSet(n);
	}

	// loop
	int k, v, size;
	for(int i=0; i<numNodes-1; ++i)
	{
		k = numNodes;
		// get the next node based on the order alpha of g
		v = g.getVertex(i); 

		// dup 
		for (int j=0; j<monAdjSets[v].size(); ++j)
		{
			int w = monAdjSets[v][j];
			int wOrder = g.getOrder(w);
			
			if (test[wOrder]) 	
			{
					monAdjSets[v].erase(monAdjSets[v].begin() + j);
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
		size = monAdjSets[v].size();
		for (int j=0; j<size; ++j)
		{
			int w = monAdjSets[v][j];
			// reset the test vector
			test[g.getOrder(w)] = false;

			// add w to the monotonely adj set of m, the one with the minimum order
			// lemma 4 page 11
			if (w != m) 
			{
				monAdjSets[m].push_back(w);
			}
		}
	}
	
	for (auto const& n: nodes)
	{
		auto originalAdj = g.getMonAdjSet(n);
		for (int j=0; j<monAdjSets[n].size(); ++j)
		{   
			int w = monAdjSets[n][j];
			int originalCount = std::count(originalAdj.begin(), originalAdj.end(), w);

			if (originalCount == 0)
				g.addEdge(n, w);
		}
	}
}
} // namespace graph_algorithms
