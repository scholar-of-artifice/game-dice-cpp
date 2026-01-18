# How to Run Tests

In this article, you will learn how to run individual tests.


## Unit Tests
### Build the Image
```
docker build --tag game-dice-cpp-unit-tests --target unit-test-suite .
```

### Run the Tests
```
docker run --rm --name game-dice-cpp-unit-test-suite game-dice-cpp-unit-tests
```