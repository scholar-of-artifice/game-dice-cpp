# How to Run Fuzz Tests

## Running `clang-format`
### Build the Image
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-fuzzing --target fuzz-test-suite .
```

### Run `clang-format`
```
docker run --rm -it \
    -v "$(pwd)/libfuzzer_tests/corpora/fuzz_dice:/app/build/libfuzzer_tests/corpus" \
    --entrypoint ./libfuzzer_tests/fuzz_dice \
    game-dice-cpp-fuzzing \
    -max_total_time=60 ./libfuzzer_tests/corpus
```