//
// Created by Yufei Hu on 10/03/2022.
//

#include "Mutex.h"

Mutex::Mutex(bool isInversionSafe) {
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
    if(isInversionSafe){
        pthread_mutexattr_setprotocol(&mutexAttr, PTHREAD_PRIO_INHERIT);
    }
    pthread_mutex_init(&posixId, &mutexAttr);
    pthread_cond_init(&posixCondId, NULL);
    pthread_mutexattr_destroy(&mutexAttr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

void Mutex::lock() {
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms) {
    timespec time_ts = timespec_from_ms(timeout_ms);
    if(pthread_mutex_timedlock(&posixId,&time_ts)==0){
        return true;
    }
    else{
        return false;
    }
}

bool Mutex::trylock() {
    if(pthread_mutex_trylock(&posixId)==0){
        return true;
    }
    else{
        return false;
    }
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}

// class Monitor
Mutex::Monitor::Monitor(Mutex& m):mutex(m){}

void Mutex::Monitor::wait() {
    pthread_cond_wait(&mutex.posixCondId,&mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms) {
    timespec time_ts = timespec_from_ms(timeout_ms);
    if(pthread_cond_timedwait(&mutex.posixCondId,&mutex.posixId,&time_ts)==0){
        return true;
    }
    else{
        return false;
    }
}

void Mutex::Monitor::notify() {
    pthread_cond_signal(&mutex.posixCondId);
}

void Mutex::Monitor::notifyAll() {
    pthread_cond_broadcast(&mutex.posixCondId);
}

// class TimeoutException
const char* Mutex::Monitor::TimeoutException::ReportException() const noexcept
{
    return "Error";
}

//class lock
Mutex::Lock::Lock(Mutex& m) : Mutex::Monitor(m){
    mutex.lock();
}

Mutex::Lock::Lock(Mutex& m, double timeout_ms) : Mutex::Monitor(m){
    if(mutex.lock(timeout_ms)==false){
        throw Mutex::Monitor::TimeoutException();
    }
}

Mutex::Lock::~Lock() {
    mutex.unlock();
}

//class TryLock
Mutex::TryLock::TryLock(Mutex &m) : Mutex::Monitor(m){
    if(mutex.trylock()== false){
        throw Mutex::Monitor::TimeoutException();
    }
}

