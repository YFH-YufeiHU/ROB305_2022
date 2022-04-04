//
// Created by Yufei Hu on 17/03/2022.
//


#include <iostream>

#include "PosixThread.h"
#include "Mutex.h"
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

    Mutex mutex;
    IncrThreadWithMutex* incrThreadWithMutex[nTasks];
    Chrono chrono;

    for(loop_t i=0;i<nTasks;i++){
        incrThreadWithMutex[i] = new IncrThreadWithMutex(&data,&mutex);
    }
    for (loop_t i=0;i<nTasks;i++){
        incrThreadWithMutex[i]->start();
    }
    for (loop_t i=0;i<nTasks;i++){
        incrThreadWithMutex[i]->join();
    }
    chrono.stop();
    std::cout<<"Counter value with custom mutex ===>["<<incrThreadWithMutex[0]->data->counter<<"]"<<std::endl;
    std::cout<<"Execution time in the case of with using custom mutex is ===>["<<chrono.lap()<<"ms]"<<std::endl;
    //for(int i=0;i<nTasks;i++){
    //    delete incrThreadWithMutex[i];
    //}

    return 0;
}
