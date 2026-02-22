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

#ifndef GAME_DICE_CPP_SRC_DISTRIBUTIONFACTORY_H
#define GAME_DICE_CPP_SRC_DISTRIBUTIONFACTORY_H
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <utility>

#include "./RoundingPolicies.h"

namespace game_dice_cpp {

// Generates a Triangular Probability Distribution.
//
// Template Parameters:
// - desired_size: the number of outcomes in the distribution.
// - RoundingPolicy: A policy struct defining a Round(double) method.
//                   Defaults to StandardRoundingPolicy.
template <std::size_t desired_size,
          typename RoundingPolicy = game_dice_cpp::StandardRoundingPolicy>
[[nodiscard]] constexpr std::array<int, desired_size> TriangleDistribution(
    std::size_t peak_index, int peak_weight) {
  // handle input argument sizes with static_asserts
  // handle the empty case
  if constexpr (desired_size == 0) {
    return {};
  } else {
    // force peak_weight to be at least 1 so that 0 probabilities cannot be used
    const int safe_peak_weight = std::max(peak_weight, 1);
    // force peak_index to be within bounds
    const int safe_peak_index = static_cast<int>(
        std::clamp(peak_index, std::size_t{0}, desired_size - 1));
    // create an empty array
    std::array<int, desired_size> out_weights{};
    // write values to out_weights
    for (std::size_t i = 0; i < desired_size; ++i) {
      double value = 0.0;
      if (std::cmp_equal(i, safe_peak_index)) {
        // this is the peak
        value = static_cast<double>(safe_peak_weight);
      } else if (std::cmp_less(i, safe_peak_index)) {
        // rising slope
        const double slope_ratio =
            static_cast<double>(i) / static_cast<double>(safe_peak_index);
        value = 1 + ((safe_peak_weight - 1) * slope_ratio);
      } else {
        // falling slope
        const double slope_ratio =
            static_cast<double>(i - safe_peak_index) /
            static_cast<double>(desired_size - 1 - safe_peak_index);
        value = safe_peak_weight - ((safe_peak_weight - 1) * slope_ratio);
      }
      // write the value using the provided RoundingPolicy
      out_weights[i] = RoundingPolicy::Round(value);
    }
    return out_weights;
  }
};

// TODO(scholar_of_artifice): Make a Binomial Distribution
// std::vector<int> BinomialDistribution(int n, double k) {};

// TODO(scholar_of_artifice): Make a Poisson Distribution
// std::vector<int> PoissonDistribution(int n, double k) {};
}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_DISTRIBUTIONFACTORY_H
