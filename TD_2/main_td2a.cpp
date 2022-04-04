//
// Created by Yufei Hu on 10/02/2022.
//

#include <signal.h>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <vector>

struct Data {
    volatile unsigned int nLoops;
    volatile double counter;
};

using loop_t = unsigned int;
void incr(volatile loop_t nLoops, volatile double* pCounter);
void* call_incr(void* v_data);

void incr(volatile loop_t nLoops, volatile double* pCounter){
    for (unsigned i=0; i<nLoops; i++){
        *pCounter += 1.0;
    }
}

void* call_incr(void* v_data){
    Data* data_ = (Data*) v_data;
    incr(data_ -> nLoops, &data_ -> counter);
    return v_data;
}

int main(int argc, char* argv[])
{
    if (argc < 3){
        std::cerr<<"Please specify nLoops and nTasks!"<<std::endl;
        return  1;
    }
    loop_t nLoops = std::stoi(argv[1]);
    loop_t nTasks = std::stoi(argv[2]);

    Data data = {nLoops, 0.0};
    std::vector<pthread_t> incrementThread(nTasks);

    for (loop_t i=0;i<nTasks;i++){
        pthread_create(&incrementThread[i], NULL, call_incr, (void*)&data);
    }

    for (loop_t i=0; i<nTasks;i++) {
        pthread_join(incrementThread[i], NULL);
    }

    std::cout << "Counter : " <<  data.counter << std::endl;
    return 0;
}