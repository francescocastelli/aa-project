#include "../../include/graph.h"
#include "../../include/fill.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class GraphTest : public ::testing::TestWithParam<std::pair<int, float>> {

protected:
  GraphTest() {

  }

  ~GraphTest() override {
  }

  void SetUp() override {
	  numNodes = std::get<0>(GetParam());
	  density = std::get<1>(GetParam());;

	  g.reserve(numNodes);
	  g.randomPopulate(numNodes, density);
	  std::vector<int> order = std::move(g.getNodeList());
	  // create random order for the nodes
	  std::random_shuffle(order.begin(), order.end());
	  g.setOrder(std::move(order));

	  auto monAdjSet = g.computeMonAdjSet();
	  graph_algorithms::fill(g, std::move(monAdjSet));
	  nodes = g.getNodeList();
  }

  void TearDown() override {
  }

  int numNodes;
  float density;
  std::vector<int> nodes;
  Graph g;
};

// after applying fill to g (randomly generated) we obtain g* (elimination graph). 
// Since every elimination graph is a perfect elimination graph, the order of g* should be a 
// perfect elimination order. 
// This test checks that, after applying fill to g, the order of g* is a perfect elimination 
// order ( alpha is a perfect el. order if v ->- w and v ->-x imply w -- x or w = x)
TEST_P(GraphTest, GraphPopoluateEdges) {
  // it through verteces
  for(auto const& v: nodes)
  {
	  // nodes monotonely adj to v
	  auto mAdjV = g.computeMonAdjSet(v);

	  // here we check the case of (v->- w and v->-x) = true
	  // so if (w -- x or w == x) == true then we are good, else the order is not a 
	  // perfect elimination order for sure.
      // In the case of (v ->- w or v ->-x) = false we always have a perfect elimination order
  	  for(int j=0; j<mAdjV.size(); ++j)
	  {
		  int w = mAdjV[j];
		  auto wAdj = g.getAdjSet(w);
		  for(int i = 0; i<mAdjV.size(); ++i)
		  {
			  int x = mAdjV[i];
			  ASSERT_TRUE(std::count(wAdj.begin(), wAdj.end(), x) == 1 || w == x);
		  }
	  }
  }
}

const std::pair<int, float> values[] = {std::make_pair(10, 0.1), std::make_pair(10, 0.3), 
										std::make_pair(10, 0.5), std::make_pair(10, 0.9), 
										std::make_pair(20, 0.1), std::make_pair(20, 0.3), 
									  	std::make_pair(20, 0.7), std::make_pair(20, 0.5), 
									  	std::make_pair(50, 0.1), std::make_pair(50, 0.4)};

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
