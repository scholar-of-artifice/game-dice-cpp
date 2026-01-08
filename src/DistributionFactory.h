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
#include <random>
#include <ranges>
#include <vector>

namespace game_dice_cpp {
// TODO: Make a Triangle Distribution
std::vector<int> TriangleDistribution(int desired_size, int peak_index,
                                      int peak_weight) {
  // check if desired_size is below acceptable value
  if (desired_size <= 0 || desired_size <= peak_index ||
      peak_index > desired_size) {
    return {};
  }
  // force peak_weight to be at least 1 so that 0 probabilities cannot be used
  peak_weight = std::clamp(peak_weight, 1, peak_weight);
  // force peak_index to be within bounds
  peak_index = std::clamp(peak_index, 0, desired_size - 1);
  // create an empty vector with reserved size
  std::vector<int> out_weights;
  out_weights.reserve(desired_size);
  // write values to out_weights
  for (int i = 0; i < desired_size; ++i) {
    double value = 0.0;
    if (i == peak_index) {
      // this is the peak
      value = static_cast<double>(peak_weight);
    } else if (i < peak_index) {
      // rising slope
      double slope_ratio =
          static_cast<double>(i) / static_cast<double>(peak_index);
      value = 1 + (peak_weight - 1) * slope_ratio;
    } else {
      // falling slope
      double slope_ratio = static_cast<double>(i - peak_index) /
                           static_cast<double>(desired_size - 1 - peak_index);
      value = peak_weight - (peak_weight - 1) * slope_ratio;
    }
    // write the value
    out_weights.push_back(static_cast<int>(std::round(value)));
  }
  return out_weights;
};
// TODO: Make a Bernoulli Distribution
// TODO: Make a Binomial Distribution
// std::vector<int> BinomialWeights(int n, double k) {
//   std::binomial_distribution<int> d(n, static_cast<double>(k));
// };

// TODO: Make a Poisson Distribution
}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_DISTRIBUTIONFACTORY_H
