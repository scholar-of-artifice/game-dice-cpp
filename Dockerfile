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

# builder stage - compile libc++ with MemorySantizer
# Memsan requires that the entire program (including the STL is instrumented)
FROM base AS msan-libcxx-builder
# Install tools needed to build LLVM
RUN apt-get update && apt-get install -y \
    ninja-build \
    python3 \
    && rm -rf /var/lib/apt/lists/*
# clone LLVM project
WORKDIR /tmp
RUN git clone --depth=1 https://github.com/llvm/llvm-project.git
# go to downloaded repo
WORKDIR /tmp/llvm-project
# 'RUN' tells docker to execute a shell command
# 'cmake' is the tool used to configure the build
# '-S runtimes' tells cmake that the source code is in /runtimes directory
# '-B build' tells cmake to create a temp directory called 'build'
# '-G Ninja' tells cmake to use the 'Ninja' tool to run the build.
# build libc++ and libc++abi with MSan enabled
RUN cmake -S runtimes -B build -G Ninja \
        \
        # tell cmake to use clang for c and c++ files
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        \
        # we do not need debug symbols
        -DCMAKE_BUILD_TYPE=Release \
        \
        # this is a list of exactly which sub-projects to build
        -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
        \
        # inject Memsan
        -DLLVM_USE_SANITIZER=Memory \
        \
        # where to save the final files
        -DCMAKE_INSTALL_PREFIX=/opt/msan-libcxx \
        \
        # dont build the internal tests for LLVM
        -DLIBCXX_INCLUDE_TESTS=OFF \
        \
        # dont build the internal benchmarks
        -DLIBCXX_INCLUDE_BENCHMARKS=OFF \
        \
        # dont build the internal tests for ABI support
        -DLIBCXXABI_INCLUDE_TESTS=OFF \
        \
        # turn off internal tests for the unwind library
        -DLIBUNWIND_INCLUDE_TESTS=OFF \
        \
        # && means to run this configuration if all the above parts succeed
        && cmake --build build --target install-cxx install-cxxabi install-unwind

# builder stage - compile libc++ with ThreadSantizer
# Tsan requires that the entire program (including the STL is instrumented)
FROM base AS tsan-libcxx-builder
# Install tools needed to build LLVM
RUN apt-get update && apt-get install -y \
    ninja-build \
    python3 \
    && rm -rf /var/lib/apt/lists/*
# clone LLVM project
WORKDIR /tmp
RUN git clone --depth=1 https://github.com/llvm/llvm-project.git
# go to downloaded repo
WORKDIR /tmp/llvm-project
# 'RUN' tells docker to execute a shell command
# 'cmake' is the tool used to configure the build
# '-S runtimes' tells cmake that the source code is in /runtimes directory
# '-B build' tells cmake to create a temp directory called 'build'
# '-G Ninja' tells cmake to use the 'Ninja' tool to run the build.
# build libc++ and libc++abi with MSan enabled
RUN cmake -S runtimes -B build -G Ninja \
        \
        # tell cmake to use clang for c and c++ files
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        \
        # we do not need debug symbols
        -DCMAKE_BUILD_TYPE=Release \
        \
        # this is a list of exactly which sub-projects to build
        -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
        \
        # inject Memsan
        -DLLVM_USE_SANITIZER=Thread \
        \
        # where to save the final files
        -DCMAKE_INSTALL_PREFIX=/opt/tsan-libcxx \
        \
        # dont build the internal tests for LLVM
        -DLIBCXX_INCLUDE_TESTS=OFF \
        \
        # dont build the internal benchmarks
        -DLIBCXX_INCLUDE_BENCHMARKS=OFF \
        \
        # dont build the internal tests for ABI support
        -DLIBCXXABI_INCLUDE_TESTS=OFF \
        \
        # turn off internal tests for the unwind library
        -DLIBUNWIND_INCLUDE_TESTS=OFF \
        \
        # && means to run this configuration if all the above parts succeed
        && cmake --build build --target install-cxx install-cxxabi install-unwind

# Unit Tests Images
# Build unit tests with Asan and UBsan
FROM base AS unit-test-suite-asan-ubsan
# copy project source code
COPY . .
# create build directory, generate files, compile the test app
RUN cmake -S . -B build -G "Unix Makefiles" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
    && cmake --build build --target unit_test_suite
# set the default execution command
WORKDIR /app/build
ENTRYPOINT ["ctest", "--test-dir", "Google_tests", "--output-on-failure", "--verbose"]

# Build unit tests with Memsan and UBsan
FROM base AS unit-test-suite-memsan-ubsan
# copy the instrumented library from the builder stage
COPY --from=msan-libcxx-builder /opt/msan-libcxx /opt/msan-libcxx
# copy project source code
COPY . .
# create build directory, generate files, compile the test app
RUN cmake -S . -B build -G "Unix Makefiles" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-fsanitize=memory,undefined -stdlib=libc++ -nostdinc++ -I/opt/msan-libcxx/include/c++/v1 -L/opt/msan-libcxx/lib -lc++abi -fno-omit-frame-pointer -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -fsanitize=memory,undefined -L/opt/msan-libcxx/lib -Wl,-rpath,/opt/msan-libcxx/lib -lc++abi" \
    && cmake --build build --target unit_test_suite
# set the default execution command
WORKDIR /app/build
ENTRYPOINT ["ctest", "--test-dir", "Google_tests", "--output-on-failure", "--verbose"]


# Build unit tests with Tsan and UBsan
FROM base AS unit-test-suite-tsan-ubsan
# copy the instrumented library from the builder stage
COPY --from=tsan-libcxx-builder /opt/tsan-libcxx /opt/tsan-libcxx
# copy project source code
COPY . .
# create build directory, generate files, compile the test app
RUN cmake -S . -B build -G "Unix Makefiles" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-fsanitize=thread,undefined -stdlib=libc++ -nostdinc++ -I/opt/tsan-libcxx/include/c++/v1 -L/opt/tsan-libcxx/lib -lc++abi -fno-omit-frame-pointer -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -fsanitize=thread,undefined -L/opt/tsan-libcxx/lib -Wl,-rpath,/opt/tsan-libcxx/lib -lc++abi" \
    && cmake --build build --target unit_test_suite
# set the default execution command
WORKDIR /app/build
ENTRYPOINT ["ctest", "--test-dir", "Google_tests", "--output-on-failure", "--verbose"]


