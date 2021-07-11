#include "graph.h"

namespace graph_algorithms
{

class CellList
{
private:
	struct cellInfo 
	{
		// fields required by the algorithm
		int flag; 
		int head;
		int next; 
		int back;
	};

	cellInfo make_empty_cell()
	{
		cellInfo cell = {nullvalue, nullvalue, nullvalue, nullvalue};
		return cell;
	}

public:
	CellList(int numNodes) : cellV (numNodes), cells (numNodes)
	{
	}

	void addEmptyCell() {cells.push_back({nullvalue, nullvalue, nullvalue, nullvalue});};

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
	// list of cell idx, indexed using a node 
	std::vector<int> cellV;

	// list of cell
	std::vector<cellInfo> cells;
};


void lexp(Graph& g)
{
	auto numNodes = g.getNodeNumber();
	// order, represent alpha so we index it using number from 0 to order.size() 
	std::vector<int> order (numNodes);
	// represent alpha^-1 so we index it using the verteces
	std::vector<int> inverseOrder (numNodes);
	std::vector<int> fixlist;
	auto nodes = g.getNodeList();

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
		cells.addEmptyCell();
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
			cells.back(cells.head(0)) = 1;
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
				// delete cell of w from set
				cells.next(cells.back(cells.cell(w))) = cells.next(cells.cell(w));
				if (cells.next(cells.cell(w)) != CellList::nullvalue) 
					cells.back(cells.next(cells.cell(w))) = cells.back(cells.cell(w));
				
				int h = cells.back(cells.flag(cells.cell(w)));
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
				cells.next(cells.cell(w)) = cells.next(h);
				if (cells.next(h) != CellList::nullvalue) 
					cells.back(cells.next(h)) = cells.cell(w);

				cells.flag(cells.cell(w)) = h; 
				cells.back(cells.cell(w)) = h;
				cells.next(h) = cells.cell(w);
			}

		for (const auto& h: fixlist)
			cells.flag(h) = CellList::nullvalue;
	}

	g.setOrder(std::move(order));
}
} // namespace graph_algorithms
