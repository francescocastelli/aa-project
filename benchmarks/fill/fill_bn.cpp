#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../include/graph.h"
#include "../../include/fill.h"

static void BM_fill(benchmark::State& state) 
{
	Graph g; 
	std::map<int, std::vector<int>> outputSet;	

	g.randomPopulate(state.range(0), state.range(1), 1);

	// create random order for the nodes
	std::vector<int> order = std::move(g.getNodeList());
    std::random_shuffle(order.begin(), order.end());
	g.setOrder(std::move(order));

	// compute the monotonely adj sets of the graph
	auto monAdjSet = g.computeMonAdjSet();

	// n is the number of nodes of the graph g
	// e is the number of edges of the graph g 
	// e' is the number of edges of the graph g* (after fill)
	state.counters["n"] = g.getNodeNumber(); 
	state.counters["e"] = g.getEdgeNumber();
	state.counters["e'"] = 0;

	// the graph is the same in every iteration of the loop
	// we count every time the new edges added with fill  
    for (auto _ : state)
    {
		benchmark::DoNotOptimize(outputSet = std::move(graph_algorithms::fill(g, std::move(monAdjSet))));
		state.PauseTiming();
		state.counters["e'"] += state.counters["e"] + g.countNewEdges(std::move(outputSet));
		state.ResumeTiming();
    }

	// we average the value of e' among the iterations 
	state.counters["e'"] = state.counters["e'"] / state.iterations(); 

	// the complexity should be O(n+e')
    state.SetComplexityN(g.getNodeNumber() + state.counters["e'"]);
}

BENCHMARK(BM_fill)->RangeMultiplier(2)
				  ->Ranges({{1<<8, 1<<13}, {1<<1, 1<<4}})
				  // linear here bc we set N as n+e'
				  ->Complexity([](benchmark::IterationCount n)->double{return static_cast<double>(n);});

//and call the main of the benchmark
BENCHMARK_MAIN();
