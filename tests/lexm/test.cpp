#include "../../include/graph.h"
#include "../../include/lexm.h"
#include "../../include/fill.h"
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

TEST_F(GraphTest, Figure2) {
	Graph g(9);

	g.addEdge(1, 2);
	g.addEdge(1, 5);

	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 6);

	g.addEdge(3, 7);

	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 8);

	g.addEdge(5, 8);

	g.addEdge(6, 7);
	g.addEdge(6, 9);

	g.addEdge(7, 9);

	g.addEdge(8, 9);

	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();

	graph_algorithms::fill(g, std::move(monAdjSet));
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 9) << "num fill edges is: " << numFillEdges;
}

TEST_F(GraphTest, Figure3) {
	Graph g(6);

	g.addEdge(1, 3);
	g.addEdge(1, 4);

	g.addEdge(2, 3);
	g.addEdge(2, 5);

	g.addEdge(3, 6);

	g.addEdge(4, 6);

	g.addEdge(5, 6);

	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();

	graph_algorithms::fill(g, std::move(monAdjSet));
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 2) << "num fill edges is: " << numFillEdges;
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
