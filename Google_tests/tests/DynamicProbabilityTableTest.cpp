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

#include "DynamicProbabilityTable.h"

TEST(DynamicProbabilityTableGetTotalWeightTest, AllPositiveWeightsHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND all weights are positive
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, 1, 1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({1, 2, 1});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, 2, 3});
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 3);
  EXPECT_EQ(table_B.GetTotalWeight(), 4);
  EXPECT_EQ(table_C.GetTotalWeight(), 6);
}

TEST(DynamicProbabilityTableGetTotalWeightTest, AllNegativeWeightsHasTotalWeightOfZero) {
  // GIVEN a table defined with known weights
  // AND all weights are negative
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({-1, -1, -1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({-1, -2, -1});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({-1, -2, -3});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 0);
  EXPECT_EQ(table_B.GetTotalWeight(), 0);
  EXPECT_EQ(table_C.GetTotalWeight(), 0);
}

TEST(DynamicProbabilityTableGetTotalWeightTest, MixedSignWeightsHasTotalWeightOfZero) {
  // GIVEN a table defined with known weights
  // AND weights are mixed signedness
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, -1, 1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({1, -2, 1});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, -2, -3});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 2);
  EXPECT_EQ(table_B.GetTotalWeight(), 2);
  EXPECT_EQ(table_C.GetTotalWeight(), 1);
}

TEST(DynamicProbabilityTableAtTest, MapsToCorrectValue) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, 2, 3});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1);
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 2);
  EXPECT_EQ(table_A.At(5), 2);
  EXPECT_EQ(table_A.At(6), 2);
}