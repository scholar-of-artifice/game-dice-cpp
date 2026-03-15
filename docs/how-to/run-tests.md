# How to Run Tests

This article explains how to build and run various test suites for `game-dice-cpp`.
To ensure maximum reproducibility and to avoid external variables, all tests are run in Docker containers.
This allows us to run complex tools such as dynamic analysis tools and profilers without requiring you to manually configure the LLVM toolchain on the host.

## 📋 Prerequisites
- **Docker:** Ensure Docker is installed and the daemon is running.
- **Hardware:** At least 4GB of RAM is recommended when building the Memory Santizer (MSan) targets, as LLVM instrumentation is resource intensive.

## 🧪 Unit Testing With `GoogleTest`
The unit test suite validates the mathematical correctness of our distrubtions and ensures edge cases (like integer overflows) are handled safely.
We provide multiple build targets instrumented with different **Dynamic Analyzers** to catch runtime bugs that that standard tests and static analysis techniques might miss.

### Address Sanitizer (`ASan`) + Undefined Behaviour Sanitizer (`UBSan`)

Use this for general development.
This catches memory leaks, buffer overflows and illegal math operations.

#### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-unit-tests-asan-ubsan --progress=plain --target unit-test-suite-asan-ubsan .
```

#### Run
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-asan-ubsan
```

### Memory Sanitizer (`MSan`) + Undefined Behaviour Sanitizer (`UBSan`)

Use this for detecting the use of uninitialized memory.
This is critical for catching non-deterministic bugs in game logic.

**Note:** This target build a custom instrumented version of `libc++`, so th initial build may take longer.

#### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-unit-tests-memsan-ubsan --progress=plain --target unit-test-suite-memsan-ubsan .
```

#### Run
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-memsan-ubsan
```

## Thread Sanitizer (`TSan`) + Undefined Behaviour Sanitizer (`UBSan`)

Use this for validating multithreaded safety and detecting data races.
Highly recommended if you are integrating this library into an asynchronous game engine loop.

#### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-unit-tests-tsan-ubsan --progress=plain --target unit-test-suite-tsan-ubsan .
```

#### Run
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-tsan-ubsan
```

### 🔍 Deep Analysis with `Valgrind`

While Santizers are fast and run during testing, `Valgrind` provides a different look at how code interacts with the CPU and memory.
Use these for final production validation.

#### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-unit-tests-valgrind --progress=plain --target unit-test-suite-valgrind .
```

#### Run for Memory Leaks (`Memcheck`)

The default command runs `memcheck` to guarantee every byte allocated is correctly freed.

```
docker run --rm \
    game-dice-cpp-unit-tests-valgrind
```

#### Run for Heap Profiling (`Massif`)

Detailed analysis of heap memory usage over time. Essential for ensuring the library does not cause "memory spikes" during gameplay.

```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=massif \
    --massif-out-file=/app/massif.out \
    ./Google_tests/unit_test_suite
```

#### Run for Performance Hostspots (`Helgrind`)

Specialized tool for detecting synchronization errors in C++ programs using the POSIX pthreads API.
This is not valid for all hardware.

What it detects:
- **Data Races:** Accessing memory from multiple threads without adequate locking.
- **Deadlocks:** Potential circular wait conditions in lock ordering.
- **API Misuse:** Incorrect use of thread synchronization primitives.

```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=helgrind \
    --error-exitcode=1 \
    ./Google_tests/unit_test_suite
```


##### Run for Performance Hostspots (`Callgrind`)

Generates a profile of function calls and instruction execution. Use this to find bottlenecks in distribution lookups.

```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=callgrind \
    --dump-instr=yes \
    ./Google_tests/unit_test_suite
```

## Summary

I hope this has given you a clear understanding of how to build and run the tests in this project.
