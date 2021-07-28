#include "../include/graph.h"

Graph::Graph() : nextNodeNum(0), numEdges(0)
{
}

Graph::Graph(int nodeNum) : nextNodeNum(0), 
								  numEdges(0),
								  inverseOrder(nodeNum)
{
	graph.reserve(nodeNum);
}

void Graph::reserve(int numNodes)
{
	graph.reserve(numNodes);
	inverseOrder.resize(numNodes);
}

void Graph::addEdge(int n1, int n2)
{
	int _n1, _n2;
	
	if (nodeMapping.count(n1) == 0)
	{
		nodeMapping[n1] = nextNodeNum; _n1 = nextNodeNum;
		graph.emplace_back(n1);
		++nextNodeNum;
	} else _n1 = nodeMapping[n1];

	if (nodeMapping.count(n2) == 0)
	{
		nodeMapping[n2] = nextNodeNum; _n2 = nextNodeNum;
		graph.emplace_back(n2);
		++nextNodeNum;
	} else _n2 = nodeMapping[n2];

	_addEdge(_n1, _n2);
}

void Graph::_addEdge(int _n1, int _n2)
{
	graph[_n2].adjSet.insert(_n1);
	auto res = graph[_n1].adjSet.insert(_n2);

	// check if the element was already present or not
	if (std::get<1>(res)) ++numEdges;
}

void Graph::addFillInEdges(int _n, nodeListTy others)
{
	auto verteces = std::move(others);
	for (auto const& _w : verteces)
		_addEdge(_n, _w);
}

void Graph::randomPopulate(int numNodes, float q)
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

Graph::setTy Graph::computeMonAdjSet() const
{
	setTy monAdjSet;

	for (auto i=0; i<nextNodeNum; ++i) 
	{
		auto& adjSetn = graph[i].adjSet;
		auto& monAdjSetn = monAdjSet[i];
		auto orderN = getOrder(i);

		for (auto const& adjEl : adjSetn)
			if (orderN < getOrder(adjEl)) 
				monAdjSetn.push_back(adjEl);
	}

	return monAdjSet;
}

Graph::nodeListTy Graph::computeMonAdjSet(int n) const
{
	nodeListTy monAdjSet;
	auto& adjSetn = graph[n].adjSet;
	auto orderN = getOrder(n);

	for (auto const& adjEl : adjSetn)
		if (orderN < getOrder(adjEl)) 
			monAdjSet.push_back(adjEl);

	return monAdjSet;
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
	nextNodeNum = 0;
	numEdges = 0;
	graph.clear();
	order.clear();
	inverseOrder.clear();
	nodeMapping.clear();
}

void Graph::printGraph() const
{
	for (int i=0; i<nextNodeNum; ++i)
	{
		std::cout << "v: " << graph[i].originalName << '\n';
		std::cout << "	edges: ";
		for(auto const& e : graph[i].adjSet)
			std::cout <<  " [" << graph[e].originalName << "] ";

		std::cout << "\n";
	}	
}

int Graph::getNodeNumber() const
{
	return graph.size();
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
	return inverseOrder[vertex];
}

Graph::nodeListTy Graph::getOrder() const
{
	return order;
}

Graph::nodeListTy Graph::getOriginalOrder() const
{
	nodeListTy originalOrder(order.size()); 

	for (auto i=0; i<order.size(); ++i)
		originalOrder[i] = graph[order[i]].originalName;

	return originalOrder;
}

Graph::nodeListTy Graph::getNodeList() const
{
	std::vector<int> nodes(nextNodeNum);
	std::iota(std::begin(nodes), std::end(nodes), 0);

	return nodes;
}

Graph::nodeListTy Graph::getAdjSet(int n) const
{
	nodeListTy vector; 
	auto& adjSet = graph[n].adjSet;

	vector.insert(vector.end(), adjSet.begin(), adjSet.end());
	return vector;
}

float Graph::uniformProb()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	return dist(rng);
}
