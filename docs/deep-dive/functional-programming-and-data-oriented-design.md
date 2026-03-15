# Functional Programming & Data-Oriented Design
`game-dice-cpp` is built on functional programming principles to ensure that the game's probability logic is predictable and easy to reason about.

## Immutability and Pure Construction

### Result-Oriented Construction
Instead of using constructors that can fail silently or throw exceptions, the library uses a factor pattern (`Make`) that returns a `std::optional`. This forces the developer to handle the invalid states explicitly at the call site.

### Immutable Data Structures
Once a Probability Table is successfully created, its internal state is immutable. This eliminates a whole class of bugs related to hidden state changes mid-frame.

## Declarative Data Pipelines

### Modern Algorithms
The library uses `std::ranges` and `std::accumualte` with custom lambdas to process weights. This declarative approach describes what the could should do rather than how to loop over it, reducing the surface area for logic errors.

### Composablity
Internal logic uses pipelines to transform raw input weights into cumulative threshold in-place or via views, maintaining high performance without sacrificing readability.

## Policy-Based Design

### Behaviour Injection
The `DistributionFactory` utilizes policy based deisgn for rounding. By injecting a `RoundingPolicy` as a template parameters, the library remains flexible and allows develoeprs to swap between standard floating-point rounding or some custom fixed point logic.
This is important for deterministic cross-platform networking.

## Strict Decoupling of Entropy

### Stateless Tables
Probability tables contain only the shape of the distribution. There is no knowledge of the random number generation engine.

### Entropy Injection
By passing the `Engine` as a parameter to the `Roll` function, we treat the generator as a side-effect that is injection into a pure logic process. This makes testing very easy.
