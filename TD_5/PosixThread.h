//
// Created by Yufei Hu on 03/03/2022.
//

#ifndef TD_4_POSIXTHREAD_H
#define TD_4_POSIXTHREAD_H

#include <pthread.h>
#include <exception>

#include "Mutex.h"
using namespace std;


class PosixThread
{
public:

    PosixThread();
    PosixThread(pthread_t posixId);
    ~PosixThread();

    void start(void*(*threadFunc)(void*), void* threadArg);
    void join();
    bool join(double timeout_ms);
    bool setScheduling(int schedPolicy, int priority);
    bool getScheduling(int* pSchedPolicy, int* pPriority);
    class Exception;

private:
    pthread_t posixId;
    pthread_attr_t posixAttr;

protected:
    bool isActive = false;
};

class PosixThread::Exception : public exception
{
public:
    const char* launchingException() const noexcept;
};

class Thread : public PosixThread{
public:
    Thread();
    ~Thread();

    bool start();
    void sleep_ms(double delay_ms);
    double startTime_ms();
    double stopTime_ms();
    double execTime_ms();

protected:
    virtual void run() = 0;

private:
    static void * call_run(void* thread_v);
    bool start_flag = false;
    timespec start_time,stop_time;
};

// class IncrThread
struct Data {
    unsigned int nLoops;
    double counter;
};
class IncrThread :public Thread{
public:
    IncrThread(Data* data);
    ~IncrThread();
    Data* data;
    void run();
};

// class IncrThreadWithMutex
class IncrThreadWithMutex: public IncrThread{
public:
    IncrThreadWithMutex(Data* data,Mutex* m);
    ~IncrThreadWithMutex();
    Mutex* mutex;
    void run();
};

#endif //TD_4_POSIXTHREAD_H
