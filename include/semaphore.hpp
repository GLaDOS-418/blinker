#ifndef INCLUDE_INCLUDE_SEMAPHORE_HPP_
#define INCLUDE_INCLUDE_SEMAPHORE_HPP_

#include <atomic>

namespace blnkr {

class Semaphore {
  std::atomic<unsigned int> tokens{0};

public:
  explicit Semaphore(const unsigned int init) {
    tokens.store(init, std::memory_order_release);
  }

  inline void wait() noexcept {
    auto old = tokens.load(std::memory_order_relaxed);
    while (old == 0 || !tokens.compare_exchange_weak(old, old - 1,
                                                     std::memory_order_acq_rel))
      old = tokens.load(std::memory_order_relaxed);
  }

  inline void signal() noexcept {
    tokens.fetch_add(1, std::memory_order_acq_rel);
  }

  inline void signal(const unsigned int count) noexcept {
    tokens.fetch_add(count, std::memory_order_acq_rel);
  }
};

} // namespace blnkr
#endif // INCLUDE_INCLUDE_SEMAPHORE_HPP_
