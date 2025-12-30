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
#include <ranges>
#include <limits>
#include <optional>

namespace game_dice_cpp {

template <size_t NumberOfOutcomes>
class StaticProbabilityTable {
 private:
  std::array<int, NumberOfOutcomes> thresholds_;

  constexpr explicit StaticProbabilityTable(
      const std::array<int, NumberOfOutcomes>& thresholds)
      : thresholds_(thresholds) {}

 public:
  //
  template <std::convertible_to<int>... Args>
    requires(sizeof...(Args) == NumberOfOutcomes)
  [[nodiscard]] static constexpr std::optional<game_dice_cpp::StaticProbabilityTable<NumberOfOutcomes>>
  Make(const Args&... input_weights) {
    // pack arguments
    std::array<int, NumberOfOutcomes> weights = {
        static_cast<int>(input_weights)...};
    // transform in-place only non-negative weights
    std::ranges::transform(weights, weights.begin(), [](int w) { return std::max(w, 0); });
    // accumulate with check-as-you-go overflow check
    // use std::optional<int> to carry the valid state through the loop
    std::optional<int> total_weight = std::accumulate(
        weights.begin(), weights.end(), std::optional<int>(0),
        [](std::optional<int> accumulated, int weight) -> std::optional<int> {
          // if a previous step failed...
          if (!accumulated) {
            return std::nullopt;
          }
          // check for overflow before it happens
          if (weight > std::numeric_limits<int>::max() - *accumulated) {
            return std::nullopt;
          }
          return *accumulated + weight;
        });
    // validation
    if (!total_weight.has_value() || *total_weight <= 0) {
      return std::nullopt;
    }
    // calculate thresholds
    std::array<int, NumberOfOutcomes> thresholds{};
    std::partial_sum(weights.begin(), weights.end(), thresholds.begin());
    // check if the thresholds do not exist or sum to nothing
    if (thresholds.empty() || thresholds.back() <= 0) {
      return std::nullopt;
    }
    // construct and return
    return StaticProbabilityTable(thresholds);
  }
  [[nodiscard]] constexpr int GetTotalWeight() const {
    return thresholds_.back();
  }
  [[nodiscard]] constexpr int At(int value) const {
    // TODO: small table optimization
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

#endif  // GAME_DICE_CPP_SRC_STATICPROBABILITYTABLE_H
