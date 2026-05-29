# Physics Simulator

A personal physics simulation project written in C++ using SFML.

This repository started as a simple particle collision simulator and will gradually evolve into a larger experimental physics sandbox featuring different simulation systems, collision detection methods, integration techniques, and real-time rendering experiments.

## Current Features

* 2D particle simulation
* Elastic collision response
* Collision overlap resolution
* Gravity simulation
* Frame-independent movement using delta time
* Randomized particle initialization
* Real-time rendering with SFML

## Technologies

* C++
* SFML
* MinGW/UCRT64

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

## Build

Example build command using g++:

```bash
g++ src/*.cpp -Iinclude -o physics-simulator \
-lsfml-graphics -lsfml-window -lsfml-system
```

## Run

```bash
./physics-simulator
```

## Repository Structure

```txt
project/
│
├── bin/
├── src/
└── README.md
```

## Motivation

This project is primarily a learning and experimentation environment for understanding how physics engines and simulation systems work internally.

The long-term goal is to progressively build more advanced systems from scratch instead of relying on existing physics engines.
