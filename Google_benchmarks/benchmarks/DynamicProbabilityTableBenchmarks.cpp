//
// Copyright 2026 scholar-of-artifice
//
// Licensed under the MIT License
//
// Copyright (c) 2026 scholar-of-artifice
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "DynamicProbabilityTable.h"

// measure the cost of making a DynamicProbabilityTable object
static void BM_DynamicProbabilityTable_Make(benchmark::State& state) {
  std::vector<int> weights(state.range(0), 1);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(
        game_dice_cpp::DynamicProbabilityTable::Make(weights));
  }
}
// register this benchmark
BENCHMARK(BM_DynamicProbabilityTable_Make)->RangeMultiplier(2)->Range(8, 2048);

// measure the cost of GetTotalWeight in DynamicProbabilityTable
static void BM_DynamicProbabilityTable_GetTotalWeight(benchmark::State& state) {
  std::vector<int> weights(state.range(0), 1);
  auto table_opt = game_dice_cpp::DynamicProbabilityTable::Make(weights);
  if (!table_opt) {
    state.SkipWithError("Failed to create table.");
    return;
  }
  const auto& table = *table_opt;
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(table.GetTotalWeight());
  }
}
// register this benchmark
BENCHMARK(BM_DynamicProbabilityTable_GetTotalWeight)
    ->RangeMultiplier(2)
    ->Range(8, 2048);

// measure the cost of lookup in DynamicProbabilityTable
static void BM_DynamicProbabilityTable_At(benchmark::State& state) {
  std::vector<int> weights(state.range(0), 1);
  auto table_opt = game_dice_cpp::DynamicProbabilityTable::Make(weights);
  if (!table_opt) {
    state.SkipWithError("Failed to create table.");
    return;
  }
  const auto& table = *table_opt;
  int total_weight = table.GetTotalWeight();
  int input = 1;
  const int stride = 127;  // some prime number stride helps hit different cache
                           // lines and tree depths
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(table.At(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_DynamicProbabilityTable_At)->RangeMultiplier(2)->Range(8, 2048);
