#include "../../../include/graph.h"
#include "../../../include/lexp.h"
#include <iostream>

int main()
{
	for (int i=1; i<20; ++i)
	{
		Graph g(50*i);
		g.randomPopulate(50 * i, 0.05 * i);
		std::cout << "e: " << g.getEdgeNumber() << '\n';
		graph_algorithms::lexp(g);
	}
}
