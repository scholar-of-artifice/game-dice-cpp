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

#include <vector>

#include "RoundingPolicies.h"

// measure the cost of Rounding with StandardRoundingPolicy object
static void BM_RoundingPolicies_StandardRoundingPolicy_Round(
    benchmark::State& state) {
  const size_t n = state.range(0);
  std::vector<double> values(n);
  for (size_t i = 0; i < n; ++i) {
    values[i] = static_cast<double>(i) + 0.5;
  }
  // the loop where the code to be timed runs
  for (auto _ : state) {
    for (double x : values) {
      // prevent compiler from optimizing the result away
      benchmark::DoNotOptimize(game_dice_cpp::StandardRoundingPolicy::Round(x));
    }
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_RoundingPolicies_StandardRoundingPolicy_Round)
    ->RangeMultiplier(2)
    ->Range(8, 2048);