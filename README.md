# False Sharing Experiment

This project contains a simple C++ program to experiment with false sharing effects in multi-threaded programs. 
The program compares sequential execution to threaded execution of two functions operating on shared data.

## Overview

- **fx()**: Performs a modifying operation on a shared variable (`sharedData.x`).
- **fy()**: Performs a non-modifying operation on another shared variable (`sharedData.y`).

The goal is to observe the performance differences—particularly if running in threaded mode leads to cache coherence issues (false sharing).

## Features

- **Switch between Sequential and Threaded Execution**  
  Change the `USE_THREADS` macro in `main.cpp` to `1` to run in threaded mode or to `0` for sequential execution.

## Building

This project requires a C++11-compliant compiler. To compile, simply run:

```bash
make
