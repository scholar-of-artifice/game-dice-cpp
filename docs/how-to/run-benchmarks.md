# How to Run Benchmarks

In this article, you will learn how to run the project benchmarks.

Benchmarking this project is done using the Google Benchmark library.
Google Benchmark here: https://github.com/google/benchmark

## 📋 Prerequisites
- **Docker:** Ensure Docker is installed and the daemon is running.
    - Get Docker at: https://www.docker.com
- **Hardware:** At least 4GB of RAM is recommended when building the Memory Santizer (MSan) targets, as LLVM instrumentation is resource intensive.

## ⏱️ Benchmarks
Benchmarks allow maintainers and users to ensure the library meets practical use cases.
The current benchmark suite allows us to understand the effect of calling each function and creating the relevant data structures.
These benchmarks are then made into a report and exported as `benchmarks.json` and copied from the Docker container to the host.

**Note**: Benchmarks and reports will be improved in the future. I hope to (one day) have a visual report explaining the benchmarks.

#### Build the Image
```
DOCKER_CONTENT_TRUST=1 docker build --tag game-dice-cpp-benchmarks --progress=plain --target benchmark-suite . 
```

#### Run the Benchmarks
```
docker run --rm \
    -v "$(pwd):/results" \
    game-dice-cpp-benchmarks \
    --benchmark_out=/results/benchmarks.json \
    --benchmark_out_format=json
```
