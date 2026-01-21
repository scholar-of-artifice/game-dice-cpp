# How to Run Tests

In this article, you will learn how to run clang tools.


## Toolchain clang
### Build the Image
```
docker build --tag game-dice-cpp-toolchain-clang --target toolchain-clang .
```

### Run the Tests
```
docker run --rm \
    -v "$(pwd):/app" \
    game-dice-cpp-toolchain-clang  \
    clang-tidy src/*.h \
    -- -Isrc --std=c++23
```