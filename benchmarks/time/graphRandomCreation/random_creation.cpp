#include <iostream>
#include <numeric>
#include <unordered_map>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../../include/graph.h"

static void BM_randomCreation(benchmark::State& state) 
{
	Graph g; 

	// the graph is the same in every iteration of the loop
	// we count every time the new edges added with fill  
    for (auto _ : state)
    {
		g.randomPopulate(state.range(0), (float)(state.range(1)) / 10.0f);
    }

	// n is the number of nodes of the graph g
	// e is the number of edges of the graph g 
	state.counters["n"] = g.getNodeNumber(); 
	state.counters["e"] = g.getEdgeNumber();
}

BENCHMARK(BM_randomCreation)->Unit(benchmark::kMicrosecond)
							->RangeMultiplier(2)
				  			->Ranges({{1<<8, 1<<12}, {1, 10}});

//and call the main of the benchmark
BENCHMARK_MAIN();
