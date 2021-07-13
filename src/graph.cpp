#include "../include/graph.h"
#include <random>
#include <iostream>
#include <algorithm>

Graph::Graph() : numNodes (0), numEdges(0)
{
}

void Graph::addNode(int n)
{
	graph.insert({n, {nodeListTy()}});
	nodeList.push_back(n);
	++numNodes;
}

void Graph::addEdge(int n1, int n2)
{
	if (graph.count(n1) == 0) {++numNodes; addNode(n1);}
	if (graph.count(n2) == 0) {++numNodes; addNode(n2);}

	graph[n1].adjSet.push_back(n2);
	graph[n2].adjSet.push_back(n1);
	++numEdges;
}

void Graph::removeNode(int n)
{
	graph.erase(n);

	for (auto const& adjN : graph[n].adjSet)
		removeEdge(n, adjN);

	nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), n), nodeList.end());
	--numNodes;
}

void Graph::removeEdge(int n1, int n2)
{
	graph[n1].adjSet.erase(std::remove(graph[n1].adjSet.begin(), 
									   graph[n1].adjSet.end(), n2), graph[n1].adjSet.end());

	graph[n2].adjSet.erase(std::remove(graph[n2].adjSet.begin(), 
									   graph[n2].adjSet.end(), n1), graph[n2].adjSet.end());

	--numEdges;
}

int Graph::getNodeNumber() const
{
	return numNodes;
}

int Graph::getEdgeNumber() const 
{
	return numEdges;
}

// num_edges is the maximum number of edges per vertex
void Graph::randomPopulate(int numNodes, int maxNumEdges, int seed)
{
	// add nodes from 0 to numNodes
	for (int i=0; i<numNodes; ++i)
		addNode(i);

	// generate edges at random for each node i
	for (int i=0; i<numNodes; ++i)
		for (int j=0; j<maxNumEdges; ++j)
		{
			int node = randomNode(0, numNodes-1, seed); 
			int nodeCount = std::count(graph[i].adjSet.begin(), graph[i].adjSet.end(), node);

			if (node != i && nodeCount == 0)
				addEdge(i, node);
		}
	
	// delete disconnected nodes
	int count = 0;
	for (int i=0; i<numNodes; ++i)
		if (graph[i].adjSet.size() == 0)
			removeNode(i);

	// create random order for the nodes
	order = std::move(getNodeList());
    std::random_shuffle(order.begin(), order.end());

	// create inverse order (alpha^-1) from order
	for (int i=0; i<order.size(); ++i)
		inverseOrder[order[i]] = i;

	// finally pre compute the monAdjSet for each node
	computeMonAdjSet();
}

// get the vertex based on the order (this is a) 
int Graph::getVertex(int orderIdx) const
{
	return order[orderIdx];	
}

// get the order based on the vertex (this is a^-1) 
int Graph::getOrder(int vertex) const 
{
	return inverseOrder.at(vertex);
}

Graph::nodeListTy Graph::getOrder() const
{
	return order;
}

Graph::nodeListTy Graph::getNodeList() const
{
	return nodeList;
}

Graph::nodeListTy Graph::getAdjSet(int n) const
{
	return graph.at(n).adjSet;
}

std::map<int, Graph::nodeListTy> Graph::computeMonAdjSet() const
{
	std::map<int, nodeListTy> monAdjSet;

	for (auto const& n: nodeList) 
		for (int i=0; i<graph.at(n).adjSet.size(); ++i)
			if (getOrder(n) < getOrder(graph.at(n).adjSet[i])) 
				monAdjSet[n].push_back(graph.at(n).adjSet[i]);

	return monAdjSet;
}

Graph::nodeListTy Graph::computeMonAdjSet(int n) const
{
	nodeListTy monAdjSet;

	for (int i=0; i<graph.at(n).adjSet.size(); ++i)
		if (getOrder(n) < getOrder(graph.at(n).adjSet[i])) 
			monAdjSet.push_back(graph.at(n).adjSet[i]);

	return monAdjSet;
}

void Graph::addNewEdges(std::map<int, Graph::nodeListTy> monAdjSet)
{
	auto newMonAdjSet = std::move(monAdjSet);

	for (auto const& n: nodeList)
	{
		auto originalAdj = std::move(computeMonAdjSet(n));
		for (int j=0; j<newMonAdjSet[n].size(); ++j)
		{   
			int w = newMonAdjSet[n][j];
			int originalCount = std::count(originalAdj.begin(), originalAdj.end(), w);

			if (originalCount == 0)
				addEdge(n, w);
		}
	}
}

int Graph::countNewEdges(std::map<int, Graph::nodeListTy> monAdjSet)
{
	int count = 0;
	auto newMonAdjSet = std::move(monAdjSet);

	for (auto const& n: nodeList)
	{
		auto originalAdj = std::move(computeMonAdjSet(n));
		for (int j=0; j<newMonAdjSet[n].size(); ++j)
		{   
			int w = newMonAdjSet[n][j];
			int originalCount = std::count(originalAdj.begin(), originalAdj.end(), w);

			if (originalCount == 0)
				++count;
		}
	}

	return count;
}

void Graph::setOrder(nodeListTy order)
{
	this->order = std::move(order);

	// create inverse order (alpha^-1) from order
	for (int i=0; i<this->order.size(); ++i)
		inverseOrder[this->order[i]] = i;
}

void Graph::reset()
{
	numNodes = 0;
	numEdges = 0;
	nodeList.clear();
	order.clear();
	graph.clear();
	inverseOrder.clear();
}

void Graph::printGraph() const
{
	for (int i=0; i<numNodes; ++i)
	{
		std::cout << "v: " << i << '\n';
		std::cout << "	edges: ";
		for (int j=0; j<graph.at(i).adjSet.size(); ++j)
			std::cout <<  " [" << graph.at(i).adjSet[j] << "] ";

		std::cout << "\n";
	}
}

int Graph::randomNode(int min, int max, int seed)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}
