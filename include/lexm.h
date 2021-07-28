#include "graph.h"
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <map>

namespace graph_algorithms 
{

/*  parameters :
 * 		graph g, the graph on which we apply lexm 
 * 
 * 	pseudo-code: 
 *
 * 		lexm algorithm is applyed to a graph with no order to compute a minimal order. Any 
 * 		ordering generated with lexm is a lexicographic order.
 *
 * 		lexm tries to find minimal ordering, not just perfect ordering, and this implies 
 * 		that there may be fill-in edges, making the label updating more complicated.
 *
 * 		1. assign to all nodes the empty label 
 * 		2. loop from n to 1 (this defines the order) 
 *         2.a get an unnumbered node with largest label (v)
 *         2.b assign to this node the current order 
 *         2.c update 
 *  
 *  	update: 
 *  		update should find all the chains of nodes from v to w, where all the nodes
 *  		in the chain are unnumbered and the corresponding labels are less than the 
 *  		label of w. Once all the w that respect this condition are found, we should 
 *  		add the current order index to the label of w.
 *
 *  		This is implemented by keeping all the verteces ordered by labels, and pick 
 *  		every time a vertex with the highest label value (v). 
 *  		First the search is applyed to the adj nodes of v, and then extended through
 *  		vertices of second highest label and so on. 
 *  		The chain of verteces is found because we go through reach from 1 to k, 
 *  		and in this way we get all the verteces with lowest labels first.
 *  		For every nodes that is connected with a rigth chain with v, we increase the 
 *  		label.
 *
 *  Complexity:
 *  	n is the number of nodes 
 *  	e is the total number of edges of g
 *
 *  	time complexity: O(n * e)
 *  	space complexity: O(n + e)
 */
void lexm(Graph &g)
{
	int numNodes = g.getNodeNumber();
	auto nodes = std::move(g.getNodeList());

	// reach is indexed by labels
	std::unordered_map<int, std::vector<int>> reach;
	// set of labels, indexed by nodes
	std::vector<float> labels (numNodes);

	// vector of nodes, always ordered in increasing orderde of labels
	std::vector<int> unnumbered;
	std::vector<bool> unreached (numNodes);

	// order 
	std::vector<int> order (numNodes);
	std::vector<int> inverseOrder (numNodes);

	// cache 
	std::unordered_map<int, std::vector<int>> cache;

	// begin 
	unnumbered.reserve(numNodes);
	for (auto const& n : nodes)
	{
		labels[n] = 1.0f;
		inverseOrder[n] = 0;
		unreached[n] = true;
		unnumbered.emplace_back(n);
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

		// first level search
		for (auto const& w : g.getAdjSet(v))
			// check that w is unnumbered
			if (inverseOrder[w] == 0)
			{
				reach[labels[w]].push_back(w);
				// mark w reached
				unreached[w] = false;

				labels[w] = labels[w] + 0.5f;
				// mark v, w as edge on g*
			}

		// search
		for (int j=1; j<=k; ++j)
		{
			auto& reachJ = reach[j];
			while (!reachJ.empty())
			{
				// delete a vertex w from reach(k)
				int w = reachJ.back();
				reachJ.pop_back();

				if (!cache.contains(w)) cache[w] = std::move(g.getAdjSet(w));

				for(auto const& z : cache[w])
				{
					if (unreached[z])
					{
						// mark z reached
						unreached[z] = false;
						if (labels[z] > j) 
						{
							reach[labels[z]].push_back(z);
							labels[z] = labels[z] + 0.5f;
							// mark v, z as an edge of g*
						}
						else reachJ.push_back(z);
					}
				}
			}
		} // end search

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
