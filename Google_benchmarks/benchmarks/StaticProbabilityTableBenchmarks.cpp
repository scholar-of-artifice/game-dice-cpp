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

#include "StaticProbabilityTable.h"

// measure the cost of making a StaticProbabilityTable object of size 8
static void BM_StaticProbabilityTable_Make_8(benchmark::State& state) {
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::StaticProbabilityTable<8>::Make(
        {8, 7, 8, 3, 2, 1, 9, 4}));
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_Make_8);

// measure the cost of At for a StaticProbabilityTable object of size 8
static void BM_StaticProbabilityTable_GetOutcomeIndex_8(
    benchmark::State& state) {
  auto table_opt =
      game_dice_cpp::StaticProbabilityTable<8>::Make({8, 7, 8, 3, 2, 1, 9, 4});
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
    benchmark::DoNotOptimize(table.GetOutcomeIndex(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_GetOutcomeIndex_8);

// measure the cost of GetTotalWeight for a StaticProbabilityTable object of
// size 8
static void BM_StaticProbabilityTable_GetTotalWeight_8(
    benchmark::State& state) {
  auto table_opt =
      game_dice_cpp::StaticProbabilityTable<8>::Make({8, 7, 8, 3, 2, 1, 9, 4});
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
BENCHMARK(BM_StaticProbabilityTable_GetTotalWeight_8);

// measure the cost of making a StaticProbabilityTable object of size 16
static void BM_StaticProbabilityTable_Make_16(benchmark::State& state) {
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::StaticProbabilityTable<16>::Make(
        {1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 2, 2, 6, 3, 7, 8}));
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_Make_16);

// measure the cost of At for a StaticProbabilityTable object of size 16
static void BM_StaticProbabilityTable_GetOutcomeIndex_16(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<16>::Make(
      {1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 2, 2, 6, 3, 7, 8});
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
    benchmark::DoNotOptimize(table.GetOutcomeIndex(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_GetOutcomeIndex_16);

// measure the cost of GetTotalWeight for a StaticProbabilityTable object of
// size 16
static void BM_StaticProbabilityTable_GetTotalWeight_16(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<16>::Make(
      {1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 2, 2, 6, 3, 7, 8});
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
BENCHMARK(BM_StaticProbabilityTable_GetTotalWeight_16);

// measure the cost of making a StaticProbabilityTable object of size 32
static void BM_StaticProbabilityTable_Make_32(benchmark::State& state) {
  const int x = 2;
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::StaticProbabilityTable<32>::Make(
        {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2,
         8, 3, 2, 5, 3, 2, 5, 8, 5, 4, 8, 2, 1, 8, 1, 9}));
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_Make_32);

// measure the cost of At for a StaticProbabilityTable object of size 32
static void BM_StaticProbabilityTable_GetOutcomeIndex_32(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<32>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2,
       8, 3, 2, 5, 3, 2, 5, 8, 5, 4, 8, 2, 1, 8, 1, 9});
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
    benchmark::DoNotOptimize(table.GetOutcomeIndex(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_GetOutcomeIndex_32);

// measure the cost of GetTotalWeight for a StaticProbabilityTable object of
// size 32
static void BM_StaticProbabilityTable_GetTotalWeight_32(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<32>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2,
       8, 3, 2, 5, 3, 2, 5, 8, 5, 4, 8, 2, 1, 8, 1, 9});
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
BENCHMARK(BM_StaticProbabilityTable_GetTotalWeight_32);

// measure the cost of making a StaticProbabilityTable object of size 64
static void BM_StaticProbabilityTable_Make_64(benchmark::State& state) {
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::StaticProbabilityTable<64>::Make(
        {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
         5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
         5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3}));
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_Make_64);

// measure the cost of At for a StaticProbabilityTable object of size 64
static void BM_StaticProbabilityTable_GetOutcomeIndex_64(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<64>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
       5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
       5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3});
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
    benchmark::DoNotOptimize(table.GetOutcomeIndex(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_GetOutcomeIndex_64);

// measure the cost of GetTotalWeight for a StaticProbabilityTable object of
// size 64
static void BM_StaticProbabilityTable_GetTotalWeight_64(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<64>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
       5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
       5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3});
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
BENCHMARK(BM_StaticProbabilityTable_GetTotalWeight_64);

// measure the cost of making a StaticProbabilityTable object of size 128
static void BM_StaticProbabilityTable_Make_128(benchmark::State& state) {
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::StaticProbabilityTable<128>::Make(
        {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
         5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
         5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3, 1, 8,
         3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2, 5, 8,
         5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2, 5, 2,
         2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3}));
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_Make_128);

// measure the cost of At for a StaticProbabilityTable object of size 128
static void BM_StaticProbabilityTable_GetOutcomeIndex_128(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<128>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
       5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
       5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3, 1, 8,
       3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2, 5, 8,
       5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2, 5, 2,
       2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3});
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
    benchmark::DoNotOptimize(table.GetOutcomeIndex(input));
    // alternate increment
    input = input + stride;
    if (input > total_weight) {
      input = (input % total_weight) + 1;
    }
  }
}
// register this benchmark
BENCHMARK(BM_StaticProbabilityTable_GetOutcomeIndex_128);

// measure the cost of GetTotalWeight for a StaticProbabilityTable object of
// size 128
static void BM_StaticProbabilityTable_GetTotalWeight_128(
    benchmark::State& state) {
  auto table_opt = game_dice_cpp::StaticProbabilityTable<128>::Make(
      {1, 8, 3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2,
       5, 8, 5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2,
       5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3, 1, 8,
       3, 2, 5, 2, 2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 8, 3, 2, 5, 3, 2, 5, 8,
       5, 4, 8, 2, 1, 8, 1, 9, 5, 6, 8, 7, 3, 1, 9, 8, 1, 1, 3, 2, 5, 2,
       2, 6, 3, 7, 8, 6, 5, 2, 1, 2, 2, 3, 2, 5, 3, 2, 5, 3});
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
BENCHMARK(BM_StaticProbabilityTable_GetTotalWeight_128);
