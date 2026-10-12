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

#endif //LOCKERSPP_LOCKERSPP_H
