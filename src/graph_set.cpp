#include "../include/graph_set.h"
#include <random>
#include <iostream>
#include <algorithm>

GraphSet::GraphSet() : nextNodeNum(0), numEdges(0)
{
}

void GraphSet::addEdge(int n1, int n2)
{
	int _n1, _n2;
	
	if (!nodeMapping.contains(n1))
	{
		nodeMapping[n1] = nextNodeNum; _n1 = nextNodeNum;
		graph.emplace_back();
		++nextNodeNum;
	} else _n1 = nodeMapping[n1];

	if (!nodeMapping.contains(n2))
	{
		nodeMapping[n2] = nextNodeNum; _n2 = nextNodeNum;
		graph.emplace_back();
		++nextNodeNum;
	} else _n2 = nodeMapping[n2];

	graph[_n2].adjSet.insert(_n1);
	graph[_n1].adjSet.insert(_n2);
	++numEdges;
}

void GraphSet::randomPopulate(int numNodes, float q)
{
	// goes through every possible edge and 
	// sample from a uniform distribution 0-1 the 
	// probability p. if p < q keep the edge
	for (int i=0; i<numNodes; ++i)
		for (int j=i+1; j<numNodes; ++j)
		{
			float p = uniformProb();

			if (p < q)
				addEdge(i, j);
		}
}

GraphSet::setTy GraphSet::computeMonAdjSet() const
{
	std::unordered_map<int, nodeListTy> monAdjSet;

	for (auto const& n: graph) 
	{
		auto& adjSetn = n.adjSet;
		auto& monAdjSetn = monAdjSet[n];
		auto orderN = getOrder(n);

		for (auto const& adjEl : adjSetn)
			if (orderN < getOrder(adjEl)) 
				monAdjSetn.push_back(adjEl);

	}

	return monAdjSet;
}

GraphSet::nodeListTy GraphSet::computeMonAdjSet(int n) const
{
	nodeListTy monAdjSet;
	auto& adjSetn = graph.at(n).adjSet;
	auto orderN = getOrder(n);

	for (auto const& adjEl : adjSetn)
		if (orderN < getOrder(adjEl)) 
			monAdjSet.push_back(adjEl);

	return monAdjSet;
}

void GraphSet::setOrder(nodeListTy order)
{
	this->order = std::move(order);

	// create inverse order (alpha^-1) from order
	for (int i=0; i<this->order.size(); ++i)
		inverseOrder[this->order[i]] = i;
}

void GraphSet::reset()
{
	numEdges = 0;
	order.clear();
	graph.clear();
	inverseOrder.clear();
}

int GraphSet::getNodeNumber() const
{
	return graph.size();
}

int GraphSet::getEdgeNumber() const 
{
	return numEdges;
}

// get the vertex based on the order (this is a) 
int GraphSet::getVertex(int orderIdx) const
{
	return order[orderIdx];	
}

// get the order based on the vertex (this is a^-1) 
int GraphSet::getOrder(int vertex) const 
{
	return inverseOrder.at(vertex);
}

GraphSet::nodeListTy GraphSet::getOrder() const
{
	return order;
}

GraphSet::nodeListTy GraphSet::getNodeList() const
{
	std::vector<int> keys;
	keys.reserve(graph.size());

	for(auto kv : graph) {
		keys.push_back(kv.first);
	} 

	return keys;
}

GraphSet::nodeListTy GraphSet::getAdjSet(int n) const
{
	nodeListTy vector; 
	auto& adjSet = graph.at(n).adjSet;

	vector.insert(vector.end(), adjSet.begin(), adjSet.end());
	return vector;
}

float GraphSet::uniformProb()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	return dist(rng);
}
