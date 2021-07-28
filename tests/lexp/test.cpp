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
	Graph g;
	std::vector<int> baselineOrder = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (int i=1; i<=10; ++i)
	{
		g.addNode(i);
	}

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
	g.addEdge(8, 10);
	g.addEdge(9, 10);

	graph_algorithms::lexp(g);

	auto order = g.getOrder();
	for(int i=0; i<order.size(); ++i)
		ASSERT_EQ(order[i], baselineOrder[i]);
}

TEST_F(GraphTest, Figure3) {
	Graph g;
	std::vector<int> baselineOrder = {1, 2, 3, 4, 5, 6};

	for (int i=1; i<7; ++i)
		g.addNode(i);

	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 3);
	g.addEdge(2, 5);
	g.addEdge(3, 6);
	g.addEdge(4, 6);
	g.addEdge(5, 6);

	graph_algorithms::lexp(g);

	auto order = g.getOrder();
	for(int i=0; i<order.size(); ++i)
		ASSERT_EQ(order[i], baselineOrder[i]);
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
