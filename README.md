# blinker

## Introduction
Semaphore means signal in french (or greek maybe, idk). hence an adjacent name `blinker`.
This project implements simple semaphore based syncrhonisation constructs from scratch in C++20.

## Features

### Sempahore
- `signal()` and `wait()` implemented using atomics.

### Mutex
- `lock()` and `unlock()` are a wrapper over binary semaphore.

### Latch
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- aka single-use barrier.

### Barrier
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- aka reusable barrier.
- TODO: implement a completion function to run after the completion of each phase.


## Build and Run
```bash
$ make build  # to build the project
$ make test   # to run all Catch2 tests
$ make run    # to run the project
$ make all    # build and run
```

**NOTE**

1. current impl has a `doctest` provided main.
2. check `Makefile` for more information.

