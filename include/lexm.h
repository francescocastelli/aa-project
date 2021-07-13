#include "graph.h"


namespace graph_algorithms 
{

void lexm(Graph &g)
{

	int numNodes = g.getNodeNumber();
	auto nodes = g.getNodeList();

	// map of labels, each vertex as an integer associated
	std::map<int, int> l;
	std::map<int, std::vector<int>> reach;
	std::vector<int> unnumbered;
	std::map<int, bool> unreached;

	std::array<int> order (numNodes);
	std::map<int, int> inverseOrder;

	// begin 
	for (auto const& n : nodes)
	{
		l[n] = 1;
		inverseOrder[n] = 0;
		unnumbered.push_back(n);
		unreached[n] = true;
	}

	int k = 1;

	// loop
	for (int i=numNodes-1; i>=0; --i)
	{
		// select an unnumbered vertex v with l(v) = k
		int v = unnumbered.back();
 		unnumbered.pop_back();

		// assign v the number i
		order[i] = v;
		inverseOrder[v] = i;

		for (int j=0; j<k; ++j)
			reach[j].clear();

		// mark all the unnumbered vertices unreached
		for (auto const& n : unnumbered)
			unreached[n] = true;

		for (auto const& w : g.getAdjSet(v))
			if (inverseOrder(w) == 0)
			{
				reach[l[w]].push_back(w);
				// mark w reached
				unreached[n] = false;

				l[w]  = l[w] + 0.5;
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
						if (l[z] < k) 
						{
							reach[l[z]].push_back(z);
							l[z] = l[z] + 0.5;
							// mark v, z as an edge of g*
						}
						else reach[k].push_back(z);
					}
			}

		// sort


	}




}

int _radix_sort(std::vector<int> &v)
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

int _counting_sort(std::vector<int> &a, int digitIndex)
{
	std::vector<int> b (a.size(), 0);
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


} // namespace graph_algorithms
