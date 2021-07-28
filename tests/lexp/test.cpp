#include "../../include/graph.h"
#include "../../include/fill.h"
#include "../../include/lexp.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace my {
namespace project {
namespace {

class GraphTest : public ::testing::Test {

protected:
  GraphTest() {

  }

  ~GraphTest() override {
  }

  void SetUp() override {
  }
};

TEST_F(GraphTest, Figure4) {
	Graph g(10);

	g.addEdge(1, 3);
	g.addEdge(1, 5);
	g.addEdge(2, 6);
	g.addEdge(2, 7);
	g.addEdge(3, 5);
	g.addEdge(3, 4);
	g.addEdge(3, 9);
	g.addEdge(4, 5);
	g.addEdge(4, 9);
	g.addEdge(5, 8);
	g.addEdge(5, 9);
	g.addEdge(6, 7);
	g.addEdge(6, 10);
	g.addEdge(7, 10);
	g.addEdge(8, 9);
	g.addEdge(8, 10);
	g.addEdge(9, 10);

	graph_algorithms::lexp(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	graph_algorithms::fill(g, std::move(monAdjSet));
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 0) << "num fill edges is: " << numFillEdges;
}

TEST_F(GraphTest, PerfectGraph) {
	Graph g(8);

	g.addEdge(1, 2);
	g.addEdge(1, 4);
	g.addEdge(1, 7);

	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 7);

	g.addEdge(3, 5);
	g.addEdge(3, 7);

	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 7);

	g.addEdge(5, 6);
	g.addEdge(5, 7);

	g.addEdge(6, 7);

	g.addEdge(7, 8);


	graph_algorithms::lexp(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	graph_algorithms::fill(g, std::move(monAdjSet));
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 0) << "num fill edges is: " << numFillEdges;
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
