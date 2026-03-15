# How to Run Fuzz Tests

## Running `fuzz tests`
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

### Clean Corpora
Over time, as the fuzzer runs repeatedly, the corpora folders will accumulate redundant examples.
You need to clean these out to keep the fuzzer fast.

LibFuzzer has a built-in command `-merge=1` that analyses the existing files and extracts only the unique inputs into an optimized folder.

TODO directions for this