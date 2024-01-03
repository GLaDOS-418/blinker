#ifndef INCLUDE_INCLUDE_EXCLUSIVE_CRITICAL_MUTEX_HPP_
#define INCLUDE_INCLUDE_EXCLUSIVE_CRITICAL_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

// this implementation prioritises exclusive-access over shared-access.
// for example, in a R-W situtation, if the writes are critical & stale data is
// not acceptable, this should be preferred. As long as there's a write waiting
// to get 'exclusiveAccess', no read can gain access to the resource.
// NOTE: Check out 'SharedMutex' & 'FairShairedMutex' for better understanding

namespace blnkr {
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
