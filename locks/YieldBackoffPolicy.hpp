#pragma once
#include <cstdint>
#include <thread>

namespace locks {

    // If we reach our spin count, back off
    // by yielding the CPU.
    class YieldBackoffPolicy
    {
    public:
        explicit YieldBackoffPolicy(const std::uint8_t spinCount = 100)
            : spinCount_(spinCount)
        {
        }

        void failed_acquire(const std::uint8_t failureCount)
        {
            if(failureCount >= spinCount_)
            {
                std::this_thread::yield();
            }
        }

        void notify_one()
        {
        }

    private:
        const std::uint8_t spinCount_;
    };
}
