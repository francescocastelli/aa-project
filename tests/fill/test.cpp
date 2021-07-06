#include "../../include/graph.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class GraphTest : public ::testing::Test {
 protected:

  GraphTest() {

  }

  ~GraphTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Graph::populateGraph() method create all the verteces in the 
// right place.
TEST_F(GraphTest, GraphPopoluateEdges) {
  Graph g(20);
  g.populateGraph(5);

  g.fill();

  // it through verteces
  for(int i=0; i<20; ++i)
  {
	  auto edges = g[i];

	  // through verteces in edges of vertex i
	  for(int j=0; j<edges.size(); ++j)
	  {
		  auto edges_two = g[edges[j]];
		  auto it = std::find(edges_two.begin(), edges_two.end(), i);
		  EXPECT_FALSE(it == edges_two.end());
	  }
  }
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
