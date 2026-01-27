# How to Run Benchmarks

In this article, you will learn how to run the project benchmarks.


## Benchmarks

#### Build the Image
```
docker build --tag game-dice-cpp-benchmarks --target benchmark-suite .
```

#### Run the Benchmarks
```
docker run --rm game-dice-cpp-benchmarks
```
