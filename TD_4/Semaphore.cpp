//
// Created by Yufei Hu on 26/03/2022.
//

#include "Semaphore.h"

Semaphore::Semaphore(unsigned initCount, unsigned maximumCount) {
    this->counter = initCount;
    this->maxCount = maximumCount;
}

Semaphore::~Semaphore(){}

void Semaphore::give() {
    Mutex::Lock lock(mutex);
    if(counter<maxCount){
        counter++;
    }
    lock.notify();
    lock.~Lock();
}

void Semaphore::take() {
    Mutex::Lock lock(mutex);
    if(counter>0){
        counter--;
    }
    lock.notify();
    lock.~Lock();
}

bool Semaphore::take(double timeout_ms)
{
    Mutex::Lock lock(mutex);
    if (counter == 0){
        lock.wait(timeout_ms);
        lock.notify();
        lock.~Lock();
        return true;
    }
    else{
        counter--;
        lock.notify();
        lock.~Lock();
        return false;
    }
}

//class SemaphoreProducer
SemaphoreProducer::SemaphoreProducer(Semaphore *semaphore, unsigned int maxCount)
: Thread(){
    this->counter = 0;
    this->maxCount = maxCount;
    this->semaphore = semaphore;
}

SemaphoreProducer::~SemaphoreProducer(){}

unsigned int SemaphoreProducer::getCounter() {
    return counter;
}

void SemaphoreProducer::run() {
    for(unsigned  int i =0; i<maxCount;++i){
        semaphore->give();
        counter++;
    }
}

//class SemaphoreConsumer
SemaphoreConsumer::SemaphoreConsumer(Semaphore *semaphore, unsigned int maxCount)
:Thread(){
    this->semaphore = semaphore;
    this->maxCount = maxCount;
}

SemaphoreConsumer::~SemaphoreConsumer() {}

unsigned int SemaphoreConsumer::getCounter() {
    return counter;
}

void SemaphoreConsumer::run() {
    while(semaphore->take(0)== false) {
        counter++;
        if(counter==maxCount)break;
    }
}