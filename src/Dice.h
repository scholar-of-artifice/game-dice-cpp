//
// Created by dev on 26/12/2025.
//

#ifndef DICE_H
#define DICE_H
#include <limits>

namespace game_dice {

/*
 * TODO: describe this class well for the sake of the user
 */
class Dice {
  /*
   * The number of sides of this dice.
   */
  int num_sides;

 public:
  /*
   * Construct a Dice object. Tell the program how many sides the dice should
   * have. game_dice::Dice(7) creates a 7 sided dice. game_dice::Dice(20)
   * creates a 20 sided dice. The number of sides will be constrained to a
   * minimum value of 2. The maximum value is a maximum of the `int` type.
   * If you know the number of sides at compile time, then a small compile time
   * optimization can be made.
   */
  constexpr explicit Dice(int sides)
      : num_sides((sides < 2) ? 2
                  : (sides >= std::numeric_limits<int>::max())
                      ? (std::numeric_limits<int>::max() - 1)
                      : sides) {}
  /*
   * Read the number of sides of this dice.
   */
  [[nodiscard]] constexpr int getNumSides() const { return num_sides; }
};

}  // namespace game_dice

#endif  // DICE_H
