#include "../../include/graph.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace my {
namespace project {
namespace {

class GraphTest : public ::testing::TestWithParam<std::pair<int, float>> {

protected:
  GraphTest() {

  }

  ~GraphTest() override {
  }

  void SetUp() override {
	  numNodes = std::get<0>(GetParam());
	  density = std::get<1>(GetParam());

	  g.randomPopulate(numNodes, density);

	  // create random order for the nodes
	  std::vector<int> order = std::move(g.getNodeList());
	  std::random_shuffle(order.begin(), order.end());
	  g.setOrder(std::move(order));

	  nodes = g.getNodeList();
  }

  void TearDown() override {
  }

  int numNodes;
  float density;
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

// check that a vertex is not in its adjSet
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

// check no duplicate edges are present
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

TEST_P(GraphTest, CorrectNumberOfEdges) {
	int sum = 0;

	for (auto const& i: nodes)
		sum += g.getAdjSet(i).size();

	EXPECT_EQ(g.getEdgeNumber(), sum/2) << "number of edges in g is not correct";
}

// check that monAdjSet are correctly computed
TEST_P(GraphTest, CheckMonAdjSet) {
  // it through verteces
  for(auto const& i: nodes)
  {
	  auto mAdjSet = g.computeMonAdjSet(i);
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

const std::pair<int, float> values[] = {std::make_pair(20, 0.05f), std::make_pair(20, 0.1f), 
										std::make_pair(20, 0.2f), std::make_pair(20, 0.9f), 
										std::make_pair(20, 1.0f), std::make_pair(2, 0.1f), 
										std::make_pair(2, 1.0f), std::make_pair(100, 1.0f), 
										std::make_pair(100, 0.5f), std::make_pair(100, 0.1f)};

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
