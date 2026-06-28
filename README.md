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
- ImGui-SFML

### Build commands:

**Debug build:**

```bash
python simulator.py debug
```

**Release build:**

```bash
python simulator.py release
```

**Run:**

```bash
python simulator.py run
```

**Clean:**

```bash
python simulator.py clean
```

**Rebuild:**

```bash
python simulator.py rebuild
```


## Repository Structure

```txt
project/
│
├── bin/             # Generated executables
├── build/           # CMake/Ninja build files
├── buildtools/      # Build system scripts
├── src/
├── CMakeLists.txt
├── simulator.py         # Build tool entry point
└── README.md
```

## Project Goals

This project is primarily a experimentation environment for understanding how physics engines and simulation systems work internally.

The purpose of this project is to explore:

- Physics engine architecture
- Collision detection algorithms
- Alternative integration methods
- Optimization techniques
- Spatial partitioning
- Real-time simulation systems
- Game physics fundamentals

The long-term goal is to progressively build more advanced systems from scratch instead of relying on existing physics engines.

Future planned features may include:

- Spatial hashing
- Quadtrees
- Different integrations
- Soft body simulation
- Fluid simulation
- Springs and joints
- Multithreading experiments
