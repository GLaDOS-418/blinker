#ifndef INCLUDE_INCLUDE_EXCLUSIVE_CRITICAL_MUTEX_HPP_
#define INCLUDE_INCLUDE_EXCLUSIVE_CRITICAL_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {

// this implementation prioritises 'writer' over 'reader'.
// once the 'writer' acquires the 'exclusiveSwitch', no reader can
// gain access to the resource as long as there's AT LEAST one 'writer'.

class ExclusiveCriticalMutex {
  Semaphore exclusiveAccess{1};
  Semaphore sharedAccess{1};

  LightSwitch exclusiveSwitch{};
  LightSwitch sharedSwitch{};

public:
  inline void lock_shared() noexcept {
    sharedAccess.wait();
    sharedAccess.signal();

    sharedSwitch.lock(exclusiveAccess);
  }

  inline void unlock_shared() noexcept {
    //
    sharedSwitch.unlock(exclusiveAccess);
  }

  inline void lock() noexcept {
    exclusiveSwitch.lock(sharedAccess);
    exclusiveAccess.wait();
  }

  inline void unlock() noexcept {
    exclusiveAccess.signal();
    exclusiveSwitch.unlock(sharedAccess);
  }
};
} // namespace blnkr

#endif // INCLUDE_INCLUDE_EXCLUSIVE_CRITICAL_MUTEX_HPP_
