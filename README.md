# blinker

## Introduction
Semaphore means signal in french (or greek maybe, idk). hence an adjacent name, `blinker`.
This project implements simple semaphore based syncrhonisation constructs from scratch in C++20.

***don't use in production directly(mostly).***

## Common syncrhonisation Patterns

### [Sempahore](./include/semaphore.hpp)
- `signal()` and `wait()` implemented using **atomics** instead of delegating it to OS semaphores.
- aka `counting semaphore`.
- a `n-way-multiplexer` is `Sempahore{n}`.

### [Mutex](./include/mutex.hpp)
- `lock()` and `unlock()` are a wrapper over binary semaphore.
- this is not the same as `std::mutex` as there is no sense of ownerships in semaaphores.
- but, the interface is the same so, can be used with RAII constructs like `std::lock_guard`.
- aka `binary semaphore`.

### [Latch](./include/latch.hpp)
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- aka `single-use barrier`.

### [Barrier](./include/barrier.hpp)
- `arrive_and_wait()` waits for `N` threads to reach till a point then signal all at once.
- TODO: implement a completion function to run after the completion of each phase.
- aka `reusable barrier`.

### [LightSwitch](./include/lightswitch.hpp)
- `lock(Semaphore&)` and `unlock(Semaphore&)` takes the same semaphore as argument.
- first thread acquires the exclusive access to the resource and the last thread releases it.
- best understood by the common shared resource access problem like reader-writer problem.
- in reader-writer, a reader acquires exclusive access to the resource via a lightswitch to allow
multiple readers while the writer can simply wait on the `Semaphore` passed to that switch.

### [SharedMutex](./include/shared_mutex.hpp) (exclusive-access is starvation prone)
- aka `read-critical reader-writer lock`.
- threads either acquire shared access to the resource via `lock_shared()` or an exclusive access via `lock()`.
- follows the traits of both `Lockable` and `SharedLockable` so, can be used with both `std::shared_lock` & `std::lock`.
- As long as there's a shared-access thread with the access to the resource, no thread can gain exclusive-access.
- This might lead to 'Starvation'.
- For example, this can be used as a RW-lock where stale reads are acceptable.

### [No-Starve SharedMutex](./include/fair_shared_mutex.hpp) (fair contention between exclusive-access & shared-access threads)
- same interface as `SharedMutex` above.
- aka `no-starve reader-writer lock`.
- implemented such that there's fair contention between readers and writers.
- once a writer starts waiting, while all existing readers can finish their tasks, no other reader gets exclusive-access.
- this enables for _at least one_ writer to get exclusive-access once all existing readers finish their tasks.
- this prevents **writer starvation** as seen with `SharedMutex` above.

### [Exclusive-Prioritised SharedMutex](./include/exclusive_critical_mutex.hpp) (exclusive-access prioritised over shared-access)
- same interface as `SharedMutex` above.
- aka `write-critical reader-writer lock`.
- once a writer gets exclusive-access to the resource, readers wait until ALL the writers are finished.
- similar to `SharedMutex` but the priority is given to the `writer` instead of the `reader`.
- can be used as a `RW-Lock` where writes are more critical or reading stale data is not acceptable.
- CAUTION: This might starve the **Readers**.


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

