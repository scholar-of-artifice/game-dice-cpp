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

#include "DistributionFactory.h"

TEST(DistributionFactoryTest,
     TriangleDistributionWithNegativeLengthHasCorrectSize) {
  // GIVEN a negative desired_size...
  // WHEN a Triangle Distribution is made...
  auto calculated_output = game_dice_cpp::TriangleDistribution(-10, -20, 100);
  // THEN the new distribution has the correct size
  EXPECT_EQ(calculated_output.size(), 0);
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithZeroLengthHasCorrectSize) {
  // GIVEN a zero desired_size...
  // WHEN a Triangle Distribution is made...
  auto calculated_output = game_dice_cpp::TriangleDistribution(0, -10, 100);
  // THEN the new distribution has the correct size
  EXPECT_EQ(calculated_output.size(), 0);
}

TEST(DistributionFactoryTest, TriangleDistributionWithAnyLengthHasCorrectSize) {
  for (int desired_size = 1; desired_size < 100; desired_size++) {
    // GIVEN a desired_size...
    // AND a peak_index
    // AND a peak_weight
    auto peak_index = static_cast<int>(std::floor(desired_size / 2));
    auto peak_weight = desired_size;
    // WHEN a Triangle Distribution is made...
    auto calculated_output = game_dice_cpp::TriangleDistribution(
        desired_size, desired_size, desired_size);
    // THEN the new distribution has the correct size
    EXPECT_EQ(calculated_output.size(), desired_size);
  }
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithNegativeDesiredSizeReturnsEmptyContainer) {
  // GIVEN a desired_size of -1
  auto desired_size = -1;
  // WHEN a Triangle Distribution is made...
  auto calculated_output = game_dice_cpp::TriangleDistribution(
      desired_size, desired_size, desired_size);
  // THEN the new distribution has the correct size
  EXPECT_EQ(calculated_output.size(), 0);
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithZeroDesiredSizeReturnsEmptyContainer) {
  // GIVEN a desired_size of 0
  auto desired_size = 0;
  // WHEN a Triangle Distribution is made...
  auto calculated_output = game_dice_cpp::TriangleDistribution(
      desired_size, desired_size, desired_size);
  // THEN the new distribution has the correct size
  EXPECT_EQ(calculated_output.size(), 0);
}

TEST(
    DistributionFactoryTest,
    TriangleDistributionWithVaryingDesiredSizePeakIdx5PeakWeight5HasCorrectValues) {
  // GIVEN a known set of inputs...
  // AND the number_of_weights is even
  // AND the pivot moves
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution is correct

  // Case A
  auto calculated_output = game_dice_cpp::TriangleDistribution(1, 5, 5);
  auto expected_output = {5};

  size_t idx = 0;
  for (auto entry : std::ranges::zip_view(calculated_output, expected_output)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry))
        << "Mismatch found at index = " << idx << " for input (1, 5, 5)";
    ++idx;
  }

  // Case B
  calculated_output = game_dice_cpp::TriangleDistribution(9, 5, 5);
  expected_output = {1, 2, 3, 3, 4, 5, 4, 2, 1};

  idx = 0;
  for (auto entry : std::ranges::zip_view(calculated_output, expected_output)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry))
        << "Mismatch found at index = " << idx << " for input (10, 5, 5)";
    ++idx;
  }

  // Case C
  calculated_output = game_dice_cpp::TriangleDistribution(10, 5, 5);
  expected_output = {1, 2, 3, 3, 4, 5, 4, 3, 2, 1};

  idx = 0;
  for (auto entry : std::ranges::zip_view(calculated_output, expected_output)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry))
        << "Mismatch found at index = " << idx << " for input (10, 5, 5)";
    ++idx;
  }

  // Case D
  calculated_output = game_dice_cpp::TriangleDistribution(15, 5, 5);
  expected_output = {1, 2, 3, 3, 4, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};

  idx = 0;
  for (auto entry : std::ranges::zip_view(calculated_output, expected_output)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry))
        << "Mismatch found at index = " << idx << " for input (15, 5, 5)";
    ++idx;
  }
}
