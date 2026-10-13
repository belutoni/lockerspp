//
// Created by Antonie Gabriel Belu on 12/10/2026.
//

#ifndef LOCKERSPP_LOCKERSPP_H
#define LOCKERSPP_LOCKERSPP_H

#include <atomic>

class SpinlockMutex {
    std::atomic<bool> m_flag;
public:
    SpinlockMutex() : m_flag(false) {}

    void lock() {
        bool expected{false};
        while (!m_flag.compare_exchange_weak(expected, true)) expected = false;
    }

    void unlock() {
        m_flag.store(false);
    }

    bool try_lock() {
        bool expected{false};
        return m_flag.compare_exchange_strong(expected, true);
    }

    SpinlockMutex(SpinlockMutex const&) = delete;
    SpinlockMutex& operator=(SpinlockMutex const&) = delete;
    SpinlockMutex(SpinlockMutex&&) = delete;
    SpinlockMutex& operator=(SpinlockMutex&&) = delete;
};

class Semaphore {
    std::atomic<std::ptrdiff_t> m_count;
public:
    explicit Semaphore(std::ptrdiff_t const count) : m_count(count) {}

    void acquire() {
        std::ptrdiff_t expected{m_count.load()};
        while (true) {
            if (expected <= 0) {
                expected = m_count.load();
            } else if (m_count.compare_exchange_weak(expected, expected - 1)) {
                    return;
            }
        }
    }

    bool try_acquire() {
        std::ptrdiff_t expected{m_count.load()};
        if (expected <= 0)
            return false;

        return m_count.compare_exchange_strong(expected, expected - 1);
    }

    void release(std::ptrdiff_t const count = 1) {
        m_count.fetch_add(count);
    }

    Semaphore(Semaphore const&) = delete;
    Semaphore& operator=(Semaphore const&) = delete;
    Semaphore(Semaphore&&) = delete;
    Semaphore& operator=(Semaphore&&) = delete;
};

#endif //LOCKERSPP_LOCKERSPP_H
