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

#include <gtest/gtest.h>

#include "StaticProbabilityTable.h"

TEST(StaticProbabilityTableTest, MakeWithEmptyWeightsReturnsNullOpt) {
  // GIVEN a table defined with no weights
  // WHEN Make is called
  // THEN there is nothing returned
  const auto table_A = game_dice_cpp::StaticProbabilityTable<0>::Make({});
  EXPECT_FALSE(table_A.has_value());
}

TEST(StaticProbabilityTableTest, MakeWithAllZeroWeightsReturnsNullOpt) {
  // GIVEN a table defined with zero weights
  // THEN the total weight matches the sum of input values
  // WHEN Make is called
  // THEN there is nothing returned
  const auto table_A = game_dice_cpp::StaticProbabilityTable<1>::Make({0});
  const auto table_B = game_dice_cpp::StaticProbabilityTable<2>::Make({0, 0});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({0, 0, 0});
  EXPECT_FALSE(table_A.has_value());
  EXPECT_FALSE(table_B.has_value());
  EXPECT_FALSE(table_C.has_value());
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithSparsePositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with positive weights and zeros
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({0, 2, 3});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 0, 3});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 0});

  EXPECT_TRUE(table_A.has_value());
  EXPECT_TRUE(table_B.has_value());
  EXPECT_TRUE(table_C.has_value());

  EXPECT_EQ(table_A->GetTotalWeight(), 5);
  EXPECT_EQ(table_B->GetTotalWeight(), 4);
  EXPECT_EQ(table_C->GetTotalWeight(), 3);
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexTotalWeightWithSparsePositiveWeightsReturnsCorrectIndexes) {
  // GIVEN a table defined with positive weights and zeros
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({0, 2, 3});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 0, 3});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 0});
  // Table A
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(3), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(5), 2);  // Table A - bound
  EXPECT_EQ(table_A->GetOutcomeIndex(6), 2);
  // Table B
  EXPECT_EQ(table_B->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(2), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(3), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(4), 2);  // Table B - bound
  EXPECT_EQ(table_B->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(6), 2);
  // Table C
  EXPECT_EQ(table_C->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_C->GetOutcomeIndex(3), 1);  // Table C - bound
  EXPECT_EQ(table_C->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(6), 2);
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithSortedPositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with sorted positive weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<1>::Make({1});
  const auto table_B = game_dice_cpp::StaticProbabilityTable<2>::Make({1, 2});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 3});
  const auto table_D =
      game_dice_cpp::StaticProbabilityTable<4>::Make({1, 2, 3, 4});
  const auto table_E =
      game_dice_cpp::StaticProbabilityTable<5>::Make({1, 2, 3, 4, 5});
  const auto table_F =
      game_dice_cpp::StaticProbabilityTable<6>::Make({1, 2, 3, 4, 5, 6});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_EQ(table_A->GetTotalWeight(), 1);
  EXPECT_EQ(table_B->GetTotalWeight(), 3);
  EXPECT_EQ(table_C->GetTotalWeight(), 6);
  EXPECT_EQ(table_D->GetTotalWeight(), 10);
  EXPECT_EQ(table_E->GetTotalWeight(), 15);
  EXPECT_EQ(table_F->GetTotalWeight(), 21);
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexWithAllSortedPositiveWeightsReturnsCorrectIndexes) {
  // GIVEN a table defined with sorted positive weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<1>::Make({1});
  const auto table_B = game_dice_cpp::StaticProbabilityTable<2>::Make({1, 2});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 3});
  const auto table_D =
      game_dice_cpp::StaticProbabilityTable<4>::Make({1, 2, 3, 4});
  const auto table_E =
      game_dice_cpp::StaticProbabilityTable<5>::Make({1, 2, 3, 4, 5});
  const auto table_F =
      game_dice_cpp::StaticProbabilityTable<6>::Make({1, 2, 3, 4, 5, 6});
  // WHEN At is called
  // the following outputs are observed...
  // Table A
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(2), 0);  // Table A - bound
  EXPECT_EQ(table_A->GetOutcomeIndex(3), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(4), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(5), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(6), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(7), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(8), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(9), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(10), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(11), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(12), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(13), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(14), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(15), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(16), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(17), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(18), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(19), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(20), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(21), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(22), 0);
  // Table B
  EXPECT_EQ(table_B->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(3), 1);  // Table B - bound
  EXPECT_EQ(table_B->GetOutcomeIndex(4), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(5), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(6), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(7), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(8), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(9), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(10), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(11), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(12), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(13), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(14), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(15), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(16), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(17), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(18), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(19), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(20), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(21), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(22), 1);
  // Table C
  EXPECT_EQ(table_C->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_C->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_C->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(6), 2);  // Table C - bound
  EXPECT_EQ(table_C->GetOutcomeIndex(7), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(8), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(9), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(10), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(11), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(12), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(13), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(14), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(15), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(16), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(17), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(18), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(19), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(20), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(21), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(22), 2);
  // Table D
  EXPECT_EQ(table_D->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_D->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_D->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_D->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_D->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_D->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_D->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_D->GetOutcomeIndex(6), 2);
  EXPECT_EQ(table_D->GetOutcomeIndex(7), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(8), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(9), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(10), 3);  // Table D - bound
  EXPECT_EQ(table_D->GetOutcomeIndex(11), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(12), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(13), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(14), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(15), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(16), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(17), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(18), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(19), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(20), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(21), 3);
  EXPECT_EQ(table_D->GetOutcomeIndex(22), 3);
  // Table E
  EXPECT_EQ(table_E->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_E->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_E->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_E->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_E->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_E->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_E->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_E->GetOutcomeIndex(6), 2);
  EXPECT_EQ(table_E->GetOutcomeIndex(7), 3);
  EXPECT_EQ(table_E->GetOutcomeIndex(8), 3);
  EXPECT_EQ(table_E->GetOutcomeIndex(9), 3);
  EXPECT_EQ(table_E->GetOutcomeIndex(10), 3);
  EXPECT_EQ(table_E->GetOutcomeIndex(11), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(12), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(13), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(14), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(15), 4);  // Table E - bound
  EXPECT_EQ(table_E->GetOutcomeIndex(16), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(17), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(18), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(19), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(20), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(21), 4);
  EXPECT_EQ(table_E->GetOutcomeIndex(22), 4);
  // Table F
  EXPECT_EQ(table_F->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_F->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_F->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_F->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_F->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_F->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_F->GetOutcomeIndex(5), 2);
  EXPECT_EQ(table_F->GetOutcomeIndex(6), 2);
  EXPECT_EQ(table_F->GetOutcomeIndex(7), 3);
  EXPECT_EQ(table_F->GetOutcomeIndex(8), 3);
  EXPECT_EQ(table_F->GetOutcomeIndex(9), 3);
  EXPECT_EQ(table_F->GetOutcomeIndex(10), 3);
  EXPECT_EQ(table_F->GetOutcomeIndex(11), 4);
  EXPECT_EQ(table_F->GetOutcomeIndex(12), 4);
  EXPECT_EQ(table_F->GetOutcomeIndex(13), 4);
  EXPECT_EQ(table_F->GetOutcomeIndex(14), 4);
  EXPECT_EQ(table_F->GetOutcomeIndex(15), 4);
  EXPECT_EQ(table_F->GetOutcomeIndex(16), 5);
  EXPECT_EQ(table_F->GetOutcomeIndex(17), 5);
  EXPECT_EQ(table_F->GetOutcomeIndex(18), 5);
  EXPECT_EQ(table_F->GetOutcomeIndex(19), 5);
  EXPECT_EQ(table_F->GetOutcomeIndex(20), 5);
  EXPECT_EQ(table_F->GetOutcomeIndex(21), 5);  // Table F - bound
  EXPECT_EQ(table_F->GetOutcomeIndex(22), 5);
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithUnsortedPositiveWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with unsorted positive weights
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 1});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({2, 1, 1});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 1, 2});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_EQ(table_A->GetTotalWeight(), 4);
  EXPECT_EQ(table_B->GetTotalWeight(), 4);
  EXPECT_EQ(table_C->GetTotalWeight(), 4);
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexWithUnsortedPositiveWeightsHasCorrectIndexes) {
  // GIVEN a table defined with unsorted positive weights
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 2, 1});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({2, 1, 1});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, 1, 2});
  // WHEN At is called
  // THEN the correct index is returned
  // Table A
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(5), 2);
  // Table B
  EXPECT_EQ(table_B->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(2), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(3), 1);
  EXPECT_EQ(table_B->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(5), 2);
  // Table C
  EXPECT_EQ(table_C->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_C->GetOutcomeIndex(2), 1);
  EXPECT_EQ(table_C->GetOutcomeIndex(3), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_C->GetOutcomeIndex(5), 2);
}

TEST(StaticProbabilityTableTest, MakeWithNegativeWeightsReturnsNullOpt) {
  // GIVEN a table defined with unsorted negative weights
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({-1, -2, -1});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({-2, -1, -1});
  const auto table_C =
      game_dice_cpp::StaticProbabilityTable<3>::Make({-1, -1, -2});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_FALSE(table_A.has_value());
  EXPECT_FALSE(table_B.has_value());
  EXPECT_FALSE(table_C.has_value());
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithUnsortedMixedSignWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with unsorted mixed signed weights
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, -2, 0});
  // WHEN GetTotalWeight is called
  // THEN the total weight matches the sum of input values
  EXPECT_EQ(table_A->GetTotalWeight(), 1);
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexWithUnsortedMixedSignWeightsHasCorrectIndexes) {
  // GIVEN a table defined with unsorted mixed signed weights
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, -2, 0});
  const auto table_B =
      game_dice_cpp::StaticProbabilityTable<3>::Make({1, -2, 1});
  // WHEN At is called
  // THEN the correct index is returned
  // Table A
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(2), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(3), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_A->GetOutcomeIndex(5), 2);
  // Table B
  EXPECT_EQ(table_B->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_B->GetOutcomeIndex(2), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(3), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(4), 2);
  EXPECT_EQ(table_B->GetOutcomeIndex(5), 2);
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithLargeWeightHasCorrectTotalWeight) {
  // GIVEN a table defined with a single large known weight
  const auto table_A = game_dice_cpp::StaticProbabilityTable<1>::Make(
      {std::numeric_limits<int>::max()});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A->GetTotalWeight(), 2147483647);
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexWithLargeWeightHasCorrectIndexes) {
  // GIVEN a table defined with a single large known weight
  const auto table_A = game_dice_cpp::StaticProbabilityTable<1>::Make(
      {std::numeric_limits<int>::max()});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(2147483647), 0);
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithLargeWeightsHasCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  const auto half_max = std::numeric_limits<int>::max() / 2;
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<2>::Make({half_max, half_max});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A->GetTotalWeight(), std::numeric_limits<int>::max() - 1);
  // TODO: consider if this actually a good idea
}

TEST(StaticProbabilityTableTest,
     GetOutcomeIndexWithLargeWeightsHasCorrectIndexes) {
  // GIVEN a table defined with known weights
  const auto half_max = std::numeric_limits<int>::max() / 2;
  const auto table_A =
      game_dice_cpp::StaticProbabilityTable<2>::Make({half_max, half_max});
  // WHEN At is called
  // THEN the returns the correct value from the table
  EXPECT_EQ(table_A->GetOutcomeIndex(-1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(0), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(1), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(half_max), 0);
  EXPECT_EQ(table_A->GetOutcomeIndex(half_max + 1), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(half_max * 2 - 1), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(half_max * 2), 1);
  EXPECT_EQ(table_A->GetOutcomeIndex(half_max * 2 + 1), 1);
}

TEST(StaticProbabilityTableTest, MakeWithOverflowWeightsDoesNotConstruct) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<4>::Make(
      {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
       std::numeric_limits<int>::max(), -1230});
  // WHEN Make is called
  // THEN the returns the correct value from the table
  EXPECT_FALSE(table_A.has_value());
}

TEST(StaticProbabilityTableTest,
     GetTotalWeightWithLargeLargeInputSizeHasCorrectTotalWeight) {
  // GIVEN a table defined with known weights
  const auto table_A = game_dice_cpp::StaticProbabilityTable<220>::Make(
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
  // WHEN At is called
  // THEN it has the correct total weight
  EXPECT_EQ(table_A->GetTotalWeight(), 220);
}