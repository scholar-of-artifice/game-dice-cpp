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

#include <vector>

#include "RoundingPolicies.h"

TEST(StandardRoundingPolicyTest, RoundReturnsLowerValue) {
  // GIVEN an input value below 3.5
  // WHEN Round is called
  // THEN the output is 3
  const std::vector<double> values = {3,    3.0000000000001, 3.1, 3.2, 3.3, 3.4,
                                      3.49, 3.4999999999999};
  const int expected_output = 3;
  for (const double input_value : values) {
    const auto calculated_output =
        game_dice_cpp::StandardRoundingPolicy::Round(input_value);
    EXPECT_EQ(calculated_output, expected_output);
  }
}

TEST(StandardRoundingPolicyTest, RoundReturnsHigherValue) {
  // GIVEN an input value above 3.5
  // WHEN Round is called
  // THEN the output is 4
  const std::vector<double> values = {
      3.5, 3.6, 3.7, 3.8, 3.9, 3.999, 3.999999999999999};
  const int expected_output = 4;
  for (const double input_value : values) {
    const auto calculated_output =
        game_dice_cpp::StandardRoundingPolicy::Round(input_value);
    EXPECT_EQ(calculated_output, expected_output);
  }
}
