# select base image
FROM ubuntu:resolute-20260106.1 AS base
# name of the author
LABEL authors="scholar-of-artifice"
# install git, clang, cmake
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    cmake \
    git \
    llvm \
    && rm -rf /var/lib/apt/lists/*
# define working directory
WORKDIR /app

# clang-format image
FROM base AS toolchain-clang-format
RUN apt-get update && apt-get install -y \
    clang-format \
    && rm -rf /var/lib/apt/lists/*

# clang-tidy image
FROM base AS toolchain-clang-tidy
RUN apt-get update && apt-get install -y \
    clang-tidy \
    && rm -rf /var/lib/apt/lists/*

# Unit Tests Image
FROM base AS unit-test-suite-asan-ubsan
# copy project source code
COPY . .
# create build directory, generate files, compile the test app
RUN cmake -S . -B build -G "Unix Makefiles" \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
    && cmake --build build --target unit_test_suite
# set the default execution command
WORKDIR /app/build
ENTRYPOINT ["ctest", "--test-dir", "Google_tests", "--output-on-failure", "--verbose"]


