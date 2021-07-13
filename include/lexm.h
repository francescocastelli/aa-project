#include "graph.h"


namespace graph_algorithms 
{

int _counting_sort(std::vector<uint32_t> &a, int digitIndex)
{
	std::vector<uint32_t> b (a.size(), 0);
	//always 10 bc we consider one digit at the time
	std::vector<int> c (10, 0); 
	
	for (auto i : a)
		c[(i/digitIndex) % 10]+=1;

	for (auto i = 1; i<10; ++i)
		c[i] += c[i-1];

	for (int i = b.size()-1; i>=0; --i)
	{
		b[c[(a[i]/digitIndex) % 10]-1] = a[i];
		--c[(a[i]/digitIndex) % 10];
	}

	a = std::move(b);
	return 0;
}

int _numDigits(int number)
{
	int digits = 0;
	if (number < 0) digits = 1; 
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

int _radix_sort(std::vector<uint32_t> &v)
{
   int max = *std::max_element(v.begin(), v.end());
   int digitNum = _numDigits(max);
   int digitIndex = 1;

   for (auto i = 1; i <= digitNum; ++i)
   {
		_counting_sort(v, digitIndex);        
		digitIndex *= 10;
   }

   return 0;
}

void lexm(Graph &g)
{

	int numNodes = g.getNodeNumber();
	auto nodes = g.getNodeList();

	// map of labels, each vertex as an integer associated
	//std::map<int, float> l;
	// reach is indexed by labels
	std::map<int, std::vector<int>> reach;
	std::vector<float> unnumbered;
	std::map<int, bool> unreached;

	std::vector<int> order (numNodes);
	std::map<int, int> inverseOrder;

	// begin 
	for (auto const& n : nodes)
	{
		//l[n] = 1.0f;
		inverseOrder[n] = 0;
		unnumbered.push_back(1.0f);
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
		for (int j=0; j<k; ++j)
			reach[j].clear();

		// mark all the unnumbered vertices unreached
		for (auto const& n : unnumbered)
			unreached[n] = true;

		for (auto const& w : g.getAdjSet(v))
			// check that w is unnumbered
			if (inverseOrder[w] == 0)
			{
				reach[unnumbered[w]].push_back(w);
				// mark w reached
				unreached[w] = false;

				unnumbered[w]  = unnumbered[w] + 0.5f;
				// mark v, w as edge on g*
			}

		// search
		for (int j=k-1; j>=0; --j)
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
						if (unnumbered[z] < j) 
						{
							reach[unnumbered[z]].push_back(z);
							unnumbered[z]  = unnumbered[z] + 0.5f;
							// mark v, z as an edge of g*
						}
						else reach[j].push_back(z);
					}
			}

		// sort
		std::vector<uint32_t> radixLabels(unnumbered.begin(), unnumbered.end());
		_radix_sort(radixLabels);
		for (int j=0; j<radixLabels.size(); ++j)
			unnumbered[j] = (float)radixLabels[j];
	}




}



} // namespace graph_algorithms
