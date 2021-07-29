#include "../../../include/graph.h"
#include "../../../include/fill.h"
#include <iostream>

int main()
{

	for (int i=1; i<20; ++i)
	{
		Graph g(50*i);
		g.randomPopulate(50 * i, 0.05 * i);

		// create random order for the nodes
		auto order = std::move(g.getNodeList());
		std::random_shuffle(order.begin(), order.end());
		g.setOrder(order);

		auto monAdjSet = std::move(g.computeMonAdjSet());
		int fillCount = 0;

		graph_algorithms::fill(g, std::move(monAdjSet), false, fillCount);
		std::cout << "e': " << g.getEdgeNumber() + fillCount << '\n';
	}
}
