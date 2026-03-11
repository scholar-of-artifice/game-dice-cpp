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
#include <cstddef>
#include <utility>

#include "./ConstExprMath.h"
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
            static_cast<double>(static_cast<long long>(i) -
                                static_cast<long long>(safe_peak_index)) /
            static_cast<double>(static_cast<long long>(desired_size) - 1 -
                                static_cast<long long>(safe_peak_index));
        value = safe_peak_weight - ((safe_peak_weight - 1) * slope_ratio);
      }
      // write the value using the provided RoundingPolicy
      out_weights[i] = RoundingPolicy::Round(value);
    }
    return out_weights;
  }
};

// TODO(scholar_of_artifice): Make a Binomial Distribution
template <std::size_t desired_size,
          typename RoundingPolicy = game_dice_cpp::StandardRoundingPolicy>
[[nodiscard]] constexpr std::array<int, desired_size> BinomialDistribution(
    double p, int weight_multiplier) {
  // TODO(scholar-of-artifice): This function needs to be broken down.
  // maximum allowed size of binomial distribuion
  constexpr std::size_t max_desired_size{512};
  // enforce size limits at compile time
  static_assert(desired_size > 0, "Distribution must have at least 1 outcome.");
  static_assert(desired_size <= max_desired_size,
                "Distribution size exceeds safe compile-time limits.");
  // enforce limits on p and weight_multiplier
  const double safe_p = std::clamp(p, 0.0, 1.0);
  const std::size_t n = desired_size - 1;
  // write values to this output array
  std::array<int, desired_size> out_weights{};
  // setup
  const int max_safe_int = std::numeric_limits<int>::max();
  const int target_total = std::clamp(
      weight_multiplier, static_cast<int>(desired_size), max_safe_int);
  // edge cases
  if constexpr (desired_size == 1) {
    out_weights.at(0) = target_total;
    return out_weights;
  }
  if (safe_p <= 0.0) {
    out_weights.fill(1);
    out_weights.at(0) = target_total - static_cast<int>(n);
    return out_weights;
  } else if (safe_p >= 1.0) {
    out_weights.fill(1);
    out_weights.at(n) = target_total - static_cast<int>(n);
    return out_weights;
  }
  // cumulative rounding logic
  // initialization
  const int pool = target_total - static_cast<int>(desired_size);
  double current_probability = game_dice_cpp::RaisePower(1.0 - safe_p, n);
  double cumulative_probability = current_probability;
  int previous_rounded_cumulative_probability = 0;
  int current_rounded_cumulative_probability =
      std::min(pool, RoundingPolicy::Round(cumulative_probability *
                                           static_cast<double>(pool)));
  out_weights.at(0) = 1 + current_rounded_cumulative_probability -
                      previous_rounded_cumulative_probability;
  previous_rounded_cumulative_probability =
      current_rounded_cumulative_probability;
  int allocated_weight = out_weights.at(0);
  const double probability_ratio = safe_p / (1.0 - safe_p);
  //
  for (std::size_t i = 1; i < n; ++i) {
    const double combinations_ratio =
        static_cast<double>(n - i + 1) / static_cast<double>(i);
    current_probability =
        current_probability * combinations_ratio * probability_ratio;
    cumulative_probability = cumulative_probability + current_probability;
    current_rounded_cumulative_probability =
        std::min(pool, RoundingPolicy::Round(cumulative_probability *
                                             static_cast<double>(pool)));
    // assign value to bin
    out_weights.at(i) = 1 + current_rounded_cumulative_probability -
                        previous_rounded_cumulative_probability;
    // ready variables for next iteration
    previous_rounded_cumulative_probability =
        current_rounded_cumulative_probability;
    allocated_weight = allocated_weight + out_weights.at(i);
  }
  // final bin weight
  out_weights.at(n) = target_total - allocated_weight;
  return out_weights;
};

// TODO(scholar_of_artifice): Make a Poisson Distribution
// std::vector<int> PoissonDistribution(int n, double k) {};
}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_DISTRIBUTIONFACTORY_H
