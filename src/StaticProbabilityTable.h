//
// Created by dev on 28/12/2025.
//

#ifndef GAME_DICE_CPP_SRC_STATICPROBABILITYTABLE_H
#define GAME_DICE_CPP_SRC_STATICPROBABILITYTABLE_H
#include <algorithm>
#include <array>
#include <concepts>
#include <iterator>
#include <numeric>

namespace game_dice_cpp {

template <size_t NumberOfOutcomes>
class StaticProbabilityTable {
 private:
  std::array<int, NumberOfOutcomes> thresholds_;
  int total_weight_;

 public:
  template <std::convertible_to<int>... Args>
    requires(sizeof...(Args) == NumberOfOutcomes)
  constexpr explicit StaticProbabilityTable(Args... input_weights)
      : total_weight_(0), thresholds_{} {
    // pack arguments into temporary array for processing
    std::array<int, NumberOfOutcomes> weights = {
        static_cast<int>(input_weights)...};
    // sanitize the input to remove negative values (in-place)
    std::transform(weights.begin(), weights.end(), weights.begin(),
                   [](int w) { return std::max(0, w); });
    // accumulate
    std::partial_sum(weights.begin(), weights.end(), thresholds_.begin());
    // store total
    if constexpr (NumberOfOutcomes > 0) {
      total_weight_ = thresholds_.back();
    }
  }
  [[nodiscard]] constexpr int GetTotalWeight() const { return total_weight_; }
  [[nodiscard]] constexpr int At(int value) const {
    // hybrid search strategy
    // TODO: hardcoded NumberOfOutcomes check... probably hardware dependent
    if constexpr (NumberOfOutcomes <= 16) {
      // linear search for small tables
      for (size_t i = 0; i < NumberOfOutcomes; ++i) {
        if (value <= thresholds_[i]) {
          return static_cast<int>(i);
        }
      }
      return static_cast<int>(NumberOfOutcomes - 1);
    } else {
      // binary search for larger tables
      const auto iter =
          std::lower_bound(thresholds_.begin(), thresholds_.end(), value);
      if (iter == thresholds_.end()) {
        return static_cast<int>(NumberOfOutcomes - 1);
      } else {
        return static_cast<int>(std::distance(thresholds_.begin(), iter));
      }
    }
  }
};

}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_STATICPROBABILITYTABLE_H
