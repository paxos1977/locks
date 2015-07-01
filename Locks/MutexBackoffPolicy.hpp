#pragma once 
#include <mutex>
#include <cstdint>

namespace locks {

    // If we reach our spin count, back off
    // by locking on a mutex and waiting for 
    // a condition variable to wake us up.
    class MutexBackoffPolicy
    {
    public:
        explicit MutexBackoffPolicy(const std::uint8_t spinCount = 100)
            : spinCount_(spinCount)
        {
        }

        void failed_acquire(const std::uint8_t failureCount)
        {
            // if we've failed for more than 
            if(failureCount >= spinCount_)
            {
                std::unique_lock<std::mutex> guard(mutex_);
                condition_.wait(guard);
            }
        }

        void notify_one()
        {
            // signal the condition variable
            condition_.notify_one();
        }

    private:
        std::mutex mutex_;
        std::condition_variable condition_;

        const std::uint8_t spinCount_;
    };
}
