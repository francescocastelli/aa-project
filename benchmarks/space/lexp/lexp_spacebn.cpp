#include "../../../include/graph.h"
#include "../../../include/lexp.h"

int main()
{
	for (int i=1; i<20; ++i)
	{
		Graph g;
		g.randomPopulate(50 * i, i+1, 0);
		graph_algorithms::lexp(g);
	}
}
