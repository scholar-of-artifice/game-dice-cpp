# game-dice-cpp
This is a small library of code for game developers looking for something to simulate `Dice` rolling and discrete random events.

## 🧑‍💻Technologies
<!--technology badges here-->
<div class="technology-list" alt="This project includes the use of the following technologies:">
    <img src="docs/assets/badges/cmake.svg" alt="CMake Logo" width="64"/>
    <img src="docs/assets/badges/cplusplus.svg" alt="C++ Programming Language Logo" width="64"/>
</div>

## 🧐 Design Philosophy

### Few Opinions, No Dependencies
As a user, all you need are the source code files.
You need only the C++ STL and no external dependencies to use the source code.
This code should integrate easily with most C++ accepting game engines (Unreal Engine, Godot, etc.).

If you wish to make modifications or run the tests yourself, you will need `CMake` and `Google Test`.

### Data-Oriented Core
The `Dice` class is a light-weight, immutable data structure.
It defines what a die is (geometry) but contains no logic.

### Functional Paradigms
The act of rolling is simplified to a **pure function**.
It requires 2 explicit inputs:
- the definition (the `Dice` you want to roll)
- the entropy (random number engine probably from the C++ STL or your game engine)

Rolling creates no side effects.
As a user or player, all you care about is the output from rolling.

### Composition over Inheritance
This library does not create deep inheritance structures with hundreds of derived variants.
Instead, we compose systems and map the outputs to probabilities.
This handles much more like a standard table top game.
However, if your needs for Dice rolling are complicated, you may find the included tools helpful.
Check the `docs/deep-dive` to learn more.

### Separation of "Prep" vs "Play"
Complex math happens during initialization.
The runtime hot-path can remain extremely fast.

## 💪 Key Advantages

### Deterministic & Testable
By injecting the random generator into the roll function, the system remains deterministic.
You can mock and test critical game mechanics with reliable results.

### Cache-Friendly Performance
`Dice` are tiny and can be contiguous in memory.
The heavy lifting of distribution math is pre-calculated which means your game loop can remain lightweight.

### Mathematical Flexibility
This system abstracts `Dice` into Discrete Distribution Generators.
It handles simple uniform rolls, custom rarity tables and non-uniform distributions using the same uniform `roll` function.

### Modern C++ Safety
This library uses modern C++ practices including `constexpr` for compile-time optimization where possible.
It also uses `[[nodiscard]]` to prevent ignored results.