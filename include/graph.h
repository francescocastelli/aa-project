#include <vector>
#include <map>
#include <iostream>

class Graph 
{
	Graph (int num_verteces) : num_verteces (num_verteces) 
	{
		// initialize with empty lists of edges each vertex
		for(int i=0; i<num_verteces; ++i)
			test.insert({i, std::vector<int>()});
	};

	Graph (const Graph&) = delete;
	Graph (Graph&&) = default;

	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = default;

	~Graph() = default;

	// num_edges is the maximum number of edges per vertex
	void populateGraph(int maxNumEdges)
	{
		for (int i=0; i<num_verteces; ++i)
		{
			std::vector<int> edges; 
			
			// generate edges at random 
			for (int j=0; j<maxNumEdges; ++j)
			{
				int edge = randomEdge(); 
				if (edge != i) edges.push_back(edge);
			}

			// add verteces in edges to vertex i vector and 
			// add vertex i to all the verteces vectors in edges
			for (int j=0; j<edges.size(); ++j)
			{
				graph[edges[j]].push_back(i);
				graph[i].push_back(edges[j]);
			}
		}
	}

	void printGraph()
	{
		for (int i=0; i<num_verteces; ++i)
		{
			std::cout << "v: " << i;
			for (int j=0; j<test[i].size(); ++j)
				std::cout <<  "  edges: " << test[i][j];

			std::cout << '\n';
		}
	}

    int randomEdge()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, num_verteces-1);

        return dist(rng);
    }

private: 
	using graphTy = std::map<int, std::vector<int>>;

	int num_verteces;
	graphTy graph;
};

