#ifndef INCLUDE_INCLUDE_LATCH_HPP_
#define INCLUDE_INCLUDE_LATCH_HPP_

#include "mutex.hpp"
#include "semaphore.hpp"
#include <mutex>

namespace blnkr {
class Latch {
  Mutex mtx;
  Semaphore latch;
  unsigned int wait_for;
  unsigned int waiting;

public:
  explicit Latch(const unsigned int count)
      : latch{Semaphore{count}}, wait_for{count}, waiting{0} {}

  inline void wait() noexcept {
    {
      std::lock_guard<Mutex> _(mtx);
      ++waiting;
      if (waiting == wait_for)
        latch.signal(wait_for);
    }

    latch.wait();
    latch.signal();
  }
};
} // namespace blnkr
#endif // INCLUDE_INCLUDE_LATCH_HPP_
