//
// Created by Yufei Hu on 02/04/2022.
//

#include "Fifo.h"
//class FifoProducer
FifoProducer::FifoProducer(Fifo<int> *fifo, unsigned int maxCount) : Thread(){
    this->fifo = fifo;
    this->counter = 0;
    this->maxCount = maxCount;
}

FifoProducer::~FifoProducer(){}

unsigned int FifoProducer::getCounter() {
    return counter;
}

void FifoProducer::run() {
    for(unsigned int i =0;i< maxCount;++i){
        fifo->push(i);
        counter++;
    }
}

//class FifoConsumer
FifoConsumer::FifoConsumer(Fifo<int> *fifo,unsigned int maxCount) : Thread(){
    this->fifo = fifo;
    this->counter = 0;
    this->maxCount = maxCount;
}

FifoConsumer::~FifoConsumer(){}

void FifoConsumer::run() {
    while(true){
        try{
            fifo->pop(500);
            counter++;
            if(counter==maxCount)break;
        }
        catch(const Fifo<int>::EmptyException& e)
        {
            break;
        }
    }
}

unsigned int FifoConsumer::getCounter()
{
    return counter;
}
