# game-dice-cpp

![Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg?labelColor=white&logoColor=00599C&style=plastic&logo=c%2B%2B)
![License](https://img.shields.io/badge/license-MIT-green.svg?labelColor=white&style=plastic)

**A header-only C++23 library for deterministic, type-safe, weighted probability distributions.**

Designed for game developers who need a robust, zero-dependency solutions for random number generation (RNG) mechanics, and system engineers who
value compile-time safety and memory control.

## Why use this library?

While simple `rand() % n` implementations are sufficient for prototyping, they introduce subtle bugs (like modulo bias)
and make unit testing impossible. The STL comes with many better options in `<random>`, however, these types and
functions often have subtle but important stipulations which may be relevent in your use case.

`game-dice-cpp` is built on functional programming principles to ensure that the game's probability logic is predictable and easy to reason about.
Learn more about this in the internal documentation: [Functional Programming & Data-Oriented Design](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/deep-dive/functional-programming-and-data-oriented-design.md)

## ⚡️At a Glance

Define a complex distribution at compile-time and roll with any STL compatible engine.

### Dice Rolling
```cpp
#include "game-dice-cpp/Dice.h"
#include "game-dice-cpp/Actions.h"

// 1. Create a d20 Dice
constexpr auto d20 = game_dice_cpp::Dice(20);

// 2. Inject your entropy source
std::mt19937_64 engine(42);

// 3. Roll for an outcome
auto outcome = game_dice_cpp::Roll(d20, engine);
```

### Loot Tables
```cpp
#include "game-dice-cpp/StaticProbabilityTable.h"
#include "game-dice-cpp/Actions.h"

// 1. Define a loot table (Common, Uncommon, Rare, Super Rare)
constexpr auto LootTable = game_dice_cpp::StaticProbabilityTable<3>::Make({80, 15, 4, 1}).value();

// 2. Inject your entropy source
std::mt19937_64 engine(42);

// 3. Roll for an outcome
auto outcome = LootTable.GetOutcomeIndex(game_dice_cpp::Roll(LootTable, engine));
```

## 🧑‍💻Technologies
<!--technology badges here-->
![C++](https://img.shields.io/badge/C%2B%2B-blue.svg?&logo=c%2B%2B&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?logo=docker&logoColor=fff)
![LLVM](https://img.shields.io/badge/LLVM-black?logo=llvm&logoColor=white)
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?logo=ubuntu&logoColor=white)

## 🚀 Features

### Network Ready Determinism
Decoupling the definition of an event from the source of entry ensures identical outcomes for replay systems and rollback networking.

### Zero-Allocation (Static Tables)
`StaticProbabilityTable` uses `std::array` and `constexpr` constructors to catch configuration errors at compile time with zero heap overhead.

### Modern C++23
Leaverage `std::ranges`, `std::span`, `std::expected` and more for a type-safe, expressive and readable API.

### Header Only & Zero Dependency
Optimized for easy integration into Godot GDExtension, Unreal Engine or custom C++ game engines.

🛠️Engineering & Quality Assurance

This project is a showcase of modern C++ engineering practices designed to be production ready.

### Automated Testing

#### 🔎 Static Analysis
`Clang-tidy` provides essential static analysis on all code with a zero-warning policy. This allows the project to maintain modern C++ standards, avoid common logic and safety issues and be more secure.

#### 🧪 Unit Testing
Comprehensive suite via [GoogleTest](https://github.com/google/googletest). Covers edge cases like integer overflow and distribution symmetry.

### 🐻 Fuzz Testing
Integrated [LibFuzzer](https://llvm.org/docs/LibFuzzer.html) to ensure the lbirary is resilient against malicious or unexpected inputs.

### 🦠 Sanitizers
Continuous validation using ASan(Address), UBSan(Undefined Behavior), TSan(Thread), and MSan(Memory) to ensure memory safety.

### 📉 Memory Profiling & Analysis (Valgrind)
The project includes a dedicated Dockerized Valgrind environment to ensuer absolute stability in production environments:

#### Memcheck
Guarantees zero memory leaks and detects illegal memory accesses.

#### Massif
Used for detailed heap profiling to monitor memory footprints during large-scale simulations.

#### Helgrind
Validates thread safety and detecs porential data races in multi-threaded game loops.

#### Callgrind
Provides instruction-level profiling to identify hotspots and optimize critical code paths.

### 📊 Performance Benchmarking

Micro-benchmarks are provided via [Google Benchmark](https://github.com/google/benchmark) to track the overhead of different RNG engiens and distribution lookups.
You can use this to decide what is appropriate for the platforms you are targeting.

### 🐳 Dockerized Toolchain
The engine development and test environments and toolchain are containerized for "it-just-works" reproducibility.


## 📚 Documentation
[Functional Programming & Data-Oriented Design](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/deep-dive/functional-programming-and-data-oriented-design.md)
[How to run Benchmarks](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/how-to/run-benchmarks.md)
[How to run Fuzz Tests](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/how-to/run-fuzz-tests.md)
[How to run Unit Tests](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/how-to/run-tests.md)
[How to run Toolchain](https://github.com/scholar-of-artifice/game-dice-cpp/blob/main/docs/how-to/run-clang-toolchain.md)