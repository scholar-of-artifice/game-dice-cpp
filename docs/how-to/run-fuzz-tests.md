# How to Run Fuzz Tests

Fuzz tests (fuzzing) is an automated software testing technique that injects invalid, random, malformed data into a system.
This is done to identify coding errors, security vulnerabilities, unhandled edge cases, and undefined behaviour.
The longer, these run, the more issues they tend to find.
Interesting inputs are then listed in a `corpus` which can then be used to make good unit test cases.

## 📋 Prerequisites
- **Docker:** Ensure Docker is installed and the daemon is running.
    - Get Docker at: https://www.docker.com
- **Hardware:** At least 4GB of RAM is recommended when building the Memory Santizer (MSan) targets, as LLVM instrumentation is resource intensive.

## Running `fuzz tests`

All fuzz tests for this project run in a Docker container.
Here are the directions to build and run the container.

**Note:** More containers will be made (in future updates) to accomodate the other dynamic analysis tools.

### Build the Image
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-fuzzing --target fuzz-asan-ubsan-test-suite .
```

### Run `fuzz tests`
```
docker run --rm -it \
    --env CTEST_PARALLEL_LEVEL=4 \
    --volume "$(pwd)/libfuzzer_tests/corpora:/app/build/libfuzzer_tests/corpora" \
    game-dice-cpp-fuzzing
```

## 🗑 Clean Corpora
Over time, as the fuzzer runs repeatedly, the corpora folders will accumulate redundant examples.
You need to clean these out to keep the fuzzer fast.

LibFuzzer has a built-in command `-merge=1` that analyses the existing files and extracts only the unique inputs into an optimized folder.

**Note:** Directions for this will follow soon.