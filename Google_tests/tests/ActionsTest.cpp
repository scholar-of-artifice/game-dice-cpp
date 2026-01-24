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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Actions.h"

TEST(ActionsTest, RollSameSeedReturnsDeterministicResult) {
  // GIVEN a d20...
  auto d20 = game_dice_cpp::Dice(20);
  // AND two distinct random number generators
  // AND the random number generators have the same seed
  std::mt19937_64 rand_generator_a(42);
  std::mt19937_64 rand_generator_b(42);
  // WHEN the dice is rolled
  auto result_a = game_dice_cpp::Roll(d20, rand_generator_a);
  auto result_b = game_dice_cpp::Roll(d20, rand_generator_b);
  // THEN the results are the same
  EXPECT_EQ(result_a, result_b) << "FAILURE: Roll value should be the same.";
}

TEST(ActionsTest, RollDifferentSeedReturnsDeterministicResult) {
  // GIVEN a d20...
  auto d20 = game_dice_cpp::Dice(20);
  // AND two distinct random number generators
  // AND the random number generators have different seed
  std::mt19937_64 rand_generator_a(42);
  std::mt19937_64 rand_generator_b(13579);
  // WHEN the dice is rolled
  auto result_a = game_dice_cpp::Roll(d20, rand_generator_a);
  auto result_b = game_dice_cpp::Roll(d20, rand_generator_b);
  // THEN the results are the same
  EXPECT_NE(result_a, result_b) << "FAILURE: Values should be distinct.";
}

TEST(ActionsTest, RollAnyDieProducesValueInRange) {
  // GIVEN a random number generator
  // AND that rng is seeded with 42
  std::mt19937_64 rand_generator(42);
  for (int sides = 2; sides < 20; sides++) {
    // AND a dice...
    auto dice = game_dice_cpp::Dice(sides);
    for (int trial = 0; trial <= 100'000; trial++) {
      // WHEN the dice is rolled
      auto result = game_dice_cpp::Roll(dice, rand_generator);
      // THEN the result is always in range
      EXPECT_THAT(result, testing::AllOf(testing::Ge(1), testing::Le(sides)))
          << "FAILURE: Value " << result << " not in range [1, " << sides
          << "].";
    }
  }
}