#ifndef INCLUDE_INCLUDE_SHARED_MUTEX_HPP_
#define INCLUDE_INCLUDE_SHARED_MUTEX_HPP_

#include "lightswitch.hpp"
#include "semaphore.hpp"

namespace blnkr {

// As long as there's an exclusive-access thread in the 'room', the
// exclusive-access thread will not be able to gain access to the resource and
// might lead to 'Starvation'. example: this can be used as a reader writer lock
// and as long as there's a reader, writer can't gain  access. which could be
// the expected behaviour in case when there're too many reads and too few
// writes and reading 'stale' data is acceptable.
//
// NOTE: 'FairSharedMutex' be used for fair contention amongs shared & exclusive
// threads OR
//       'ExclusiveCriticalMutex' can be used if exclusive-access threads are to
//       be given priority.

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
