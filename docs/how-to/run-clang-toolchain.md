# How to clang Toolchain

In this article, you will learn how to run the various `clang` tools used in this project.
The key idea with these tools is to automatically enforce your minimum standards.

## Autoformatting with `clang-format`

> Tabs versus spaces?
> Spaces around your parenthesis?
> How long can a line of code be?

I have given this matter all the consideration it deserves.
Autoformat your code and talk about something important.
I find that this is often a point of grand-standing for people who pretend to be engineers but, in reality, refuse to grow into higher levels of problem solving difficulty.

This project uses the Google format as specified in `/.clang-format`.
This is simply because I find this particular style works well if you have limited screen space.

### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-toolchain-clang-format --target toolchain-clang-format .
```

### Run
```
docker run --rm \
    -v "$(pwd):/work" \
    -w /work \
    -u "$(id -u):$(id -g)" \
    game-dice-cpp-toolchain-clang-format  \
    sh -c "find src Google_tests/tests Google_benchmarks/benchmarks -name '*.cpp' -o -name '*.h' | xargs clang-format -i -style=file"
```

## Initial Automated Code Review with `clang-tidy`

`clang-tidy` presents a number of checks that are useful for making higher quality code.
It acts as a linter and checks for:
- **Modernization:** Ensuring C++23 features are used where appropriate.
- **Performance:** Catching expensive copies or inefficient STL use.
- **Safety:** Identifying potentially unsafe code before the code is compiled.
- **Security:** Identifying common bad practices which lead to common security issues.


### Build
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-toolchain-clang-tidy --target toolchain-clang-tidy .
```

### Run
```
docker run --rm \
    -v "$(pwd):/app" \
    game-dice-cpp-toolchain-clang-tidy  \
    clang-tidy src/*.h \
    -- -Isrc --std=c++23 -x c++
```