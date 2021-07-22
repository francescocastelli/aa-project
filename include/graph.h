#pragma once
#include <vector>
#include <map>
#include <unordered_map>

class Graph 
{
	using nodeListTy = std::vector<int>;

private:

	struct nodeInfo 
	{
		// each vertex in adjSet indicates the 2nd vertex of the edge
		// i ---- j   means graph[i].adjSet contains j
		nodeListTy adjSet; 
	};

public:
	Graph ();

	Graph (const Graph&) = delete;
	Graph (Graph&&) = default;

	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = default;

	~Graph() = default;

	// add a new edge btw n1 and n2 
	// if one of the nodes is not present, it will be inserted
	void addEdge(int n1, int n2);

	// add a new node with no edges
	void addNode(int n);

	void removeNode(int n);

	void removeEdge(int n1, int n2);

	int getNodeNumber() const;

	int getEdgeNumber() const;

	// num_edges is the maximum number of edges per vertex
	void randomPopulate(int numNodes, int maxNumEdges, int seed = -1);

	nodeListTy getNodeList() const;

	// get the vertex based on the order (this is a) 
	int getVertex(int orderIdx) const;

	// get the order based on the vertex (this is a^-1) 
	int getOrder(int vertex) const;

	// get entire order list 
	nodeListTy getOrder() const;

	// get the adjacent list of node n
	nodeListTy getAdjSet(int n) const;

	std::map<int, nodeListTy> computeMonAdjSet() const;

	nodeListTy computeMonAdjSet(int n) const;

	// take in input a map of monotonely adj set and 
	// computes the difference wrt to ones of the current graph
	// then add the new edges
	void addNewEdges(std::map<int, nodeListTy> monAdjSet);

	int countNewEdges(std::map<int, nodeListTy> monAdjSet);

	void setOrder(nodeListTy order);

	void reset();

	void printGraph() const;

private: 
	using graphTy = std::unordered_map<int, nodeInfo>;

	int numNodes;
	int numEdges;
	// nodeList 
	nodeListTy nodeList;
	// actual graph
	graphTy graph;
	// alpha
	nodeListTy order;
	// alpha^-1
	std::unordered_map<int, int> inverseOrder;

	// ------------------ private methods ------------------
	
    int randomNode(int min, int max, int seed);
};

