//
// Created by Yufei Hu on 03/03/2022.
//

#include <iostream>
#include <pthread.h>
#include "PosixThread.h"
#include "timespec.h"


PosixThread::PosixThread(){
    this -> posixId = 0;
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&posixAttr, SCHED_OTHER);
    sched_param schedParam;
    schedParam.sched_priority = 0;
    pthread_attr_setschedparam(&posixAttr, &schedParam);
}

PosixThread::PosixThread(pthread_t posixId) {
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
    sched_param schedParam;
    int policy;
    int result = pthread_getschedparam(posixId, &policy, &schedParam);
    if(result == 0){
        this -> isActive = true;
        pthread_attr_setschedpolicy(&posixAttr, policy);
        pthread_attr_setschedparam(&posixAttr, &schedParam);
    }
    else{
        throw PosixThread::Exception();
    }
}

PosixThread::~PosixThread() {
    pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(void *(*threadFunc)(void *), void *threadArg) {
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
    isActive = true;
}

void PosixThread::join() {
    pthread_join(posixId, NULL);
}

bool PosixThread::join(double timeout_ms) {
    timespec timeout = timespec_from_ms(timeout_ms);
    int result = pthread_timedjoin_np(posixId, NULL, &timeout);
    if (result==0){
        return true;
    }
    else{
        return false;
    }
}

bool PosixThread::setScheduling(int schedPolicy, int priority) {
    sched_param schedParam;
    schedParam.sched_priority = priority;
    if(!isActive){
        pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
        pthread_attr_setschedparam(&posixAttr, &schedParam);
    }
    else{
        pthread_setschedparam(posixId, schedPolicy, &schedParam);
    }
    return isActive;
}

bool PosixThread::getScheduling(int *pSchedPolicy, int *pPriority) {
    sched_param schedParam;
    *pPriority = schedParam.sched_priority;
    if(!isActive){
        pthread_attr_getschedpolicy(&posixAttr, pSchedPolicy);
        pthread_attr_getschedparam(&posixAttr, &schedParam);
    }
    else{
        pthread_getschedparam(posixId, pSchedPolicy, &schedParam);
    }
    return isActive;
}

const char *PosixThread::Exception::launchingException() const noexcept
{
    return "\nThere is no corresponding thread!\n";
}

// class thread
Thread::Thread(){}

Thread::~Thread(){}

bool Thread::start(){
    if(!start_flag){
        start_time = timespec_now();
        PosixThread::start(call_run, (void*) this);
        start_flag = true;
    }
    return start_flag;
}

void Thread::sleep_ms(double delay_ms){
    timespec time_wait;
    time_wait = timespec_from_ms(delay_ms);
    timespec_wait( time_wait);
}

double Thread::startTime_ms(){
    return timespec_to_ms(start_time);
}

double Thread::stopTime_ms(){
    return timespec_to_ms(stop_time);
}

double Thread::execTime_ms(){
    stop_time = timespec_now();
    return timespec_to_ms(stop_time - start_time);
}

void* Thread::call_run(void* thread_v){
    Thread* thread = (Thread*) thread_v;
    thread->run();
    return (void*) thread;
}

//class IncrThread
IncrThread::IncrThread(Data* data) : Thread(), data(data){
    this->data->nLoops = data->nLoops;
    this->data->counter = data->counter;
}

IncrThread::~IncrThread() {}

void IncrThread::run() {
    for(unsigned int i=0; i < data->nLoops; i++)
    {
        data -> counter += 1.0;
    }
}

//class IncrThreadWithMutex
IncrThreadWithMutex::IncrThreadWithMutex(Data *data, Mutex *m)
: IncrThread(data),mutex(m){
    this->data->nLoops = data->nLoops;
    this->data->counter = data->counter;
    this->mutex = m;
}

IncrThreadWithMutex::~IncrThreadWithMutex() {}

void IncrThreadWithMutex::run(){
    for(unsigned int i=0; i < data->nLoops; i++){
        Mutex::Lock lock = Mutex::Lock(*mutex);
        data -> counter += 1.0;
        lock.~Lock();
    }
}