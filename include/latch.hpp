#ifndef INCLUDE_INCLUDE_LATCH_HPP_
#define INCLUDE_INCLUDE_LATCH_HPP_

#include "mutex.hpp"
#include "semaphore.hpp"
#include <mutex>

namespace blnkr {
class Latch {
  Mutex mtx{};
  Semaphore latch{0};
  unsigned int wait_for{0};
  unsigned int arrived{0};

public:
  explicit Latch(const unsigned int count) : wait_for{count} {}

  inline void arrive_and_wait() noexcept {
    {
      std::lock_guard<Mutex> _(mtx);
      ++arrived;
      if (arrived == wait_for)
        latch.signal(wait_for);
    }

    latch.wait();
    latch.signal();
  }
};
} // namespace blnkr
#endif // INCLUDE_INCLUDE_LATCH_HPP_
