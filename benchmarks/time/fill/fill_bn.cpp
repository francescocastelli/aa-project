#include <iostream>
#include <numeric>
#include <unordered_map>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../../include/graph.h"
#include "../../../include/fill.h"

static void createRandomOrder(Graph& g)
{
	// create random order for the nodes
	auto order = std::move(g.getNodeList());
    std::random_shuffle(order.begin(), order.end());
	g.setOrder(std::move(order));
}

static void BM_fill(benchmark::State& state) 
{
	Graph g(state.range(0)); 
	g.randomPopulate(state.range(0), (float) (state.range(1)) / 10.0f);
	createRandomOrder(g);

	// compute the monotonely adj sets of the graph
	auto monAdjSet = std::move(g.computeMonAdjSet());

	// n is the number of nodes of the graph g
	// e is the number of edges of the graph g 
	// e' is the number of edges of the graph g* (after fill)
	state.counters["n"] = g.getNodeNumber(); 
	state.counters["e"] = g.getEdgeNumber();
	int fillCount = 0;

	// the graph is the same in every iteration of the loop
	// we count every time the new edges added with fill  
    for (auto _ : state)
    {
		fillCount = 0;
		graph_algorithms::fill(g, std::move(monAdjSet), false, fillCount);
		state.PauseTiming();
		monAdjSet = std::move(g.computeMonAdjSet());
		state.ResumeTiming();
    }

	// we average the value of e' among the iterations 
	state.counters["e'"] = fillCount + state.counters["e"]; 

	// the complexity should be O(n+e')
    state.SetComplexityN(g.getNodeNumber() + state.counters["e'"]);
}

BENCHMARK(BM_fill)->Unit(benchmark::kMicrosecond)
				  ->RangeMultiplier(2)
				  ->Ranges({{1<<5, 1<<12}, {1, 9}})
				  // linear here bc we set N as n+e'
				  ->Complexity([](benchmark::IterationCount n)->double{return static_cast<double>(n);});

//and call the main of the benchmark
BENCHMARK_MAIN();
