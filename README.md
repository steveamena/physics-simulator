# Physics Simulator

A physics simulation project written in C++ using SFML.

This repository started as a simple particle collision simulator and will gradually evolve into a larger experimental physics sandbox featuring different simulation systems, collision detection methods, integration techniques, and real-time rendering experiments.

## Current Simulations

### Collision Demo

A simple particle system featuring:

- Elastic collisions
- Gravity
- Wall constraints
- Overlap correction
- Frame-independent movement using delta time
- Randomized particle initialization
- Real-time rendering

## Build

### Dependencies:

- C++11 or newer
- CMake
- Ninja
- SFML 3
- Python 3

### Build commands:

**Debug build:**

```bash
python build.py debug
```

**Release build:**

```bash
python build.py release
```

## Run

```bash
python build.py run
```

## Repository Structure

```txt
project/
│
├── build/
├── src/
├── CMakeLists.txt
├── build.py
└── README.md
```

## Motivation

This project is primarily a learning and experimentation environment for understanding how physics engines and simulation systems work internally.

The long-term goal is to progressively build more advanced systems from scratch instead of relying on existing physics engines.


## Project Goals

The purpose of this project is to explore:

* Physics engine architecture
* Collision detection algorithms
* Numerical integration methods
* Optimization techniques
* Spatial partitioning
* Real-time simulation systems
* Game physics fundamentals

Future planned features may include:

* Spatial hashing
* Quadtrees
* Different integrations
* Soft body simulation
* Fluid simulation
* Springs and joints
* Multithreading experiments
