#include "../include/graph.h"

void Graph::fill(Graph g)
{
	// begin
	int numNodes = g.getNumNodes();
	std::vector<std::vector<int>> monAdjSets;
	std::vector<bool> test(numNodes, false);
	int k, v, size;

	for (int i=0; i<numNodes-1; ++i)
		monAdjSets[i] = g.getMonAdjSet(i);

	// loop
	for(int i=0; i<numNodes-1; ++i)
	{
		k = numNodes;
		v = g.getVertex(i); 

		// dup 
		for (int j=0; j<monAdjSets[v].size(); ++j)
		{
			int w = monAdjSets[v][j];
			int wOrder = g.getOrder(w);
			
			if (test[wOrder]) 	
			{
				auto it = std::find(monAdjSets[v].begin(), monAdjSets[v].end(), w);
				if (it != monAdjSets[v].end()) 
				{
					std::swap(*it, monAdjSets[v].back());
					monAdjSets[v].pop_back();
					--j;
				}
			}
			else
			{
				test[wOrder] = true;
				k = std::min(k, wOrder);
			}
		}

		int m = g.getVertex(k);

		// add 
		size = monAdjSets[v].size();
		for (int j=0; j<size; ++j)
		{
			int w = monAdjSets[v][j];
			test[getOrder(w)] = false;

			if (w != m) 
			{
				monAdjSets[v].push_back(w);
				monAdjSets[v].push_back(w);
			}
		}
	}
	
	//TODO: add all the new fill-in edges to the graph g
}
