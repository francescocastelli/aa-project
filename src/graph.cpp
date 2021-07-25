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
	if (graph.count(n1) == 0) {addNode(n1);}
	if (graph.count(n2) == 0) {addNode(n2);}

	graph[n1].adjSet.push_back(n2);
	graph[n2].adjSet.push_back(n1);
	++numEdges;
}

void Graph::removeNode(int n)
{
	for (auto const& adjN : graph[n].adjSet)
		removeEdge(n, adjN);

	graph.erase(n);
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

void Graph::randomPopulate(int numNodes, float q)
{
	// generate edges at random for each node i
	for (int i=0; i<numNodes; ++i)
		for (int j=i+1; j<numNodes; ++j)
		{
			float p = uniformProb();

			if (p < q)
				addEdge(i, j);
		}
}

Graph::setTy Graph::computeMonAdjSet() const
{
	std::unordered_map<int, nodeListTy> monAdjSet;

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

void Graph::addNewEdges(setTy monAdjSet)
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

int Graph::countNewEdges(setTy monAdjSet)
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
	for (auto const& n: nodeList)
	{
		std::cout << "v: " << n << '\n';
		std::cout << "	edges: ";
		for (int j=0; j<graph.at(n).adjSet.size(); ++j)
			std::cout <<  " [" << graph.at(n).adjSet[j] << "] ";

		std::cout << "\n";
	}
}

int Graph::getNodeNumber() const
{
	return numNodes;
}

int Graph::getEdgeNumber() const 
{
	return numEdges;
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


int Graph::randomNode(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

float Graph::uniformProb()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	return dist(rng);
}
