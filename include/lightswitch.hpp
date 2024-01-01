#ifndef INCLUDE_INCLUDE_LIGHTSWITCH_HPP_
#define INCLUDE_INCLUDE_LIGHTSWITCH_HPP_

#include "mutex.hpp"
#include "semaphore.hpp"
#include <doctest/doctest.h>
#include <mutex>

namespace blnkr {

class LightSwitch {
  Mutex mtx{};
  unsigned int count{0};

public:
  // NOTE: make sure to pass the SAME semaphore in
  // lock() and unlock()

  void lock(Semaphore &lSwitch) {
    std::lock_guard<Mutex> _{mtx};
    ++count;
    if (1 == count)
      lSwitch.wait();
  }

  void unlock(Semaphore &lSwitch) {
    std::lock_guard<Mutex> _{mtx};
    --count;
    if (0 == count)
      lSwitch.signal();
  }
};
} // namespace blnkr

#endif // INCLUDE_INCLUDE_LIGHTSWITCH_HPP_
