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

#include "DistributionFactory.h"

// measure the cost of constructing a Dice object
static void BM_TriangleDistribution(benchmark::State& state) {
  // vary the size
  int size = state.range(0);
  // keep the peak in the middle
  int peak_index = size / 2;
  // const weight
  const int peak_weight = 100;
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(
        game_dice_cpp::TriangleDistribution(size, peak_index, peak_weight));
  }
}
// register this benchmark
BENCHMARK(BM_TriangleDistribution)->RangeMultiplier(2)->Range(8, 2048);