#include <vector>
#include <map>

class Graph 
{
	using edgeListTy = std::vector<int>;

private:

	struct nodeInfo 
	{
		// each vertex in edges indicates the 2nd vertex of the edge
		// i ---- j   means graph[i].edges contains j
		edgeListTy edges; 
		// monotonic adj set for the vertex
		edgeListTy monAdjSet;
	};

public:
	Graph (int num_verteces);

	Graph (const Graph&) = delete;
	Graph (Graph&&) = default;

	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = default;

	~Graph() = default;

	// returns only the list of edges adj to the vertex
	const edgeListTy& operator[](int vertex); 
	const edgeListTy& getEdges(int vertex);

	// returns the monotonic adjacent set of the vertex
	const edgeListTy& getMonotonicAdjSet(int vertex);

	// num_edges is the maximum number of edges per vertex
	void populateGraph(int maxNumEdges);

	// get the vertex based on the order (this is a) 
	int getVertex(int orderIdx);

	// get the order based on the vertex (this is a^-1) 
	int getOrder(int vertex);

	// get entire order list 
	const edgeListTy& getOrder();

	void printGraph();

	// ----------------- requested methods -----------------
	
	void fill();

private: 
	using graphTy = std::map<int, nodeInfo>;

	int num_verteces;
	graphTy graph;
	edgeListTy order;

	// ------------------ private methods ------------------
	
    int randomEdge();
	edgeListTy computeMonAdjSet(int vertex);
};

