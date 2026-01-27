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
#include "Dice.h"
#include "Actions.h"

// measure the cost Roll a Dice object with mt19937
static void BM_Roll_w_mt19937(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::mt19937(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_mt19937);

// measure the cost Roll a Dice object with mt19937_64 Engine
static void BM_Roll_w_mt19937_64(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::mt19937_64(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_mt19937_64);

// measure the cost Roll a Dice object with ranlux24_base Engine
static void BM_Roll_w_ranlux24_base(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::ranlux24_base(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_ranlux24_base);


// measure the cost Roll a Dice object with ranlux48_base Engine
static void BM_Roll_w_ranlux48_base(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::ranlux48_base(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_ranlux48_base);

// measure the cost Roll a Dice object with ranlux24 Engine
static void BM_Roll_w_ranlux24(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::ranlux24(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_ranlux24);


// measure the cost Roll a Dice object with ranlux48 Engine
static void BM_Roll_w_ranlux48(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::ranlux48(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_ranlux48);


// measure the cost Roll a Dice object with minstd_rand Engine
static void BM_Roll_w_minstd_rand(benchmark::State& state) {
  const auto dice = game_dice_cpp::Dice(20);
  auto engine = std::minstd_rand(42);
  // the loop where the code to be timed runs
  for (auto _ : state) {
    // prevent compiler from optimizing the result away
    benchmark::DoNotOptimize(game_dice_cpp::Roll(dice, engine));
  }
}
// register this benchmark
BENCHMARK(BM_Roll_w_minstd_rand);
