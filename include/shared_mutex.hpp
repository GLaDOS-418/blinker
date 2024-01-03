#ifndef INCLUDE_INCLUDE_SHARED_MUTEX_HPP_
#define INCLUDE_INCLUDE_SHARED_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {

// reader=shared-access thread, writer=exclusive-access thread
// As long as there's at least one 'reader' accessing the resource, the
// 'writer' will not be able to gain access to the resource and this
// might lead to the 'Starvation' of 'writer' thread.
// NOTE: check 'FairSharedMutex' for no-starve shared-mutex and
//       'ExclusiveCriticalMutex' for write-critical shared-mutex

class SharedMutex {
  Semaphore exclusiveAccess{1};
  LightSwitch sharedSwitch{};

public:
  inline void lock_shared() noexcept { sharedSwitch.lock(exclusiveAccess); }

  inline void unlock_shared() noexcept { sharedSwitch.unlock(exclusiveAccess); }

  inline void lock() noexcept { exclusiveAccess.wait(); }

  inline void unlock() noexcept { exclusiveAccess.signal(); }
};
} // namespace blnkr

#endif // INCLUDE_INCLUDE_SHARED_MUTEX_HPP_
