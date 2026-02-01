# How to Run Benchmarks

In this article, you will learn how to run the project benchmarks.


## Benchmarks

#### Build the Image
```
docker build --tag game-dice-cpp-benchmarks --target benchmark-suite .
```

#### Run the Benchmarks
```
docker run --rm \
    -v "$(pwd):/results" \
    game-dice-cpp-benchmarks \
    --benchmark_out=/results/benchmarks.json \
    --benchmark_out_format=json
```
