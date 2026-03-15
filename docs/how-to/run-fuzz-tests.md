# How to Run Fuzz Tests

## Running `fuzz tests`
### Build the Image
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-fuzzing --target fuzz-test-suite .
```

### Run `fuzz tests`
```
docker run --rm -it \
    --env CTEST_PARALLEL_LEVEL=4 \
    --volume "$(pwd)/libfuzzer_tests/corpora:/app/build/libfuzzer_tests/corpora" \
    game-dice-cpp-fuzzing
```