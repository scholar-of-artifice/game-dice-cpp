# select base image
FROM ubuntu:resolute-20260106.1 as base
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
# install depenedencies
# Unit Tests Image
FROM base as unit-test-suite
# copy project source code
COPY . .
# create build directory, generate files, compile the test app
RUN cmake -S . -B build -G "Unix Makefiles" \
    && cmake --build build --target unit_test_suite \
# set the default execution command
WORKDIR /app/build
ENTRYPOINT ["cteset", "--output-on-failure"]


