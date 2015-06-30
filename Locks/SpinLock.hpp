#pragma once 
#include <atomic>

namespace locks {

    class SpinLock
    {
    public:
        SpinLock();

        void lock();
        void unlock();

    private:
        std::atomic_bool lock_;
    };


    inline 
    SpinLock::SpinLock()
        : lock_(false)
    { 
    }
    
    inline
    void SpinLock::lock()
    {
        while(lock_.exchange(true));
    }

    inline 
    void SpinLock::unlock()
    {
        lock_ = false;
    }
}
