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
template <size_t SizeVar>
static void BM_TriangleDistribution(benchmark::State& state) {
  // vary the size
  // keep the peak in the middle
  const std::size_t peak_index = SizeVar / 2;
  // const weight
  const int peak_weight = 100;
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(
        game_dice_cpp::TriangleDistribution<SizeVar>(peak_index, peak_weight));
  }
}
// register this benchmark
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 8);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 16);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 32);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 64);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 128);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 256);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 512);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 1024);
BENCHMARK_TEMPLATE(BM_TriangleDistribution, 2048);
