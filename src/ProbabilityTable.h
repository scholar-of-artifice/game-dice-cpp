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

#ifndef GAME_DICE_CPP_SRC_PROBABILITYTABLE_H
#define GAME_DICE_CPP_SRC_PROBABILITYTABLE_H
#include <vector>

namespace game_dice_cpp {
// A datstructure that maps a linear range [1, N] to a set of weight indeces.
//
// The ProbabilityTable enforces "Explicity Probability".
// As a user, you must provide integer weights. This guarantees that no outcome
// witha  weight > 0 can be "rounded out" of existence.
template <int TotalWeight>
class ProbabilityTable {
 private:
  // Cumulative upper bounds.
  std::vector<int> thresholds_;
  int total_weight_;

 public:
  // Explicit Weight Initialization
  // The user must define exactly the "shape" of the probability distribution.
  explicit ProbabilityTable(const std::vector<int>& weights)
      : total_weight_(0) {
    thresholds_.reserve(weights.size());
    for (const auto& w : weights) {
      auto safe_weight = std::max(w, 0);
      total_weight_ += safe_weight;
      thresholds_.push_back(total_weight_);
    }
  }

  // Returns the exact die size required to drive this table.
  [[nodiscard]] int total_weight() const { return total_weight_; }

  // Maps a value (example: from a die roll) to an outcome index.
  [[nodiscard]] int Map(int value) const {
    const auto iter = std::lower_bound(thresholds_.begin(), thresholds_.end(), value);
    return static_cast<int>(std::distance(thresholds_.begin(), iter));
  }
};
}  // namespace game_dice_cpp

#endif  // PROBABILITYTABLE_H
