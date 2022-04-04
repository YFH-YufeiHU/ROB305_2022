//
// Created by Yufei Hu on 10/03/2022.
//

#ifndef TD_4_MUTEX_H
#define TD_4_MUTEX_H

#include <pthread.h>
#include <exception>

#include "timespec.h"

class Mutex {
public:
    Mutex(bool isInversionSafe);
    ~Mutex();
    class Monitor;
    class Lock;
    class TryLock;


private:
    void lock();
    bool lock(double timeout_ms);
    bool trylock();
    void unlock();

    pthread_mutex_t posixId;
    pthread_cond_t posixCondId;

};
//class Monitor
class Mutex::Monitor {
public:
    class TimeoutException;
    void wait();
    bool wait(double timeout_ms);
    void notify();
    void notifyAll();

    Mutex& mutex;
protected:
    Monitor(Mutex& m);
};
//class TimeoutException
class Mutex::Monitor::TimeoutException
{
public:
    const char* ReportException() const noexcept;
};
//class Lock
class Mutex::Lock : public Mutex::Monitor{
public:
    Lock(Mutex& m);
    Lock(Mutex& m,double timeout_ms);
    ~Lock();
};
//class TryLock
class Mutex::TryLock : public Mutex::Monitor{
public:
    TryLock(Mutex& m);
    ~TryLock();
};

#endif //TD_4_MUTEX_H
