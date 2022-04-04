//
// Created by Yufei Hu on 10/02/2022.
//

#include <signal.h>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <time.h>

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
    if (argc < 4){
        std::cerr<<"Please specify nLoops, nTasks and Policy!"<<std::endl;
        return  1;
    }

    loop_t nLoops = std::stoi(argv[1]);
    loop_t nTasks = std::stoi(argv[2]);
    loop_t nSchedPolicy = std::stoi(argv[3]);
    std::cout<< "nLoops: "<<nLoops<<"   nTasks: "<<nTasks<<std::endl;

    int schedPolicy;
    if(nSchedPolicy == 0) {
        schedPolicy = SCHED_RR;
        std::cout<< "SCHED_RR"<<std::endl;
    }
    else if( nSchedPolicy == 1) {
        schedPolicy = SCHED_FIFO;
        std::cout<< "SCHED_FIFO"<<std::endl;
    }
    else {
        schedPolicy = SCHED_OTHER;
        std::cout<< "SCHED_OTHER"<<std::endl;
    }

    sched_param schedParam;
    schedParam.sched_priority = sched_get_priority_max(schedPolicy);
    pthread_setschedparam(pthread_self(), schedPolicy, &schedParam);

    Data data = {nLoops, 0.0};

    volatile bool stop = false;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, schedPolicy);
    sched_param schedParams;
    schedParams.sched_priority = 9;
    pthread_attr_setschedparam(&attr, &schedParams);

    std::vector<pthread_t> incrementThread(nTasks);
    struct timespec time_start, time_end;

    clock_gettime(CLOCK_REALTIME,&time_start);
    for (loop_t i=0;i<nTasks;i++)
    {
        pthread_create(&incrementThread[i], &attr, call_incr, (void*)&data);
    }
    for (loop_t i=0; i<nTasks;i++) {
        pthread_join(incrementThread[i], NULL);
    }
    std::cout << "Counter : " <<  data.counter << std::endl;
    clock_gettime(CLOCK_REALTIME,&time_end);

    std::cout<<"Time : "<<(time_end.tv_sec-time_start.tv_sec)<<"s"<<(time_end.tv_nsec-time_start.tv_nsec)<<"us"<<std::endl;

    return 0;
}