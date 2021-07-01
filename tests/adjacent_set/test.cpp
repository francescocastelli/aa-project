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

TEST_F(GraphTest, GraphAdjSet) {
  Graph g(20);
  g.populateGraph(10);

  // it through verteces
  for(int i=0; i<20; ++i)
  {
	  auto mAdjSet = g.getMonotonicAdjSet(i);
	  // through verteces in edges of vertex i
	  for(int j=0; j<mAdjSet.size(); ++j)
	  {
		  auto count = std::count(g[i].begin(), g[i].end(), mAdjSet[j]);
		  // check that the order of a vertex in monotonic adj set is greater that i
		  EXPECT_TRUE(g.getOrder(mAdjSet[j]) > g.getOrder(i));
		  // check that a vertex in the monotonically adj set is also in the adj set of i
		  EXPECT_TRUE(count == 1);
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
