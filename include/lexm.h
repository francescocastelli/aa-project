#include "graph.h"
#include <algorithm>
#include <math.h>
#include <unordered_map>

namespace graph_algorithms 
{

void lexm(Graph &g)
{
	int numNodes = g.getNodeNumber();
	auto nodes = g.getNodeList();

	// reach is indexed by labels
	std::unordered_map<int, std::vector<int>> reach;
	// vector of nodes, always ordered in increasing order 
	std::vector<int> unnumbered;
	// map of labels, indexed by nodes
	std::unordered_map<int, float> labels;

	std::map<int, bool> unreached;

	std::vector<int> order (numNodes);
	std::unordered_map<int, int> inverseOrder;

	// begin 
	for (auto const& n : nodes)
	{
		labels[n] = 1.0f;
		inverseOrder[n] = 0;
		unnumbered.push_back(n);
		unreached[n] = true;
	}

	// k is the number of distinct labels
	int k = 1;

	// loop
	for (int i=numNodes-1; i>=0; --i)
	{
		// select an unnumbered vertex v with l(v) = k
		// so we select the vertex with the highest label
		// keep unnumbered order by labels in incresing order
		int v = unnumbered.back();
 		unnumbered.pop_back();

		// assign v the number i
		order[i] = v;
		inverseOrder[v] = i;
		unreached[v] = false;

		// we need to do this because we are searching for a chain like
		// [v, v2, ..., v_k+1 = w] with vj unnumbered and l(vj) < l(w) for j=2,...,k
		for (int j=1; j<=k; ++j)
			reach[j].clear();

		// mark all the unnumbered vertices unreached
		for (auto const& n : unnumbered)
			unreached[n] = true;

		for (auto const& w : g.getAdjSet(v))
			// check that w is unnumbered
			if (inverseOrder[w] == 0)
			{
				reach[labels[w]].push_back(w);
				// mark w reached
				unreached[w] = false;

				labels[w]  = labels[w] + 0.5f;
				// mark v, w as edge on g*
			}

		// search
		for (int j=1; j<=k; ++j)
			while (!reach[j].empty())
			{
				// delete a vertex w from reach(k)
				int w = reach[j].back();
				reach[j].pop_back();

				for(auto const& z : g.getAdjSet(w))
					if (unreached[z])
					{
						// mark z reached
						unreached[z] = false;
						if (labels[z] > j) 
						{
							reach[labels[z]].push_back(z);
							labels[z]  = labels[z] + 0.5f;
							// mark v, z as an edge of g*
						}
						else reach[j].push_back(z);
					}
			}
		// end search
		// sort
		std::sort(unnumbered.begin(), unnumbered.end(), 
				  [&labels](const int &l, const int &r) 
				  {
				  		return labels[l] < labels[r];
				  });

		// reassign l(w) values to be integers from 1 to k, redefining k appropriately
		std::map<float, std::vector<int>> bins;
		for (auto const& n: unnumbered)
		{
			float l = labels[n];
			bins[l].push_back(n);
		}

		// set the new k
		k = bins.size();

		// set the new labels
		// the cycles below iterate over all the unnumbered verteces, 
		// complexity is linear in the number of them 
		float count = 1.0f;
		for (auto const& b: bins)
		{
			for(auto const& n: b.second)
				labels[n] = count;

			++count;
		}
	}

	g.setOrder(order);
}
} // namespace graph_algorithms
