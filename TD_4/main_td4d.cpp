//
// Created by Yufei Hu on 03/04/2022.
//

#include <iostream>

#include "Fifo.h"


using loop_t = unsigned int;

int main(int argc, char* argv[]){

    if (argc < 3){
        std::cerr<<"please  specify  nProd and nCons !"<<std::endl;
        return  1;
    }
    loop_t nProd = std::stoi(argv[1]);
    loop_t nCons = std::stoi(argv[2]);
    loop_t maxCount = 1e5;
    loop_t token_fifo=0;

    Fifo<int> fifo;
    FifoProducer* fifoProducer[nProd];
    FifoConsumer* fifoConsumer[nCons];

    //producer
    for(unsigned int i=0;i< nProd;++i){
        fifoProducer[i] = new FifoProducer(&fifo,maxCount);
    }
    for(unsigned int i=0;i< nProd;++i){
        fifoProducer[i]->start();
    }
    for(unsigned int i=0;i< nProd;++i) {
        fifoProducer[i]->join();
        token_fifo += fifoProducer[i]->getCounter();
    }
    std::cout<<"Tokens (fifo) of fifo Producer :"<<token_fifo<<std::endl;

    //consumers
    for(unsigned int i=0;i< nCons;++i){
        fifoConsumer[i] = new FifoConsumer(&fifo,maxCount);
    }
    for(unsigned int i=0;i< nCons;++i){
        fifoConsumer[i]->start();
    }
    for(unsigned int i=0;i< nCons;++i){
        fifoConsumer[i]->join();
        token_fifo -= fifoConsumer[i]->getCounter();
    }
    std::cout<<"Tokens (fifo) after fifo Consumer :"<<token_fifo<<std::endl;

    for(int i=0;i<nCons;i++){
        delete fifoConsumer[i];
    }
    for(int i=0;i<nProd;i++){
        delete fifoProducer[i];
    }
    return 0;
}