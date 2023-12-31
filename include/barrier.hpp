#ifndef INCLUDE_INCLUDE_BARRIER_HPP_
#define INCLUDE_INCLUDE_BARRIER_HPP_

#include "mutex.hpp"
#include <atomic>
#include <doctest/doctest.h>
#include <iostream>
#include <mutex>
#include <syncstream>
#include <thread>
#include <type_traits>

namespace blnkr {

// TODO: impl a completion function callable that is
// executed exactly once after phase one ends and before phase two begins.
// template <typename Fn>
//   requires std::is_invocable_v<Fn>
class Barrier {
  Mutex mtx{};
  Semaphore phaseOneB{0};
  Semaphore phaseTwoB{0};
  unsigned int arrived{0};
  const unsigned int wait_for{0};

  void phase_one() {
    {
      std::lock_guard<Mutex> _{mtx};
      ++arrived;
      if (wait_for == arrived) {
        phaseOneB.signal(wait_for);
      }
    }

    phaseOneB.wait();
  }

  void phase_two() {
    {
      std::lock_guard<Mutex> _{mtx};
      --arrived;
      if (arrived == 0)
        phaseTwoB.signal(wait_for);
    }

    phaseTwoB.wait();
  }

public:
  explicit Barrier(const size_t _wait_for) : wait_for(_wait_for) {}

  void arrive_and_wait() noexcept {
    phase_one();
    phase_two();
  }
};
} // namespace blnkr

TEST_CASE("doctest-barrier") {
  const int n = 3;

  blnkr::Barrier barrier{n};
  const int expected = n;
  std::atomic_int actual = 0;

  auto fn = [&expected, &actual, &barrier]() {
    ++actual;
    barrier.arrive_and_wait();
    REQUIRE(actual.load(std::memory_order_acquire) == expected);
    std::osyncstream(std::cout) << actual << std::endl;
  };

  std::jthread j1{fn};
  std::jthread j2{fn};
  std::jthread j3{fn};
}

#endif // INCLUDE_INCLUDE_BARRIER_HPP_
