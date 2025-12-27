//
// Copyright 2025 scholar-of-artifice
//
// Licensed under the MIT License
//
// Copyright (c) 2025 scholar-of-artifice
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

#include <gtest/gtest.h>

#include "../../src/Actions.h"

TEST(ActionsTest, RollAd6AlwaysProducesValueInRange) {
  // GIVEN a d6...
  auto d6 = game_dice::Dice(6);
  // AND a random number generator
  // AND that rng is seeded with 42
  std::mt19937_64 rand_generator(42);
  for (int trial = 0; trial <= 1'000'000; trial++) {
    // WHEN the dice is rolled
    auto result = game_dice::roll(d6, rand_generator);
    // THEN the result is always in range
    EXPECT_GE(result, 1)
    << "FAILURE: Result less than 1.";
    EXPECT_LE(result, 6)
    << "FAILURE: Result greater than 6.";
  }
}

TEST(ActionsTest, RollAd12AlwaysProducesValueInRange) {
  // GIVEN a d12...
  auto d12 = game_dice::Dice(12);
  // AND a random number generator
  // AND that rng is seeded with 42
  std::mt19937_64 rand_generator(42);
  for (int trial = 0; trial <= 1'000'000; trial++) {
    // WHEN the dice is rolled
    auto result = game_dice::roll(d12, rand_generator);
    // THEN the result is always in range
    EXPECT_GE(result, 1)
    << "FAILURE: Result less than 1.";
    EXPECT_LE(result, 12)
    << "FAILURE: Result greater than 12.";
  }
}


TEST(ActionsTest, RollAd20AlwaysProducesValueInRange) {
  // GIVEN a d20...
  auto d20 = game_dice::Dice(20);
  // AND a random number generator
  // AND that rng is seeded with 42
  std::mt19937_64 rand_generator(42);
  for (int trial = 0; trial <= 1'000'000; trial++) {
    // WHEN the dice is rolled
    auto result = game_dice::roll(d20, rand_generator);
    // THEN the result is always in range
    EXPECT_GE(result, 1)
    << "FAILURE: Result less than 1.";
    EXPECT_LE(result, 20)
    << "FAILURE: Result greater than 20.";
  }
}