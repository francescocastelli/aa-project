#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../../include/graph.h"
#include "../../../include/lexm.h"

static void BM_lexm(benchmark::State& state) 
{
	Graph g(state.range(0)); 
	g.randomPopulate(state.range(0), (float) (state.range(1)) / 10.0f);

	// n is the number of nodes of the graph g
	// e is the number of edges of the graph g 
	state.counters["n"] = g.getNodeNumber(); 
	state.counters["e"] = g.getEdgeNumber();

    for (auto _ : state)
    {
		graph_algorithms::lexm(g);
    }

	// the complexity should be O(ne)
    state.SetComplexityN(state.counters["n"] * state.counters["e"]);
}

BENCHMARK(BM_lexm)->Unit(benchmark::kMicrosecond)
				  ->RangeMultiplier(2)
				  ->Ranges({{1<<5, 1<<12}, {1, 9}})
				  // linear here bc we set N as n+e
				  ->Complexity([](benchmark::IterationCount n)->double{return static_cast<double>(n);});

//and call the main of the benchmark
BENCHMARK_MAIN();
