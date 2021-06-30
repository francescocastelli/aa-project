#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <algorithm>

class Graph 
{
private: 
	using graphTy = std::map<int, std::vector<int>>;
	using orderTy = std::vector<int>;

public:

	Graph (int num_verteces) : num_verteces (num_verteces), 
							   order(num_verteces)
	{
		// initialize with empty lists of edges each vertex
		for(int i=0; i<num_verteces; ++i)
			graph.insert({i, std::vector<int>()});

		// random order of verteces from 0 to num_verteces
		std::iota(order.begin(), order.end(), 0);
		std::random_shuffle(order.begin(), order.end());
	};

	Graph (const Graph&) = delete;
	Graph (Graph&&) = default;

	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = default;

	~Graph() = default;

	// operators overloading 
	const std::vector<int>& operator[](int vertex) { return graph[vertex]; }

	// num_edges is the maximum number of edges per vertex
	void populateGraph(int maxNumEdges)
	{
		for (int i=0; i<num_verteces; ++i)
		{
			// generate edges at random 
			for (int j=0; j<maxNumEdges; ++j)
			{
				int edge = randomEdge(); 
				if (edge != i && std::count(graph[i].begin(), graph[i].end(), edge) == 0)
					graph[i].push_back(edge);
			}

			// add vertex i to all the verteces vectors in graph[i] 
			for (int j=0; j<graph[i].size(); ++j)
			{
				if (std::count(graph[graph[i][j]].begin(), graph[graph[i][j]].end(), i) == 0)
					graph[graph[i][j]].push_back(i);
			}
		}
	}

	// get the vertex based on the order (this is a) 
	int getVertex(int orderIdx) 
	{
		return order[orderIdx];	
	}

	const orderTy& getOrder()
	{
		return order;
	}

	// get the order based on the vertex (this is a^-1) 
	int getOrder(int vertex) 
	{
		auto it = std::find(order.begin(), order.end(), vertex);
		return std::distance(order.begin(), it); 
	}


	std::vector<int> getMonotonicAdj(int vertex)
	{
		std::vector<int> mAdj;

		for (int i=0; i<graph[vertex].size(); ++i)
			if (getOrder(vertex) < getOrder(graph[vertex][i])) 
				mAdj.push_back(graph[vertex][i]);
		
		return mAdj;
	}

	void printGraph()
	{
		for (int i=0; i<num_verteces; ++i)
		{
			std::cout << "v: " << i;
			for (int j=0; j<graph[i].size(); ++j)
				std::cout <<  "  edges: " << graph[i][j];

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

	int num_verteces;
	graphTy graph;
	orderTy order;
};

