//
// Created by Yufei Hu on 26/03/2022.
//

#ifndef TD_4_SEMAPHORE_H
#define TD_4_SEMAPHORE_H

#include <climits>

#include "Mutex.h"
#include "PosixThread.h"

class Semaphore {
public :
    Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT_MAX);
    ~Semaphore();
    void give();
    void take();
    bool take(double timeout_ms);

private :
    unsigned int counter;
    unsigned int maxCount;
    Mutex mutex;
};

//class SemaphoreProducer
class SemaphoreProducer : public Thread
{
public:
    SemaphoreProducer(Semaphore *semaphore, unsigned int maxCount);
    ~SemaphoreProducer();
    unsigned int getCounter();
    void run();

private:
    Semaphore *semaphore;
    unsigned int counter;
    unsigned int maxCount;
};

//class SemaphoreConsumer
class SemaphoreConsumer : public Thread
{
public:
    SemaphoreConsumer(Semaphore *semaphore, unsigned int maxCount);
    ~SemaphoreConsumer();
    unsigned int getCounter();
    void run();

private:
    Semaphore *semaphore;
    unsigned int counter;
    unsigned int maxCount;
};


#endif //TD_4_SEMAPHORE_H
