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

#include <ranges>

#include "DistributionFactory.h"

TEST(DistributionFactoryTest,
     TriangleDistributionWithZeroLengthHasCorrectSize) {
  // GIVEN a zero desired_size...
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution has the correct size
  auto calculated_output = game_dice_cpp::TriangleDistribution<0>(0, 100);
  EXPECT_EQ(calculated_output.size(), 0);
}

TEST(DistributionFactoryTest, TriangleDistributionWithAnyLengthHasCorrectSize) {
  // GIVEN a desired_size...
  // AND a peak_index
  // AND a peak_weight
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution has the correct size
  // --- test case A ---
  auto calculated_output_A = game_dice_cpp::TriangleDistribution<8>(4, 10);
  EXPECT_EQ(calculated_output_A.size(), 8);
  // --- test case B ---
  auto calculated_output_B = game_dice_cpp::TriangleDistribution<25>(13, 10);
  EXPECT_EQ(calculated_output_B.size(), 25);
  // --- test case C ---
  auto calculated_output_C = game_dice_cpp::TriangleDistribution<130>(80, 100);
  EXPECT_EQ(calculated_output_C.size(), 130);
}

TEST(
    DistributionFactoryTest,
    TriangleDistributionWithVaryingDesiredSizePeakIdx5PeakWeight5HasCorrectValues) {
  // GIVEN a known set of inputs...
  // AND the desired_size varies
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution is correct

  // --- test case A
  std::array<int, 1> calculated_output_A =
      game_dice_cpp::TriangleDistribution<1>(5, 5);
  std::array<int, 1> expected_output_A = {5};
  EXPECT_EQ(calculated_output_A, expected_output_A)
      << "CASE A:\tMismatch found for input (1, 5, 5)";

  // --- test case B
  std::array<int, 2> calculated_output_B =
      game_dice_cpp::TriangleDistribution<2>(5, 5);
  std::array<int, 2> expected_output_B = {1, 5};
  EXPECT_EQ(calculated_output_B, expected_output_B)
      << "CASE B:\tMismatch found for input (2, 5, 5)";

  // --- test case C
  std::array<int, 3> calculated_output_C =
      game_dice_cpp::TriangleDistribution<3>(5, 5);
  std::array<int, 3> expected_output_C = {1, 3, 5};
  EXPECT_EQ(calculated_output_C, expected_output_C)
      << "CASE C:\tMismatch found for input (3, 5, 5)";

  // --- test case D
  std::array<int, 9> calculated_output_D =
      game_dice_cpp::TriangleDistribution<9>(5, 5);
  std::array<int, 9> expected_output_D = {1, 2, 3, 3, 4, 5, 4, 2, 1};
  EXPECT_EQ(calculated_output_D, expected_output_D)
      << "CASE D:\tMismatch found for input (9, 5, 5)";

  // --- test case E
  std::array<int, 10> calculated_output_E =
      game_dice_cpp::TriangleDistribution<10>(5, 5);
  std::array<int, 10> expected_output_E = {1, 2, 3, 3, 4, 5, 4, 3, 2, 1};
  EXPECT_EQ(calculated_output_E, expected_output_E)
      << "CASE E:\tMismatch found for input (10, 5, 5)";

  // --- test case F
  std::array<int, 15> calculated_output_F =
      game_dice_cpp::TriangleDistribution<15>(5, 5);
  std::array<int, 15> expected_output_F = {1, 2, 3, 3, 4, 5, 5, 4,
                                           4, 3, 3, 2, 2, 1, 1};
  EXPECT_EQ(calculated_output_F, expected_output_F)
      << "CASE F:\tMismatch found for input (15, 5, 5)";
}

TEST(
    DistributionFactoryTest,
    TriangleDistributionWithDesiredSize5VaryingPeakIdxPeakWeight5HasCorrectValues) {
  // GIVEN a known set of inputs...
  // AND the peak_idx varies
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution is correct

  // ---test case A
  std::array<int, 5> calculated_output_A =
      game_dice_cpp::TriangleDistribution<5>(0, 5);
  std::array<int, 5> expected_output_A = {5, 4, 3, 2, 1};
  EXPECT_EQ(calculated_output_A, expected_output_A)
      << "CASE A:\tMismatch found for input (5, 0, 5)";

  // --- test case B
  std::array<int, 5> calculated_output_B =
      game_dice_cpp::TriangleDistribution<5>(1, 5);
  std::array<int, 5> expected_output_B = {1, 5, 4, 2, 1};
  EXPECT_EQ(calculated_output_B, expected_output_B)
      << "CASE B:\tMismatch found for input (5, 1, 5)";

  // --- test case C
  std::array<int, 5> calculated_output_C =
      game_dice_cpp::TriangleDistribution<5>(2, 5);
  std::array<int, 5> expected_output_C = {1, 3, 5, 3, 1};
  EXPECT_EQ(calculated_output_C, expected_output_C)
      << "CASE C:\tMismatch found for input (5, 2, 5)";

  // --- test case D
  std::array<int, 5> calculated_output_D =
      game_dice_cpp::TriangleDistribution<5>(3, 5);
  std::array<int, 5> expected_output_D = {1, 2, 4, 5, 1};
  EXPECT_EQ(calculated_output_D, expected_output_D)
      << "CASE D:\tMismatch found for input (5, 3, 5)";

  // --- test case E
  std::array<int, 5> calculated_output_E =
      game_dice_cpp::TriangleDistribution<5>(4, 5);
  std::array<int, 5> expected_output_E = {1, 2, 3, 4, 5};
  EXPECT_EQ(calculated_output_E, expected_output_E)
      << "CASE E:\tMismatch found for input (5, 4, 5)";
}

TEST(
    DistributionFactoryTest,
    TriangleDistributionWithDesiredSize7PeakIdx4PeakWeightVaryingHasCorrectValues) {
  // GIVEN a known set of inputs...
  // AND the peak_weight varies
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution is correct

  // --- test case A
  std::array<int, 7> calculated_output_A =
      game_dice_cpp::TriangleDistribution<7>(4, 0);
  std::array<int, 7> expected_output_A = {1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(calculated_output_A, expected_output_A)
      << "CASE A:\tMismatch found for input (7,4,0)";

  // --- test case B
  std::array<int, 7> calculated_output_B =
      game_dice_cpp::TriangleDistribution<7>(4, 1);
  std::array<int, 7> expected_output_B = {1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(calculated_output_B, expected_output_B)
      << "CASE B:\tMismatch found for input (7, 4, 1) ";

  // --- test case C
  std::array<int, 7> calculated_output_C =
      game_dice_cpp::TriangleDistribution<7>(4, 2);
  std::array<int, 7> expected_output_C = {1, 1, 2, 2, 2, 2, 1};
  EXPECT_EQ(calculated_output_C, expected_output_C)
      << "CASE C:\tMismatch found for input (7,4,2)";

  // --- test case D
  std::array<int, 7> calculated_output_D =
      game_dice_cpp::TriangleDistribution<7>(4, 3);
  std::array<int, 7> expected_output_D = {1, 2, 2, 3, 3, 2, 1};
  EXPECT_EQ(calculated_output_D, expected_output_D)
      << "CASE D:\tMismatch found for input (7,4,3)";

  // --- test case E
  std::array<int, 7> calculated_output_E =
      game_dice_cpp::TriangleDistribution<7>(4, 10);
  std::array<int, 7> expected_output_E = {1, 3, 6, 8, 10, 6, 1};
  EXPECT_EQ(calculated_output_E, expected_output_E)
      << "CASE E:\tMismatch found for input (7,4,3)";
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithHugePeakIndexClampsToUpperBound) {
  // GIVEN desired_size of 5
  // AND a peak_index of SIZE_MAX
  // AND a peak_weight of 5
  // WHEN TriangleDistribution is called
  // THEN the peak should be clamped to the end (resulting in a rising slope)
  constexpr std::size_t desired_size = 5;
  const std::size_t huge_index = std::numeric_limits<std::size_t>::max();
  const int peak_weight = 5;
  auto calculated_output = game_dice_cpp::TriangleDistribution<desired_size>(
      huge_index, peak_weight);
  std::array<int, 5> expected_output = {1, 2, 3, 4, 5};
  EXPECT_EQ(calculated_output, expected_output)
      << "Mismatch found for input (5, SIZE_MAX, 5)";
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithUnderflowingPeakIndexClampsToUpperBound) {
  // GIVEN desired_size of 5
  // AND a peak_index of SIZE_MAX
  // AND a peak_weight of 5
  // WHEN TriangleDistribution is called
  // THEN the peak should be clamped to the end (resulting in a rising slope)
  constexpr std::size_t desired_size = 5;
  const std::size_t huge_index = -25;
  const int peak_weight = 5;
  auto calculated_output = game_dice_cpp::TriangleDistribution<desired_size>(
      huge_index, peak_weight);
  std::array<int, 5> expected_output = {1, 2, 3, 4, 5};
  EXPECT_EQ(calculated_output, expected_output)
      << "Mismatch found for input (5, -25, 5)";
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithOverflowingPeakIndexClampsToUpperBound) {
  // GIVEN desired_size of 5
  // AND a peak_index beyond SIZE_MAX
  // AND a peak_weight of 5
  // WHEN TriangleDistribution is called
  // THEN the peak should be clamped to the end (resulting in a rising slope)
  constexpr std::size_t desired_size = 5;
  const std::size_t overflowing_peak_weight = 2'200'000'000;
  const int peak_weight = 5;
  auto calculated_output = game_dice_cpp::TriangleDistribution<desired_size>(
      overflowing_peak_weight, peak_weight);
  std::array<int, 5> expected_output = {1, 2, 3, 4, 5};
  EXPECT_EQ(calculated_output, expected_output)
      << "Mismatch found for input (5, 2.2B, 5)";
}