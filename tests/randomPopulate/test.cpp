#include "../../include/graph.h"
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
	  nodes = g.getNodeList();
  }

  void TearDown() override {
  }

  int numNodes;
  int numEdges;
  std::vector<int> nodes;
  Graph g;
};

// Tests that the Graph::randomPopulate() method create all the verteces in the 
// right place.
TEST_P(GraphTest, GraphPopoluateEdges) {
  // it through verteces
  for(auto const& n: nodes)
  {
	  auto edges = g.getAdjSet(n);

	  // check that i is present in the adjSet of all the adjacent nodes
	  for(int j=0; j<edges.size(); ++j)
	  {
		  auto edges_two = g.getAdjSet(edges[j]);
		  auto it = std::find(edges_two.begin(), edges_two.end(), n);
		  EXPECT_FALSE(it == edges_two.end()) << "node " << n <<" not found in adjList of "<<j;
	  }
  }
}

TEST_P(GraphTest, GraphNoSameVertexInEdges) {
  // it through verteces
  for(auto const& i: nodes)
  {
	  auto edges = g.getAdjSet(i);

	  // through verteces in edges of vertex i
	  for(int j=0; j<edges.size(); ++j)
		  EXPECT_FALSE(i == edges[j]) << "repetion of node " << i;
  }
}

TEST_P(GraphTest, GraphNoDuplicateEdges) {
  // it through verteces
  for(auto const& i: nodes)
  {
	  auto edges = g.getAdjSet(i);

	  // through verteces in edges of vertex i
	  for(int j=0; j<edges.size(); ++j)
	  {
		  auto edges_two = g.getAdjSet(edges[j]);
		  auto count = std::count(edges_two.begin(), edges_two.end(), i);
		  EXPECT_TRUE(count < 2) << "duplicate in ajd set of node "<< i;
	  }
  }
}

TEST_P(GraphTest, ConnectedGraph) {
  ASSERT_NE(g.getNodeNumber(), 1)<<"graph should be connected, 0 or more than one node required";
  ASSERT_EQ(g.getNodeNumber(), nodes.size());

  // it through verteces
  for(auto const& i: nodes)
  {
	  auto edges = g.getAdjSet(i);
	  EXPECT_TRUE(edges.size() > 0) << "node " << i << " has no adj nodes " 
		  						    << "size: "<< edges.size()
									<< "numNodes: "<< g.getNodeNumber();
  }
}

TEST_P(GraphTest, CorrectNumberOfNodes) {
  EXPECT_EQ(g.getNodeNumber(), nodes.size()) << "number of nodes in g is not correct";
}

TEST_P(GraphTest, CheckMonAdjSet) {
  // it through verteces
  for(auto const& i: nodes)
  {
	  auto mAdjSet = g.getMonAdjSet(i);
	  auto adjSet = g.getAdjSet(i);
	  // through verteces in edges of vertex i
	  for(int j=0; j<mAdjSet.size(); ++j)
	  {
		  auto count = std::count(adjSet.begin(), adjSet.end(), mAdjSet[j]);
		  // check that the order of a vertex in monotonic adj set is greater that i
		  EXPECT_TRUE(g.getOrder(mAdjSet[j]) > g.getOrder(i));
		  // check that a vertex in the monotonically adj set is also in the adj set of i
		  EXPECT_TRUE(count == 1);
	  }
  }
}

const std::pair<int, int> values[] = {std::make_pair(20, 5), std::make_pair(25, 10), 
									  std::make_pair(5, 10), std::make_pair(50, 30), 
									  std::make_pair(2, 1), std::make_pair(100, 100), 
									  std::make_pair(100, 2)};

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
