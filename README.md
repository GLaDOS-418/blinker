# blinker

## Introduction
Semaphore means signal in french (or greek maybe, idk). hence an adjacent name `blinker`.
This project implements simple semaphore based syncrhonisation constructs from scratch in C++20.

## Features
- Sempahore: `signal()` and `wait()` implemented using atomics.
- Mutex: `lock()` and `unlock()` are a wrapper over binary semaphore.
- Latch: `wait()` waits for `N` threads to reach till a point then signals all at once. **(use once)**

## Build and Run

```bash
$ make build  # to build the project
$ make test   # to run all tests
$ make run    # to run the project
```

NOTE: check `Makefile` for more information.

