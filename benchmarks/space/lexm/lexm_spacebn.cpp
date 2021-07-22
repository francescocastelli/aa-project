#include "../../../include/graph.h"
#include "../../../include/lexm.h"
#include <iostream>

int main()
{
	for (int i=1; i<20; ++i)
	{
		Graph g;
		g.randomPopulate(50 * i, i+1, 0);
		graph_algorithms::lexm(g);
	}
}
