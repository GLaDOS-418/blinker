#ifndef INCLUDE_INCLUDE_FAIR_SHARED_MUTEX_HPP_
#define INCLUDE_INCLUDE_FAIR_SHARED_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {
// This is more fair than 'blnkr::SharedMutex' because once the exclusive-access
// starts waiting at 'shared', no more shared-access thread can get access of
// the 'exclusive' resource. This makes the algorithm Starvation Free. It's fair
// because both the exclusive-access & shared-access thread compete fairly when
// grabbing the 'shared' token.
//
// NOTE: if exlusive-access is more critical, you might want to use 'ExclusiveCriticalMutex'

class FairSharedMutex {

  Semaphore exclusive{1};
  Semaphore shared{1};
  LightSwitch sharedSwitch{};

public:
  inline constexpr void lock_shared() noexcept {
    shared.wait();
    shared.signal();
    sharedSwitch.lock(exclusive);
  }

  inline constexpr void unlock_shared() noexcept {
    sharedSwitch.unlock(exclusive);
  }

  inline constexpr void lock() noexcept {
    shared.wait();
    exclusive.wait();
  }

  inline constexpr void unlock() noexcept {
    shared.signal();
    exclusive.signal();
  }
};
} // namespace blnkr

#endif // INCLUDE_INCLUDE_FAIR_SHARED_MUTEX_HPP_
