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

#ifndef GAME_DICE_CPP_SRC_DYNAMICPROBABILITYTABLE_H
#define GAME_DICE_CPP_SRC_DYNAMICPROBABILITYTABLE_H
#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

namespace game_dice_cpp {
// A data structure that maps a linear range [1, N] to a set of weight indexes.
//
// You should choose DynamicProbabilityTable when the number of outcomes is
// unknown until the game runs.
//
// Examples include:
// - loading from external files
// - variable-state mechanics
// - modding support
//
// You should choose DynamicProbabilityTable if flexibility is more important
// than raw memory performance.
class DynamicProbabilityTable {
 private:
  // Cumulative upper bounds.
  std::vector<int> thresholds_;
  int total_weight_;

 public:
  // Explicit Weight Initialization
  // The user must define exactly the "shape" of the probability distribution.
  explicit DynamicProbabilityTable(const std::vector<int>& weights)
      : total_weight_(0) {
    // create a view that sees only non-negative weights
    auto safe_weights = weights | std::ranges::views::transform(
                                      [](int w) { return std::max(w, 0); });
    // fill the thresholds vector using the standard algorithm
    thresholds_.reserve(weights.size());
    std::partial_sum(safe_weights.begin(), safe_weights.end(),
                     std::back_inserter(thresholds_));
    // the total is simply the final threshold... or 0 if it was empty
    total_weight_ = thresholds_.empty() ? 0 : thresholds_.back();
  }

  // Returns the exact die size required to drive this table.
  [[nodiscard]] int GetTotalWeight() const { return total_weight_; }

  // Maps a value (example: from a die roll) to an outcome index.
  [[nodiscard]] int At(int value) const {
    const auto iter =
        std::lower_bound(thresholds_.begin(), thresholds_.end(), value);
    return static_cast<int>(std::distance(thresholds_.begin(), iter));
  }
};
}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_DYNAMICPROBABILITYTABLE_H
