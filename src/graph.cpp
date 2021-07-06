#include "../include/graph.h"
#include <random>
#include <iostream>
#include <algorithm>

Graph::Graph (int num_verteces) : num_verteces (num_verteces), 
						   		  order(num_verteces)
{
	// initialize with empty lists of edges and monAdj set each vertex
	for(int i=0; i<num_verteces; ++i)
		graph.insert({i, {std::vector<int>(), std::vector<int>()}});

	// random order of verteces from 0 to num_verteces
	std::iota(order.begin(), order.end(), 0);
	std::random_shuffle(order.begin(), order.end());
}

const Graph::edgeListTy& Graph::operator[](int vertex) 
{ 
	return graph[vertex].edges; 
}

const Graph::edgeListTy& Graph::getEdges(int vertex)
{
	return graph[vertex].edges; 
}

const Graph::edgeListTy& Graph::getMonotonicAdjSet(int vertex)
{
	return graph[vertex].monAdjSet;
}

// num_edges is the maximum number of edges per vertex
void Graph::populateGraph(int maxNumEdges)
{
	for (int i=0; i<num_verteces; ++i)
	{
		// generate edges at random 
		for (int j=0; j<maxNumEdges; ++j)
		{
			int edge = randomEdge(); 
			if (edge != i && std::count(graph[i].edges.begin(), graph[i].edges.end(), edge) == 0)
				graph[i].edges.push_back(edge);
		}

		// add vertex i to all the verteces vectors in graph[i] 
		for (int j=0; j<graph[i].edges.size(); ++j)
		{
			if (std::count(graph[graph[i].edges[j]].edges.begin(), 
						   graph[graph[i].edges[j]].edges.end(), i) == 0)
				graph[graph[i].edges[j]].edges.push_back(i);
		}
	}
	
	for (int i=0; i<num_verteces; ++i)
	{
		graph[i].monAdjSet = std::move(computeMonAdjSet(i));
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

const Graph::edgeListTy& Graph::getOrder()
{
	return order;
}

Graph::edgeListTy Graph::computeMonAdjSet(int vertex)
{
	std::vector<int> mAdj;

	for (int i=0; i<graph[vertex].edges.size(); ++i)
		if (getOrder(vertex) < getOrder(graph[vertex].edges[i])) 
			mAdj.push_back(graph[vertex].edges[i]);
	
	return mAdj;
}


void Graph::printGraph()
{
	for (int i=0; i<num_verteces; ++i)
	{
		std::cout << "v: " << i << '\n';
		std::cout << "	edges: ";
		for (int j=0; j<graph[i].edges.size(); ++j)
			std::cout <<  " [" << graph[i].edges[j] << "] ";

		std::cout << '\n' << "	mAdj: ";
		for (int j=0; j<graph[i].monAdjSet.size(); ++j)
			std::cout <<  " [" << graph[i].monAdjSet[j] << "] ";

		std::cout << "\n\n";
	}
}

int Graph::randomEdge()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, num_verteces-1);

	return dist(rng);
}

void Graph::fill()
{
	// begin
	std::map<int, std::vector<int>> out;
	std::vector<bool> test(num_verteces, false);
	int k, v, size;

	// loop
	for(int i=0; i<num_verteces; ++i)
	{
		k = num_verteces;
		v = getVertex(i); 

		// dup 
		//size = graph[v].monAdjSet.size();
		for (int j=0; j<graph[v].monAdjSet.size(); ++j)
		{
			int w = graph[v].monAdjSet[j];
			int wOrder = getOrder(w);
			
			if (test[wOrder]) 	
			{
				//std::remove(graph[v].monAdjSet.begin(), graph[v].monAdjSet.end(), w);
				auto it = std::find(graph[v].monAdjSet.begin(), graph[v].monAdjSet.end(), w);
				if (it != graph[v].monAdjSet.end()) 
				{
					std::swap(*it, graph[v].monAdjSet.back());
					graph[v].monAdjSet.pop_back();
					--j;
				}

			}
			else
			{
				test[wOrder] = true;
				k = std::min(k, wOrder);
			}
		}

		int m = getVertex(k);

		// add 
		size = graph[v].monAdjSet.size();
		for (int j=0; j<size; ++j)
		{
			int w = graph[v].monAdjSet[j];
			test[getOrder(w)] = false;

			if (w != m) graph[m].monAdjSet.push_back(w);
		}
	}
}
