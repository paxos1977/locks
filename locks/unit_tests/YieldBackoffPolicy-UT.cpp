#include "./platform/UnitTestSupport.hpp"

#include <locks/SpinLockWithBackoff.hpp>
#include <locks/YieldBackoffPolicy.hpp>

#include <cstddef>
#include <mutex>
#include <thread>

namespace {

    TEST(verifySpinLockWithBackoffInstantiation)
    {
        locks::SpinLockWithBackoff<locks::YieldBackoffPolicy> lock;
    }

    TEST(verifySpinLockWithBackoffWorksWithLockGuard)
    {
        locks::SpinLockWithBackoff<locks::YieldBackoffPolicy> lock;
        std::lock_guard<locks::SpinLockWithBackoff<locks::YieldBackoffPolicy>> guard(lock);
    }

    TEST(verifySpinLockWithBackoffWorksWithUniqueLock)
    {
        locks::SpinLockWithBackoff<locks::YieldBackoffPolicy> lock;
        std::unique_lock<locks::SpinLockWithBackoff<locks::YieldBackoffPolicy>> guard(lock);
    }

    TEST(verifySpinLockWithBackoffProtectsASharedVariable)
    {
        locks::SpinLockWithBackoff<locks::YieldBackoffPolicy> lock;
        std::size_t count = 0;

        auto func = [&lock, &count](){

            for(std::size_t i = 0; i < 100; ++i)
            {
                std::unique_lock<locks::SpinLockWithBackoff<locks::YieldBackoffPolicy>> guard(lock);
                count++;
            }
        };

        std::thread t1(func);
        std::thread t2(func);

        t1.join();
        t2.join();

        CHECK_EQUAL(200U, count);

    }

    TEST(verifySpinLockWithBackoffDoesBackoff)
    {
        locks::SpinLockWithBackoff<locks::YieldBackoffPolicy> lock(1);
        std::size_t count = 0;

        std::thread t1([&lock, &count]()
        {
            std::unique_lock<locks::SpinLockWithBackoff<locks::YieldBackoffPolicy>> guard(lock);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            count += 1;
        });

        std::thread t2([&lock, &count]()
        {
            std::unique_lock<locks::SpinLockWithBackoff<locks::YieldBackoffPolicy>> guard(lock);
            ++count;
        });

        t1.join();
        t2.join();

        CHECK_EQUAL(2U, count);
    }
}
