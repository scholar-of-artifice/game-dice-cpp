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

#include "StaticProbabilityTable.h"

TEST(StaticProbabilityTableTest,
     EmptyWeightInitializationHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND the weights are empty
  const auto table_A = game_dice_cpp::StaticProbabilityTable<0>();
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 0);
}

TEST(StaticProbabilityTableTest, AllPositiveWeightsHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND all weights are positive
  // small cases
  const auto table_A = game_dice_cpp::StaticProbabilityTable<3>(1, 1, 1);
  const auto table_B = game_dice_cpp::StaticProbabilityTable<3>(1, 2, 1);
  const auto table_C = game_dice_cpp::StaticProbabilityTable<3>(1, 2, 3);
  // medium cases
  const auto table_D =
      game_dice_cpp::StaticProbabilityTable<10>(1, 2, 3, 1, 8, 9, 22, 12, 1, 3);
  const auto table_E = game_dice_cpp::StaticProbabilityTable<12>(
      1, 2, 3, 1, 8, 9, 22, 12, 1, 3, 53, 33);
  const auto table_F = game_dice_cpp::StaticProbabilityTable<20>(
      1, 2, 3, 1, 8, 9, 22, 12, 1, 3, 53, 33, 12, 1, 15, 6, 81, 9, 10, 1);
  // large cases
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  // small cases
  EXPECT_EQ(table_A.GetTotalWeight(), 3);
  EXPECT_EQ(table_B.GetTotalWeight(), 4);
  EXPECT_EQ(table_C.GetTotalWeight(), 6);
  // medium cases
  EXPECT_EQ(table_D.GetTotalWeight(), 62);
  EXPECT_EQ(table_E.GetTotalWeight(), 148);
  EXPECT_EQ(table_F.GetTotalWeight(), 283);
}

TEST(StaticProbabilityTableTest, AllNegativeWeightsHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND all weights are positive
  // small cases
  const auto table_A = game_dice_cpp::StaticProbabilityTable<3>(-1, -1, -1);
  const auto table_B = game_dice_cpp::StaticProbabilityTable<3>(-1, -2, -1);
  const auto table_C = game_dice_cpp::StaticProbabilityTable<3>(-1, -2, -3);
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  // small cases
  EXPECT_EQ(table_A.GetTotalWeight(), 0);
  EXPECT_EQ(table_B.GetTotalWeight(), 0);
  EXPECT_EQ(table_C.GetTotalWeight(), 0);
}

TEST(StaticProbabilityTableTest, MixedSignWeightsHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND all weights are positive
  // small cases
  const auto table_A = game_dice_cpp::StaticProbabilityTable<3>(1, -1, 1);
  const auto table_B = game_dice_cpp::StaticProbabilityTable<3>(1, -2, 1);
  const auto table_C = game_dice_cpp::StaticProbabilityTable<3>(1, -2, -3);
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  // small cases
  EXPECT_EQ(table_A.GetTotalWeight(), 2);
  EXPECT_EQ(table_B.GetTotalWeight(), 2);
  EXPECT_EQ(table_C.GetTotalWeight(), 1);
}

TEST(StaticProbabilityTableTest, MapsToCorrectValue) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<3>(1, 2, 3);
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1);
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 2);
  EXPECT_EQ(table_A.At(5), 2);
  EXPECT_EQ(table_A.At(6), 2);
}

TEST(StaticProbabilityTableTest, OutOfBoundsLookup) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<3>(1, 2, 3);
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(-1), 0);
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(10), 2);
}

TEST(StaticProbabilityTableTest, MapsToCorrectValueWithLinearSearch) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<16>(
      1, 2, 3, 1, 2, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1);
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1);
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 2);
  EXPECT_EQ(table_A.At(5), 2);
  EXPECT_EQ(table_A.At(6), 2);
  EXPECT_EQ(table_A.At(7), 3);
  EXPECT_EQ(table_A.At(8), 4);
  EXPECT_EQ(table_A.At(9), 4);
  EXPECT_EQ(table_A.At(10), 5);
  EXPECT_EQ(table_A.At(11), 6);
  EXPECT_EQ(table_A.At(12), 6);
  EXPECT_EQ(table_A.At(13), 7);
  EXPECT_EQ(table_A.At(14), 7);
  EXPECT_EQ(table_A.At(15), 7);
  EXPECT_EQ(table_A.At(16), 8);
  EXPECT_EQ(table_A.At(17), 8);
  EXPECT_EQ(table_A.At(18), 8);
  EXPECT_EQ(table_A.At(19), 8);
  EXPECT_EQ(table_A.At(20), 9);
  EXPECT_EQ(table_A.At(21), 9);
  EXPECT_EQ(table_A.At(22), 9);
  EXPECT_EQ(table_A.At(23), 9);
  EXPECT_EQ(table_A.At(24), 9);
  EXPECT_EQ(table_A.At(25), 10);
  EXPECT_EQ(table_A.At(26), 11);
  EXPECT_EQ(table_A.At(27), 12);
  EXPECT_EQ(table_A.At(28), 13);
  EXPECT_EQ(table_A.At(29), 14);
  EXPECT_EQ(table_A.At(30), 15);
}

TEST(StaticProbabilityTableTest, MapsToCorrectValueWithBinarySearch) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<17>(
      1, 2, 3, 1, 2, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1);
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1);
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 2);
  EXPECT_EQ(table_A.At(5), 2);
  EXPECT_EQ(table_A.At(6), 2);
  EXPECT_EQ(table_A.At(7), 3);
  EXPECT_EQ(table_A.At(8), 4);
  EXPECT_EQ(table_A.At(9), 4);
  EXPECT_EQ(table_A.At(10), 5);
  EXPECT_EQ(table_A.At(11), 6);
  EXPECT_EQ(table_A.At(12), 6);
  EXPECT_EQ(table_A.At(13), 7);
  EXPECT_EQ(table_A.At(14), 7);
  EXPECT_EQ(table_A.At(15), 7);
  EXPECT_EQ(table_A.At(16), 8);
  EXPECT_EQ(table_A.At(17), 8);
  EXPECT_EQ(table_A.At(18), 8);
  EXPECT_EQ(table_A.At(19), 8);
  EXPECT_EQ(table_A.At(20), 9);
  EXPECT_EQ(table_A.At(21), 9);
  EXPECT_EQ(table_A.At(22), 9);
  EXPECT_EQ(table_A.At(23), 9);
  EXPECT_EQ(table_A.At(24), 9);
  EXPECT_EQ(table_A.At(25), 10);
  EXPECT_EQ(table_A.At(26), 11);
  EXPECT_EQ(table_A.At(27), 12);
  EXPECT_EQ(table_A.At(28), 13);
  EXPECT_EQ(table_A.At(29), 14);
  EXPECT_EQ(table_A.At(30), 15);
}

TEST(StaticProbabilityTableTest, HandlesLargeSafeWeights) {
  // GIVEN a table defined with known weights
  const auto half_max = std::numeric_limits<int>::max() / 2;
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<2>(half_max, half_max);
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(half_max + 1), 1);
}

TEST(StaticProbabilityTableTest, CompileTimeChecksMixedSignedWeights) {
  constexpr auto table = game_dice_cpp::StaticProbabilityTable<4>(1, -5, 0, 2);
  static_assert(table.GetTotalWeight() == 3);
  static_assert(table.At(1) == 0);
  static_assert(table.At(2) == 3);
}

TEST(StaticProbabilityTableTest, CompileTimeChecksSingleWeight) {
  constexpr auto single_table = game_dice_cpp::StaticProbabilityTable<1>(10);
  static_assert(single_table.GetTotalWeight() == 10);
  static_assert(single_table.At(5) == 0);
}

TEST(StaticProbabilityTableTest, CompileTimeChecksZeroWeights) {
  constexpr auto single_table =
      game_dice_cpp::StaticProbabilityTable<3>(0, 0, 0);
  static_assert(single_table.GetTotalWeight() == 0);
  static_assert(single_table.At(1) == 2);
}

// TODO: compile-time negative weights
// TODO: total weight zero
// TODO: integer overflow safety