//
// Created by Yufei Hu on 26/03/2022.
//

#include <iostream>

#include "Semaphore.h"


using loop_t = unsigned int;

int main(int argc, char* argv[]){

    if (argc < 3){
        std::cerr<<"please  specify  nProd and nCons !"<<std::endl;
        return  1;
    }
    loop_t nProd = std::stoi(argv[1]);
    loop_t nCons = std::stoi(argv[2]);
    unsigned int maxCount = 1e5;
    unsigned int Tokens = 0;

    Semaphore semaphore;
    SemaphoreProducer* semaphoreProducer[nProd];
    SemaphoreConsumer* semaphoreConsumer[nCons];

    for(loop_t i=0;i< nProd;++i){
        semaphoreProducer[i] = new SemaphoreProducer(&semaphore,maxCount);
    }
    for(loop_t i=0;i< nProd;++i){
        semaphoreProducer[i]->start();
    }
    for(loop_t i=0;i< nProd;++i) {
        semaphoreProducer[i]->join();
        Tokens += semaphoreProducer[i]->getCounter();
    }
    std::cout<<"Tokens of semaphore Producer :"<<Tokens<<std::endl;


    for(loop_t i=0;i< nCons;++i){
        semaphoreConsumer[i] = new SemaphoreConsumer(&semaphore,maxCount);
    }
    for(loop_t i=0;i< nCons;++i){
        semaphoreConsumer[i]->start();
    }
    for(loop_t i=0;i< nCons;++i){
        semaphoreConsumer[i]->join();
        Tokens -= semaphoreConsumer[i]->getCounter();
    }
    std::cout<<"Tokens of semaphore Consumer :"<<Tokens<<std::endl;

    
    return 0;
}
