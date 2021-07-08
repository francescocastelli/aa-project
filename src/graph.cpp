#include "../include/graph.h"
#include <random>
#include <iostream>
#include <algorithm>

Graph::Graph() : numNodes (0)
{
}

void Graph::addNode(int n)
{
	graph.insert({n, {nodeListTy()}});
	++numNodes;
}

int Graph::getNodeNumber()
{
	return numNodes;
}

void Graph::addEdge(int n1, int n2)
{
	if (graph.count(n1) == 0) {++numNodes; addNode(n1);}
	if (graph.count(n2) == 0) {++numNodes; addNode(n2);}

	graph[n1].adjSet.push_back(n2);
	graph[n2].adjSet.push_back(n1);
}

// num_edges is the maximum number of edges per vertex
void Graph::randomPopulate(int numNodes, int maxNumEdges)
{
	// add nodes from 0 to numNodes
	for (int i=0; i<numNodes; ++i)
		addNode(i);

	// generate edges at random for each node i
	for (int i=0; i<numNodes; ++i)
		for (int j=0; j<maxNumEdges; ++j)
		{
			int node = randomNode(0, numNodes-1); 
			int nodeCount = std::count(graph[i].adjSet.begin(), graph[i].adjSet.end(), node);

			if (node != i && nodeCount == 0)
				addEdge(i, node);
		}
	
	// delete disconnected nodes
	for (int i=0; i<numNodes; ++i)
		if (graph[i].adjSet.size() == 0)
		{
			graph.erase(i);
			--numNodes;
		}
}

// get the vertex based on the order (this is a) 
int Graph::getVertex(int orderIdx) 
{
	return order[orderIdx];	
}

// get the order based on the vertex (this is a^-1) 
int Graph::getOrder(int vertex) 
{
	auto it = std::find(order.begin(), order.end(), vertex);
	return std::distance(order.begin(), it); 
}

const Graph::nodeListTy& Graph::getOrder()
{
	return order;
}

Graph::nodeListTy Graph::getNodeList()
{
	nodeListTy nodeList;

	for(auto const& k: graph)
		nodeList.push_back(k.first);

	return nodeList;
}

Graph::nodeListTy Graph::getAdjSet(int n)
{
	return graph[n].adjSet;
}

Graph::nodeListTy Graph::getMonAdjSet(int n)
{
	nodeListTy mAdj;

	for (int i=0; i<graph[n].adjSet.size(); ++i)
		if (getOrder(n) < getOrder(graph[n].adjSet[i])) 
			mAdj.push_back(graph[n].adjSet[i]);
	
	return mAdj;
}

void Graph::printGraph()
{
	for (int i=0; i<numNodes; ++i)
	{
		std::cout << "v: " << i << '\n';
		std::cout << "	edges: ";
		for (int j=0; j<graph[i].adjSet.size(); ++j)
			std::cout <<  " [" << graph[i].adjSet[j] << "] ";

		std::cout << "\n";
	}
}

int Graph::randomNode(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

	return dist(rng);
}

