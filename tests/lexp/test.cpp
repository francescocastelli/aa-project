#include "../../include/graph.h"
#include "../../include/fill.h"
#include "../../include/lexp.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace my {
namespace project {
namespace {

class GraphTest : public ::testing::TestWithParam<std::pair<int, int>> {

protected:
  GraphTest() {

  }

  ~GraphTest() override {
  }

  void SetUp() override {
	  numNodes = std::get<0>(GetParam());
	  numEdges = std::get<1>(GetParam());;

	  g.randomPopulate(numNodes, numEdges);
	  graph_algorithms::lexp(g);
  }

  void TearDown() override {
  }

  int numNodes;
  int numEdges;
  std::vector<int> order;
  Graph g;
};

TEST_P(GraphTest, CheckLexp) {
  auto newOrder = g.getOrder();

  for(int i=0; i<order.size(); ++i)
  {	
	  ASSERT_TRUE(order[i] == newOrder[i]) << "original: " << order[i] << " - lexp: " << newOrder[i];
  }
}

const std::pair<int, int> values[] = {std::make_pair(20, 5), std::make_pair(25, 10), 
									  std::make_pair(5, 10), std::make_pair(50, 30)};

INSTANTIATE_TEST_SUITE_P(nodesEdgesRange, 
						 GraphTest, 
						 testing::ValuesIn(values));
}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
