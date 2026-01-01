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

TEST(DistributionFactoryTest, TriangleDistributionWithAnyLengthHasCorrectSize) {
  for (int desired_size = 1; desired_size < 100; desired_size++) {
    // GIVEN a desired_size...
    // AND a peak_index
    // AND a peak_weight
    auto peak_index = static_cast<int>(std::floor(desired_size / 2));
    auto peak_weight = desired_size;
    // WHEN a Triangle Distribution is made...
    auto calculated_output = game_dice_cpp::TriangleDistribution(
        desired_size, peak_index, peak_weight);
    // THEN the new distribution has the correct size
    EXPECT_EQ(calculated_output.size(), desired_size);
  }
}

TEST(DistributionFactoryTest,
     TriangleDistributionWithSpecificInputsHasCorrectValues) {
  // GIVEN a known set of inputs...
  // AND the number_of_weights is even
  // AND the pivot moves
  // WHEN a Triangle Distribution is made...
  // THEN the new distribution is correct

  // Case A
  auto calculated_output_A = game_dice_cpp::TriangleDistribution(4, 0, 5);
  auto expected_output_A = {5, 4, 3, 1};
  for (auto entry :
       std::ranges::zip_view(calculated_output_A, expected_output_A)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry));
  }
  // Case B
  auto calculated_output_B = game_dice_cpp::TriangleDistribution(4, 1, 5);
  auto expected_output_B = {1, 5, 3, 1};
  for (auto entry :
       std::ranges::zip_view(calculated_output_B, expected_output_B)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry));
  }
  // Case C
  auto calculated_output_C = game_dice_cpp::TriangleDistribution(4, 2, 5);
  auto expected_output_C = {1, 3, 5, 1};
  for (auto entry :
       std::ranges::zip_view(calculated_output_C, expected_output_C)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry));
  }
  // Case D
  auto calculated_output_D = game_dice_cpp::TriangleDistribution(4, 3, 5);
  auto expected_output_D = {1, 3, 4, 5};
  for (auto entry :
       std::ranges::zip_view(calculated_output_D, expected_output_D)) {
    EXPECT_EQ(std::get<0>(entry), std::get<1>(entry));
  }
}
