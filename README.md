# Drone simulator
## Introduction
This is a simple "game" where you can fly a drone above a 3D terrain.
The collision system blocks you from flying through other objects (or at least should).
The project is still in progress, but for now you can safely collide with simple shapes
(somehow with terrain it doesn't work as good I wanted to).

## Algorithms/libraries used
- rendering: OpenGL
- terrain generation - Perlin Noise algorithm
- collision system - GJK algorithm with a sphere optimization

## Build requirements
You need at least cmake 3.28.

## How to build
I tested it only on Linux. To make it work, run in the main directory:

```bash
cmake -S . -B build
cd build
make
```

## How to run game
After building, go back to the main directory. Then run:

```bash
./build/game
```

## How to run tests
I've did some unit tests (currently only for the collision system)
If you want to run them, run in the main directory.
```bash
./build/tests
```
(I think it would be better to integrate them into some GitHub CI/CD, maybe in the future)