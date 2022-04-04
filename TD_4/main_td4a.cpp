//
// Created by Yufei Hu on 10/03/2022.
//

#include <iostream>

#include "PosixThread.h"
#include "Chrono.h"

using loop_t = unsigned int;

int main(int argc, char* argv[]){

    if (argc < 3){
        std::cerr<<"please  specify  nLoops and nTasks !"<<std::endl;
        return  1;
    }
    loop_t nLoops = std::stoi(argv[1]);
    loop_t nTasks = std::stoi(argv[2]);
    Data data = {nLoops,0.0};

    double execTime=0;
    IncrThread* incrThread[nTasks];
    Chrono chrono;

    for(int i=0;i<nTasks;i++){
        incrThread[i] = new IncrThread(&data);
    }
    for (int i=0;i<nTasks;i++){
        incrThread[i]->start();
        execTime += incrThread[i]->execTime_ms();
    }
    for (int i=0;i<nTasks;i++){
        incrThread[i]->join();
    }
    chrono.stop();
    std::cout<<"Counter value without mutex ===>["<<incrThread[0]->data->counter<<"]"<<std::endl;
    std::cout<<"Execution time in the case of without using mutex is ===>["<<chrono.lap()<<" ms]"<<std::endl;
    for(int i=0;i<nTasks;i++){
        delete incrThread[i];
    }

    return 0;
}