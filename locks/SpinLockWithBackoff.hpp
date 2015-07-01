#pragma once 
#include <atomic>
#include <cstdint>

namespace locks {

    template<class BackoffPolicy>
    class SpinLockWithBackoff : public BackoffPolicy
    {
    public:
        template<typename... Args>
        SpinLockWithBackoff(Args&&... args)
            : BackoffPolicy(std::forward<Args>(args)...)
            , lock_(false)
        {
        }

        void lock();
        void unlock();

    private:
        std::atomic_bool lock_;
    };


    template<class BackoffPolicy>
    void SpinLockWithBackoff<BackoffPolicy>::lock()
    {
        std::uint_fast8_t count = 0;

        while(lock_.exchange(true))
        {
            this->failed_acquire(count++);
        }
    }

    template<class BackoffPolicy>
    void SpinLockWithBackoff<BackoffPolicy>::unlock()
    {
        lock_ = false;
        this->notify_one();
    }
}
