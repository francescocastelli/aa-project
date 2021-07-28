#pragma once
#include <vector>
#include <map>
#include <unordered_map>

class Graph 
{
	using nodeListTy = std::vector<int>;
	using setTy = std::unordered_map<int, nodeListTy>;

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


	void removeEdge(int n1, int n2);

	// create a random undirected and connected graph
	// number of nodes = numNodes
	// edges are generated by sampling a number p from a uniform distribution btw 0-1
	// if p is less than q than the edges is added
	// q defines the density of the graph
	void randomPopulate(int numNodes, float q);

	// compute the monotonely adjacent set for each node
	// return a map containing all the info
	setTy computeMonAdjSet() const;

	// compute the monotonely adjacent set for the specified node n
	nodeListTy computeMonAdjSet(int n) const;

	// take in input a map of monotonely adj set and 
	// computes the difference wrt to ones of the current graph
	// then add the new edges
	void addNewEdges(setTy monAdjSet);

	// take in input a map of monotonely adj set and 
	// computes the difference wrt to ones of the current graph
	// return the number of nodes that will be added
	int countNewEdges(setTy monAdjSet);

	void setOrder(nodeListTy order);

	void reset();

	void printGraph() const;

	// ------------------------------------------------------------------------------------ 

	int getNodeNumber() const;

	int getEdgeNumber() const;

	nodeListTy getNodeList() const;

	// get the vertex based on the order (this is a) 
	int getVertex(int orderIdx) const;

	// get the order based on the vertex (this is a^-1) 
	int getOrder(int vertex) const;

	// get entire order list 
	nodeListTy getOrder() const;

	// get the adjacent list of node n
	const nodeListTy& getAdjSet(int n) const;

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
	
	float uniformProb();
	// add and remove new node 
	void _addNode(int n);
	void _removeNode(int n);
};

