# game-dice-cpp

![Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg?labelColor=white&logoColor=00599C&style=plastic&logo=c%2B%2B)
![License](https://img.shields.io/badge/license-MIT-green.svg?labelColor=white&style=plastic)

**A header-only C++23 library for deterministic, weighted probability distributions.**

Designed for game developers who need a robust, zero-dependency solutions for RNG mechanics, and system engineers who
value compile-time safety and memory control.

## 🧑‍💻Technologies

<!--technology badges here-->
![C++](https://img.shields.io/badge/C%2B%2B-blue.svg?&logo=c%2B%2B&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?logo=docker&logoColor=fff)
![LLVM](https://img.shields.io/badge/LLVM-black?logo=llvm&logoColor=white)
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?logo=ubuntu&logoColor=white)

## 🧐 Design Philosophy

**game-dice-cpp** is a modern C++23, header only library designed to make probabilty mechanics **type-safe**, *
*deterministic** and **testable**.
This library addresses those pain points by adopting Data Oriented Design and Functional Programming paradigms to
strictly decouple the *definition* of the random event from the *source* of the entropy

### Why use this library?

While simple `rand() % n` implementations are sufficient for prototyping, they introduce subtle bugs (like modulo bias)
and make unit testing impossible. The STL comes with many better options in `<random>`, however, these types and
functions often have subtle but important stipulations which may be relevent in your use case.

#### Determinism

By injecting the random number engine into every roll, you guarantee identical outcomes for replay systems, network
sync, or regression testing..

#### Compile-Time Safety

Utilizes modern C++ features to validate `StaticProbabilityTable` at build time. Can catch certain error before the game
even launches.

#### Zero Dependencies

No external libraries required. Just drop the `src/` folder into your Godot GDExtension or Unreal Engine project and
build.

## ⚡️ Quick Start

### Prerequisites
* **C++ Compiler**: Must support **C++23** (e.g., GCC 13+, Clang 16+, MSVC 19.36+).
* **CMake**: Version **3.31** or higher.

### Method 1: CMake FetchContent (Recommended)
The most robust way to integrate this library is via CMake's `FetchContent`.
This ensures your project always builds with the correct version and settings.

- Add this to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
        game_dice_cpp
        GIT_REPOSITORY [https://github.com/scholar-of-artifice/game-dice-cpp.git] (https://github.com/scholar-of-artifice/game-dice-cpp.git)
        GIT_TAG main  # or a specific commit hash for stability
)
FetchContent_MakeAvailable(game_dice_cpp)

# Link it to your target (header-only, so it adds include paths automatically)
target_link_libraries(YourGameTarget PRIVATE game_dice_cpp)
```

### Method 2: Header-Only (Manual)

Since `game-dice-cpp` is a pure interface library with no compiled binaries, you can simply copy the files. You will
probably do this if you intend to compile from source.

- Copy the `src/` folder into your project's vendor directory (example: `ThirdParty/game-dice-cpp/`).
- Add that folder to your include path.

## 📚 Learn More
All types are strictly scoped within the `game_dice_cpp` namespace.
Please refer to the documentation to learn more about using the library.
- TODO documentation here
- Want to learn more about performance and benchmarks?
- Want to see some usage examples?
- Want to learn more about the Architecture of this library?
- Want to learn more about the Design Principles of this library?
- Want to see the future RoadMap and current limitations?