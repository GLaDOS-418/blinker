#ifndef INCLUDE_INCLUDE_FAIR_SHARED_MUTEX_HPP_
#define INCLUDE_INCLUDE_FAIR_SHARED_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {

// reader=shared-access thread, writer=exclusive-access thread
// This is more fair than 'SharedMutex' because once the 'writer'
// starts waiting to gain exlusive-access, no more 'reader' can gain access of
// the resource. This makes the algorithm 'Starvation' Free as it guarantees
// both the 'writer' & the 'reader' threads to compete for the resource.

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
