#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../../include/graph.h"
#include "../../../include/lexp.h"

static void BM_lexp(benchmark::State& state) 
{
	Graph g; 
	g.randomPopulate(state.range(0), state.range(1), 1);

	// n is the number of nodes of the graph g
	// e is the number of edges of the graph g 
	state.counters["n"] = g.getNodeNumber(); 
	state.counters["e"] = g.getEdgeNumber();

    for (auto _ : state)
    {
		graph_algorithms::lexp(g);
    }

	// the complexity should be O(n+e)
    state.SetComplexityN(state.counters["n"] + state.counters["e"]);
}

BENCHMARK(BM_lexp)->RangeMultiplier(2)
				  ->Ranges({{1<<8, 1<<14}, {1<<1, 1<<6}})
				  // linear here bc we set N as n+e
				  ->Complexity([](benchmark::IterationCount n)->double{return static_cast<double>(n);});

//and call the main of the benchmark
BENCHMARK_MAIN();
