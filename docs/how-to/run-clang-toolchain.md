# How to clang Toolchain

## Running `clang-format`
### Build the Image
```
docker build --tag game-dice-cpp-toolchain-clang-format --target toolchain-clang-format .
```

### Run `clang-format`
```
docker run --rm \
    -v "$(pwd):/work" \
    -w /work \
    -u "$(id -u):$(id -g)" \
    game-dice-cpp-toolchain-clang-format  \
    sh -c "find src -name '*.cpp' -o -name '*.h' | xargs clang-format -i -style=file"
```

## Running `clang-tidy`
### Build the Image
```
docker build --tag game-dice-cpp-toolchain-clang-tidy --target toolchain-clang-tidy .
```

### Run `clang-tidy`
```
docker run --rm \
    -v "$(pwd):/app" \
    game-dice-cpp-toolchain-clang-tidy  \
    clang-tidy src/*.h \
    -- -Isrc --std=c++23
```