//g++ test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark_res
#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../../include/graph.h"
#include "../../include/fill.h"

static void BM_fill(benchmark::State& state) 
{
	Graph g; 
	g.randomPopulate(state.range(0), state.range(0) / 4, 0);
	auto monAdjSet = g.computeMonAdjSet();

    for (auto _ : state)
    {
       graph_algorithms::fill(g, std::move(monAdjSet));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_fill)->RangeMultiplier(2)->Range(1<<5, 1<<11)->Complexity();

//and call the main of the benchmark
BENCHMARK_MAIN();
