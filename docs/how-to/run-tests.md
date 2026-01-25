# How to Run Tests

In this article, you will learn how to run individual tests.


## Unit Tests

### unit tests + asan + ubsan
#### Build the Image
```
docker build --tag game-dice-cpp-unit-tests-asan-ubsan --target unit-test-suite-asan-ubsan .
```

#### Run the Tests
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-asan-ubsan
```

### unit tests + memsan + ubsan
#### Build the Image
```
docker build --tag game-dice-cpp-unit-tests-memsan-ubsan --target unit-test-suite-memsan-ubsan .
```

#### Run the Tests
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-memsan-ubsan
```


### unit tests + tsan + ubsan
#### Build the Image
```
docker build --tag game-dice-cpp-unit-tests-tsan-ubsan --target unit-test-suite-tsan-ubsan .
```

#### Run the Tests
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests-tsan-ubsan
```

### unit tests + valgrind
#### Build the Image
```
docker build --tag game-dice-cpp-unit-tests-valgrind --target unit-test-suite-valgrind .
```

#### Run the Tests

##### Run Memcheck
```
docker run --rm \
    game-dice-cpp-unit-tests-valgrind
```

##### Run Massif
```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=massif \
    --massif-out-file=/app/massif.out \
    ./Google_tests/unit_test_suite
```

##### Run Helgrind
```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=helgrind \
    --error-exitcode=1 \
    ./Google_tests/unit_test_suite
```


##### Run Callgrind
```
docker run --rm \
    --entrypoint valgrind \
    game-dice-cpp-unit-tests-valgrind \
    --tool=callgrind \
    --dump-instr=yes \
    ./Google_tests/unit_test_suite
```

