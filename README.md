# blinker

## Introduction
Semaphore means signal in french (or greek maybe, idk). hence an adjacent name, `blinker`.
This project implements simple semaphore based syncrhonisation constructs from scratch in C++20.

***don't use in production directly(mostly).***

## Common syncrhonisation Patterns

### Sempahore
- `signal()` and `wait()` implemented using atomics.
- aka `counting semaphore`.

### Mutex
- `lock()` and `unlock()` are a wrapper over binary semaphore.
- aka `binary semaphore`.

### Latch
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- aka `single-use barrier`.

### Barrier
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- TODO: implement a completion function to run after the completion of each phase.
- aka `reusable barrier`.

### LightSwitch
- `lock(Semaphore&)` and `unlock(Semaphore&)` takes the same semaphore as argument.
- first thread acquires the exclusive access to the resource and the last thread releases it.
- best understood by the common shared resource access problem like reader-writer problem.
- in reader-writer, a reader acquires exclusive access to the resource via a lightswitch to allow
multiple readers while the writer can simply wait on the `Semaphore` passed to that switch.

### SharedMutex
- threads either acquire shared access to the resource via `lock_shared()` or an exclusive access via `lock()`.
- aka `reader-writer lock`.


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

