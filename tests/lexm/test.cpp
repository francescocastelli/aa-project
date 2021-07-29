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

	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
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

	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 2) << "num fill edges is: " << numFillEdges;
}

// this is a perfect elimination graph 
// so lexm should get to the same result of lexp 
// since any minimal ordering in a perfect elimination graph is perfect
TEST_F(GraphTest, PerfectGraph1) {
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


	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 0) << "num fill edges is: " << numFillEdges;
}

TEST_F(GraphTest, PerfectGraph2) {
	Graph g(9);

	g.addEdge(1, 5);
	g.addEdge(1, 6);
	g.addEdge(1, 7);

	g.addEdge(2, 3);
	g.addEdge(2, 9);

	g.addEdge(3, 7);
	g.addEdge(3, 8);
	g.addEdge(3, 9);

	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 9);

	g.addEdge(5, 6);
	g.addEdge(5, 7);
	g.addEdge(5, 9);

	g.addEdge(6, 7);
	g.addEdge(6, 8);
	g.addEdge(6, 9);

	g.addEdge(7, 8);
	g.addEdge(7, 9);

	g.addEdge(8, 9);
	
	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 0) << "num fill edges is: " << numFillEdges;
}

TEST_F(GraphTest, PerfectGraph3) {
	Graph g(7);

	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(1, 5);
	g.addEdge(1, 6);
	g.addEdge(1, 7);

	g.addEdge(2, 3);

	g.addEdge(3, 4);

	g.addEdge(4, 5);

	g.addEdge(5, 6);

	g.addEdge(6, 7);

	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 0) << "num fill edges is: " << numFillEdges;
}

// https://www.semanticscholar.org/paper/Minimal-Elimination-Ordering-Inside-a-Given-Chordal-Dahlhaus/b05011bcb117b104ca0efe5b13bf011d73c1977a
TEST_F(GraphTest, MinimalOrderingGraph) {
	Graph g(9);

	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(1, 5);
	g.addEdge(1, 6);
	g.addEdge(1, 7);
	g.addEdge(1, 8);
	g.addEdge(1, 9);

	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 6);
	g.addEdge(2, 7);
	g.addEdge(2, 8);
	g.addEdge(2, 9);

	g.addEdge(3, 4);

	g.addEdge(4, 5);

	g.addEdge(5, 6);

	g.addEdge(6, 7);

	g.addEdge(7, 8);

	g.addEdge(8, 9);

	graph_algorithms::lexm(g);

	auto monAdjSet = g.computeMonAdjSet();
	int numEdgesBefore = g.getEdgeNumber();
	int fillCount = 0;
	graph_algorithms::fill(g, std::move(monAdjSet), true, fillCount);
	int numFillEdges = g.getEdgeNumber() - numEdgesBefore;

	ASSERT_EQ(numFillEdges, 15) << "num fill edges is: " << numFillEdges;
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
