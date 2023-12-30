#ifndef INCLUDE_INCLUDE_MUTEX_HPP_
#define INCLUDE_INCLUDE_MUTEX_HPP_

#include "semaphore.hpp"

namespace blnkr {

class Mutex {
  Semaphore s{1};

public:
  inline void lock() noexcept { s.wait(); }

  inline void unlock() noexcept { s.signal(); }
};

} // namespace blnkr
#endif // INCLUDE_INCLUDE_MUTEX_HPP_
