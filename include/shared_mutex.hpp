#ifndef INCLUDE_INCLUDE_SHARED_MUTEX_HPP_
#define INCLUDE_INCLUDE_SHARED_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {

class SharedMutex {
  Semaphore exclusiveAccess{1};
  LightSwitch readerAccess{};

public:
  inline void lock_shared() noexcept { readerAccess.lock(exclusiveAccess); }

  inline void unlock_shared() noexcept { readerAccess.unlock(exclusiveAccess); }

  inline void lock() noexcept { exclusiveAccess.wait(); }

  inline void unlock() noexcept { exclusiveAccess.signal(); }
};
} // namespace blnkr

#endif // INCLUDE_INCLUDE_SHARED_MUTEX_HPP_
