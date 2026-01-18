FROM ubuntu:resolute-20260106.1 as base
LABEL authors="scholar-of-artifice"

# install git, clang, cmake
RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    git \
    llvm \
    && rm -rf /var/lib/apt/lists/*
# install depenedencies
#
# Unit Tests Image
FROM base as unit-test-suite



