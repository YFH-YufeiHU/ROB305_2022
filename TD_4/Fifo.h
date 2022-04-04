//
// Created by Yufei Hu on 02/04/2022.
//

#ifndef TD_4_FIFO_H
#define TD_4_FIFO_H

#include <queue>
#include <exception>

#include "Mutex.h"
#include "PosixThread.h"

template <typename T> class Fifo {
public:
    void push(T element);
    T pop();
    T pop(double timeout_ms);
    class EmptyException : std::exception{
    public:
        const char* throwException() const noexcept;
    };

private:
    std::queue<T> elements;
    Mutex mutex;
};

template <typename T> void Fifo<T>::push(T element)
{
    Mutex::Lock lock(mutex);
    elements.push(element);
    lock.notify();
    lock.~Lock();
}


template <typename T> T Fifo<T>::pop()
{
    Mutex::Lock lock(mutex);
    T popElement = elements.front();
    if (!elements.empty()==true){
        elements.pop();
    }
    else{
        lock.wait();
    }
    lock.notify();
    lock.~Lock();
    return popElement;
}

template <typename T> T Fifo<T>::pop(double timeout_ms)
{
    Mutex::Lock lock(mutex);
    T popElement = elements.front();
    if (!elements.empty()==true){
        elements.pop();
    }
    else{
        throw Fifo<T>::EmptyException();
    }
    lock.notify();
    lock.~Lock();
    return popElement;
}

template <typename T> const char *Fifo<T>::EmptyException::throwException() const noexcept
{
    return "There is no element in the FIFO!\n";
}

// class FifoProducer
class FifoProducer : public Thread
{
public:
    FifoProducer(Fifo<int> *fifo, unsigned int maxCount);
    ~FifoProducer();
    unsigned int getCounter();
    void run();

private:
    Fifo<int> *fifo;
    unsigned int counter;
    unsigned int maxCount;
};

//class FifoConsumer
class FifoConsumer : public Thread
{
public:
    FifoConsumer(Fifo<int> *fifo, unsigned int maxCount);
    ~FifoConsumer();
    unsigned int getCounter();
    void run();

private:
    Fifo<int> *fifo;
    unsigned int counter;
    unsigned int maxCount;
};



#endif //TD_4_FIFO_H
