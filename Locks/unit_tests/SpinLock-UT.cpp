#include <UnitTest++/UnitTest++.h>
#include <Locks/SpinLock.hpp>

#include <mutex>

namespace {

    TEST(verifySpinLockInstantiation)
    {
        locks::SpinLock lock;
    }

    TEST(verifySpinLockWorksWithLockGuard)
    {
        locks::SpinLock lock;
        std::lock_guard<locks::SpinLock> guard(lock);
    }

    TEST(verifySpinLockWorksWithUniqueLock)
    {
        locks::SpinLock lock;
        std::unique_lock<locks::SpinLock> guard(lock);
    }
}
