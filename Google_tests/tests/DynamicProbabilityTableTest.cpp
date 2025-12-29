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

TEST(DynamicProbabilityTableTest, ConstructorWithEmptyWeightsHas0TotalWeight) {
  // GIVEN a table defined with no weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 0);
}

TEST(DynamicProbabilityTableTest, AtWithEmptyWeightsReturnsCorrectIndexes) {
  // GIVEN a table defined with no weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({});
  // WHEN At is called
  // THEN a negative (out of bounds index) returns 0
  EXPECT_EQ(table_A.At(-1), 0);
  // AND a 0 (in bounds index) returns 0
  EXPECT_EQ(table_A.At(0), 0);
  // AND a positive (out of bounds index) returns 0
  EXPECT_EQ(table_A.At(1), 0);
}

TEST(DynamicProbabilityTableTest,
     ConstructorWithSortedPositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with sorted positive weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({1, 2});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, 2, 3});
  const auto table_D = game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4});
  const auto table_E = game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4, 5});
  const auto table_F =
      game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4, 5, 6});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_EQ(table_A.GetTotalWeight(), 1);
  EXPECT_EQ(table_B.GetTotalWeight(), 3);
  EXPECT_EQ(table_C.GetTotalWeight(), 6);
  EXPECT_EQ(table_D.GetTotalWeight(), 10);
  EXPECT_EQ(table_E.GetTotalWeight(), 15);
  EXPECT_EQ(table_F.GetTotalWeight(), 21);
}

TEST(DynamicProbabilityTableTest,
     AtWithAllSortedPositiveWeightsReturnsCorrectIndexes) {
  // GIVEN a table defined with sorted positive weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({1, 2});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, 2, 3});
  const auto table_D = game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4});
  const auto table_E = game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4, 5});
  const auto table_F =
      game_dice_cpp::DynamicProbabilityTable({1, 2, 3, 4, 5, 6});
  // WHEN At is called
  // the following outputs are observed...
  // Table A
  EXPECT_EQ(table_A.At(-1), 0);
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1); // Table A - bound
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 1);
  EXPECT_EQ(table_A.At(5), 1);
  EXPECT_EQ(table_A.At(6), 1);
  EXPECT_EQ(table_A.At(7), 1);
  EXPECT_EQ(table_A.At(8), 1);
  EXPECT_EQ(table_A.At(9), 1);
  EXPECT_EQ(table_A.At(10), 1);
  EXPECT_EQ(table_A.At(11), 1);
  EXPECT_EQ(table_A.At(12), 1);
  EXPECT_EQ(table_A.At(13), 1);
  EXPECT_EQ(table_A.At(14), 1);
  EXPECT_EQ(table_A.At(15), 1);
  EXPECT_EQ(table_A.At(16), 1);
  EXPECT_EQ(table_A.At(17), 1);
  EXPECT_EQ(table_A.At(18), 1);
  EXPECT_EQ(table_A.At(19), 1);
  EXPECT_EQ(table_A.At(20), 1);
  EXPECT_EQ(table_A.At(21), 1);
  EXPECT_EQ(table_A.At(22), 1);
  // Table B
  EXPECT_EQ(table_B.At(-1), 0);
  EXPECT_EQ(table_B.At(0), 0);
  EXPECT_EQ(table_B.At(1), 0);
  EXPECT_EQ(table_B.At(2), 1);
  EXPECT_EQ(table_B.At(3), 1); // Table B - bound
  EXPECT_EQ(table_B.At(4), 2);
  EXPECT_EQ(table_B.At(5), 2);
  EXPECT_EQ(table_B.At(6), 2);
  EXPECT_EQ(table_B.At(7), 2);
  EXPECT_EQ(table_B.At(8), 2);
  EXPECT_EQ(table_B.At(9), 2);
  EXPECT_EQ(table_B.At(10), 2);
  EXPECT_EQ(table_B.At(11), 2);
  EXPECT_EQ(table_B.At(12), 2);
  EXPECT_EQ(table_B.At(13), 2);
  EXPECT_EQ(table_B.At(14), 2);
  EXPECT_EQ(table_B.At(15), 2);
  EXPECT_EQ(table_B.At(16), 2);
  EXPECT_EQ(table_B.At(17), 2);
  EXPECT_EQ(table_B.At(18), 2);
  EXPECT_EQ(table_B.At(19), 2);
  EXPECT_EQ(table_B.At(20), 2);
  EXPECT_EQ(table_B.At(21), 2);
  EXPECT_EQ(table_B.At(22), 2);
  // Table C
  EXPECT_EQ(table_C.At(-1), 0);
  EXPECT_EQ(table_C.At(0), 0);
  EXPECT_EQ(table_C.At(1), 0);
  EXPECT_EQ(table_C.At(2), 1);
  EXPECT_EQ(table_C.At(3), 1);
  EXPECT_EQ(table_C.At(4), 2);
  EXPECT_EQ(table_C.At(5), 2);
  EXPECT_EQ(table_C.At(6), 2);  // Table C - bound
  EXPECT_EQ(table_C.At(7), 3);
  EXPECT_EQ(table_C.At(8), 3);
  EXPECT_EQ(table_C.At(9), 3);
  EXPECT_EQ(table_C.At(10), 3);
  EXPECT_EQ(table_C.At(11), 3);
  EXPECT_EQ(table_C.At(12), 3);
  EXPECT_EQ(table_C.At(13), 3);
  EXPECT_EQ(table_C.At(14), 3);
  EXPECT_EQ(table_C.At(15), 3);
  EXPECT_EQ(table_C.At(16), 3);
  EXPECT_EQ(table_C.At(17), 3);
  EXPECT_EQ(table_C.At(18), 3);
  EXPECT_EQ(table_C.At(19), 3);
  EXPECT_EQ(table_C.At(20), 3);
  EXPECT_EQ(table_C.At(21), 3);
  EXPECT_EQ(table_C.At(22), 3);
  // Table D
  EXPECT_EQ(table_D.At(-1), 0);
  EXPECT_EQ(table_D.At(0), 0);
  EXPECT_EQ(table_D.At(1), 0);
  EXPECT_EQ(table_D.At(2), 1);
  EXPECT_EQ(table_D.At(3), 1);
  EXPECT_EQ(table_D.At(4), 2);
  EXPECT_EQ(table_D.At(5), 2);
  EXPECT_EQ(table_D.At(6), 2);
  EXPECT_EQ(table_D.At(7), 3);
  EXPECT_EQ(table_D.At(8), 3);
  EXPECT_EQ(table_D.At(9), 3);
  EXPECT_EQ(table_D.At(10), 3); // Table D - bound
  EXPECT_EQ(table_D.At(11), 4);
  EXPECT_EQ(table_D.At(12), 4);
  EXPECT_EQ(table_D.At(13), 4);
  EXPECT_EQ(table_D.At(14), 4);
  EXPECT_EQ(table_D.At(15), 4);
  EXPECT_EQ(table_D.At(16), 4);
  EXPECT_EQ(table_D.At(17), 4);
  EXPECT_EQ(table_D.At(18), 4);
  EXPECT_EQ(table_D.At(19), 4);
  EXPECT_EQ(table_D.At(20), 4);
  EXPECT_EQ(table_D.At(21), 4);
  EXPECT_EQ(table_D.At(22), 4);
  // Table E
  EXPECT_EQ(table_E.At(-1), 0);
  EXPECT_EQ(table_E.At(0), 0);
  EXPECT_EQ(table_E.At(1), 0);
  EXPECT_EQ(table_E.At(2), 1);
  EXPECT_EQ(table_E.At(3), 1);
  EXPECT_EQ(table_E.At(4), 2);
  EXPECT_EQ(table_E.At(5), 2);
  EXPECT_EQ(table_E.At(6), 2);
  EXPECT_EQ(table_E.At(7), 3);
  EXPECT_EQ(table_E.At(8), 3);
  EXPECT_EQ(table_E.At(9), 3);
  EXPECT_EQ(table_E.At(10), 3);
  EXPECT_EQ(table_E.At(11), 4);
  EXPECT_EQ(table_E.At(12), 4);
  EXPECT_EQ(table_E.At(13), 4);
  EXPECT_EQ(table_E.At(14), 4);
  EXPECT_EQ(table_E.At(15), 4); // Table E - bound
  EXPECT_EQ(table_E.At(16), 5);
  EXPECT_EQ(table_E.At(17), 5);
  EXPECT_EQ(table_E.At(18), 5);
  EXPECT_EQ(table_E.At(19), 5);
  EXPECT_EQ(table_E.At(20), 5);
  EXPECT_EQ(table_E.At(21), 5);
  EXPECT_EQ(table_E.At(22), 5);
  // Table F
  EXPECT_EQ(table_F.At(-1), 0);
  EXPECT_EQ(table_F.At(0), 0);
  EXPECT_EQ(table_F.At(1), 0);
  EXPECT_EQ(table_F.At(2), 1);
  EXPECT_EQ(table_F.At(3), 1);
  EXPECT_EQ(table_F.At(4), 2);
  EXPECT_EQ(table_F.At(5), 2);
  EXPECT_EQ(table_F.At(6), 2);
  EXPECT_EQ(table_F.At(7), 3);
  EXPECT_EQ(table_F.At(8), 3);
  EXPECT_EQ(table_F.At(9), 3);
  EXPECT_EQ(table_F.At(10), 3);
  EXPECT_EQ(table_F.At(11), 4);
  EXPECT_EQ(table_F.At(12), 4);
  EXPECT_EQ(table_F.At(13), 4);
  EXPECT_EQ(table_F.At(14), 4);
  EXPECT_EQ(table_F.At(15), 4);
  EXPECT_EQ(table_F.At(16), 5);
  EXPECT_EQ(table_F.At(17), 5);
  EXPECT_EQ(table_F.At(18), 5);
  EXPECT_EQ(table_F.At(19), 5);
  EXPECT_EQ(table_F.At(20), 5);
  EXPECT_EQ(table_F.At(21), 5); // Table F - bound
  EXPECT_EQ(table_F.At(22), 6);
}

TEST(DynamicProbabilityTableTest,
     ConstructorWithUnsortedPositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with unsorted positive weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, 2, 1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({2, 1, 1});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, 1, 2});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_EQ(table_A.GetTotalWeight(), 4);
  EXPECT_EQ(table_B.GetTotalWeight(), 4);
  EXPECT_EQ(table_C.GetTotalWeight(), 4);
}

TEST(DynamicProbabilityTableTest,
     AtWithUnsortedPositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with unsorted positive weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, 2, 1});
  const auto table_B = game_dice_cpp::DynamicProbabilityTable({2, 1, 1});
  const auto table_C = game_dice_cpp::DynamicProbabilityTable({1, 1, 2});
  // WHEN At is called
  // THEN the correct index is returned
  // Table A
  EXPECT_EQ(table_A.At(-1), 0);
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(1), 0);
  EXPECT_EQ(table_A.At(2), 1);
  EXPECT_EQ(table_A.At(3), 1);
  EXPECT_EQ(table_A.At(4), 2);
  EXPECT_EQ(table_A.At(5), 3);
  // Table B
  EXPECT_EQ(table_B.At(-1), 0);
  EXPECT_EQ(table_B.At(0), 0);
  EXPECT_EQ(table_B.At(1), 0);
  EXPECT_EQ(table_B.At(2), 0);
  EXPECT_EQ(table_B.At(3), 1);
  EXPECT_EQ(table_B.At(4), 2);
  EXPECT_EQ(table_B.At(5), 3);
  // Table C
  EXPECT_EQ(table_C.At(-1), 0);
  EXPECT_EQ(table_C.At(0), 0);
  EXPECT_EQ(table_C.At(1), 0);
  EXPECT_EQ(table_C.At(2), 1);
  EXPECT_EQ(table_C.At(3), 2);
  EXPECT_EQ(table_C.At(4), 2);
  EXPECT_EQ(table_C.At(5), 3);
}

TEST(DynamicProbabilityTableTest, AllNegativeWeightsHasTotalWeightOfZero) {
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

TEST(DynamicProbabilityTableTest, MixedSignWeightsHasTotalWeightOfZero) {
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

TEST(DynamicProbabilityTableTest, AllZeroWeightsHasTheCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  // AND all weights are positive
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({0, 0, 0, 0, 0});
  // WHEN total_weight is called
  // THEN the total weight matches the sum of inputs
  EXPECT_EQ(table_A.GetTotalWeight(), 0);
}

TEST(DynamicProbabilityTableTest, MapsToCorrectValue) {
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

TEST(DynamicProbabilityTableTest, OutOfBoundsLookup) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::DynamicProbabilityTable({1, 2, 3});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(-1), 0);
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(10), 3);
}

TEST(DynamicProbabilityTableTest, HandlesLargeSafeWeights) {
  // GIVEN a table defined with known weights
  const auto half_max = std::numeric_limits<int>::max() / 2;
  const auto table_A =
      game_dice_cpp::DynamicProbabilityTable({half_max, half_max});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A.At(0), 0);
  EXPECT_EQ(table_A.At(half_max + 1), 1);
}

// TODO: integer overflow safety