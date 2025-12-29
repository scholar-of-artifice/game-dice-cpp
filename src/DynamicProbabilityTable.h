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
#include <optional>
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

  // Explicit Weight Initialization
  // The user must define exactly the "shape" of the probability distribution.
  explicit DynamicProbabilityTable(std::vector<int>&& thresholds)
      : thresholds_(std::move(thresholds)) {}

 public:
  //
  [[nodiscard]] static std::optional<game_dice_cpp::DynamicProbabilityTable>
  Make(const std::vector<int>& weights) {
    // pre-allocate storage
    std::vector<int> calculated_thresholds;
    calculated_thresholds.reserve(weights.size());
    // create a view that sees only non-negative weights
    auto safe_weights = weights | std::ranges::views::transform(
                                      [](int w) { return std::max(w, 0); });
    std::partial_sum(safe_weights.begin(), safe_weights.end(),
                     std::back_inserter(calculated_thresholds));
    // check if the thresholds do not exist or sum to nothing
    if (calculated_thresholds.empty() || calculated_thresholds.back() <= 0) {
      return std::nullopt;
    }
    // construct and return
    return DynamicProbabilityTable(std::move(calculated_thresholds));
  }
  // Returns the exact die size required to drive this table.
  [[nodiscard]] int GetTotalWeight() const { return thresholds_.back(); }

  // Maps a value (example: from a die roll) to an outcome index.
  [[nodiscard]] int At(int value) const {
    // binary search for the value
    const auto iter =
        std::lower_bound(thresholds_.begin(), thresholds_.end(), value);
    // clamp value within range of table
    if (iter == thresholds_.end()) {
      // this case happens when the input value is greater than the total_weight
      return static_cast<int>(thresholds_.size() - 1);
    }
    return static_cast<int>(std::distance(thresholds_.begin(), iter));
  }
};
}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_DYNAMICPROBABILITYTABLE_H
