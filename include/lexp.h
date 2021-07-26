#include "graph.h"
#include <algorithm>

namespace graph_algorithms
{

class CellList
{
private:
	struct cellInfo 
	{
		cellInfo () : flag (nullvalue), head (nullvalue), next (nullvalue), back (nullvalue) {}

		// fields required by the algorithm
		int flag; 
		int head;
		int next; 
		int back;
	};

public:
	CellList(int numNodes) : cells (numNodes)
	{
	}

	void addEmptyCell() {cells.emplace_back();}

	// managing the cell list items
	int& flag(int cellIdx) {return cells[cellIdx].flag;}
	int& head(int cellIdx) {return cells[cellIdx].head;}
	int& next(int cellIdx) {return cells[cellIdx].next;}
	int& back(int cellIdx) {return cells[cellIdx].back;}
	
	// get the cell idx of the vertex v
	int& cell(int v) {return cellV[v];}

	// nullptr basically 
	static constexpr int nullvalue = -1;

private:
	// map of cell idx, indexed using a node 
	std::unordered_map<int, int> cellV;

	// list of cell
	std::vector<cellInfo> cells;
};

/*  parameters :
 * 		graph g, the graph on which we apply lexm 
 * 
 * 	pseudo-code: 
 *
 * 		lexp algorithm is applyed to a graph with no order to compute a perfect order.
 *
 * 		this goal can also be reached using lexm and then testing that the fill-in set 
 * 		is empty using fill. But lexp will produce the same result is less time.
 * 		We exploit the fact that we are searching for perfect orders, and this implies 
 * 		that the fill-in set will be empty and the label of a node can be computed from 
 * 		its monotonely adjacent set.
 *
 * 		1. assign to all nodes the empty label 
 * 		2. loop from n to 1 (this defines the order) 
 *         2.a get an unnumbered node with largest label (v)
 *         2.b assign to this node the current order 
 *         2.c update2
 *  
 *  	update2: 
 *  		for each unnumbered vertex w adjacent to v add the current order index to 
 *  		label of w.
 *
 *  Complexity:
 *  	n is the number of nodes 
 *  	e is the total number of edges of g
 *
 *  	time complexity: O(n + e)
 *  	space complexity: O(n + e)
 */
void lexp(Graph& g)
{
	auto numNodes = g.getNodeNumber();
	// order, represent alpha so we index it using number from 0 to order.size() 
	std::vector<int> order (numNodes);
	// represent alpha^-1 so we index it using the verteces
	std::unordered_map<int, int> inverseOrder;
	std::vector<int> fixlist;
	//auto nodes = g.getNodeList();
	std::vector<int> nodes = std::move(g.getNodeList()); 
	std::sort(nodes.begin(), nodes.end(), std::greater<int>());

    CellList cells (numNodes);	

	// inizialization, implicity assign label empty to all nodes
	cells.addEmptyCell();
	cells.addEmptyCell();
	cells.head(0) = 1;
	cells.back(1) = 0;

	// c is the number of the first empty cell
	int c = 2;

	for (auto const& v: nodes)
	{
		//cells.addEmptyCell();
		cells.head(c) = v;
		cells.cell(v) = c; cells.next(c-1) = c;
		cells.flag(c) = 1;
		cells.back(c) = c-1;
		++c;	
		inverseOrder[v] = 0;
	}

	for (int i=numNodes-1; i>=0; --i)
	{
		// skip empty sets
		while (cells.next(cells.head(0)) == CellList::nullvalue)
		{
			cells.head(0) = cells.head(cells.head(0));
			cells.back(cells.head(0)) = 0;
		}

		// pick next vertex to number
		// select
		int p = cells.next(cells.head(0));
		
		// delete cell of vertex from set
		cells.next(cells.head(0)) = cells.next(p);
		if (cells.next(cells.head(0)) != CellList::nullvalue)
			cells.back(cells.next(cells.head(0))) = cells.head(0);

		int v = cells.head(p);
		
		// assign v the number i
		order[i] = v;
		inverseOrder[v] = i;
		fixlist.clear();

		// update2
		auto adjSetV = g.getAdjSet(v);
		for(const auto& w: adjSetV)
			if (inverseOrder[w] == 0)
			{
				auto& cellw = cells.cell(w);
				// delete cell of w from set
				cells.next(cells.back(cellw)) = cells.next(cellw);
				if (cells.next(cellw) != CellList::nullvalue) 
					cells.back(cells.next(cellw)) = cells.back(cellw);
				
				int h = cells.back(cells.flag(cellw));
				// if h is an old set then create a new set
				if (cells.flag(h) == CellList::nullvalue)
				{
					cells.addEmptyCell();
					cells.head(c) = cells.head(h);
					cells.head(h) = c; 
					cells.back(cells.head(c)) = c;
					cells.back(c) = h; 
					cells.flag(c) = 0; 
					cells.next(c) = CellList::nullvalue;
					fixlist.push_back(c);
					h = c;
					++c;
				}

				// add cell of w to new set
				cells.next(cellw) = cells.next(h);
				if (cells.next(h) != CellList::nullvalue) 
					cells.back(cells.next(h)) = cellw;

				cells.flag(cellw) = h; 
				cells.back(cellw) = h;
				cells.next(h) = cellw;
			}

		for (const auto& h: fixlist)
			cells.flag(h) = CellList::nullvalue;
	}

	g.setOrder(order);
}
} // namespace graph_algorithms
