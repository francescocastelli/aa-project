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
	  auto mAdj = g[i];

	  // through adjacent list of vertex i
	  for(int j=0; j<mAdj.size(); ++j)
	  {
		  auto w = mAdj[j];
		  auto wEdges = g[w];
		  auto wMadj = g.getMonotonicAdjSet(w);
		  for (int h=0; h<mAdj.size(); ++h)
		  {
			  auto x = mAdj[h];
			  auto it = std::find(wEdges.begin(), wEdges.end(), x);
			  auto it2 = std::find(wMadj.begin(), wMadj.end(), x);
			  EXPECT_TRUE(x == w || it != wEdges.end() || it2 != wMadj.end()); 
		  }
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
