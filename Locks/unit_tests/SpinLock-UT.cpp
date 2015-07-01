#include <UnitTest++/UnitTest++.h>
#include <Locks/SpinLock.hpp>

#include <cstddef>
#include <mutex>
#include <thread>

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

    TEST(verifySpinLockProtectsSharedVariable)
    {
        locks::SpinLock lock;
        std::size_t count = 0;

        auto func = [&lock, &count](){

            for(std::size_t i = 0; i < 100; ++i)
            {
                std::unique_lock<locks::SpinLock> guard(lock);
                count++;
            }
        };

        std::thread t1(func);
        std::thread t2(func);

        t1.join();
        t2.join();

        CHECK_EQUAL(200U, count);
    }
}
