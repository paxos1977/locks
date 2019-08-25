# Locks

A small header only library implementing some useful high-performance locks in C++11.

### Examples 

A simple spin lock example. 

    locks::SpinLock lock;
    std::unique_lock<locks::SpinLock> guard(lock);

A spin lock with a spin count and a backoff policy that acquires a mutex after 20 failed attempts to acquire the lock.

    locks::SpinLockWithBackoff<locks::MutexBackoffPolicy> lock(20);
    std::unique_lock<locks::SpinLockWithBackoff<locks::MutexBackoffPolicy>> guard(lock);

### Dependencies 

- c++11

Used for unit testing on all platforms:

- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

### Contributors 

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 
