//
// Created by Yufei Hu on 03/04/2022.
//

#include <time.h>
#include <iostream>

#include "Looper.h"
#include "Mutex.h"


int main(){
    // make sure the core is single
    cpu_set_t  myCpuSet;
    CPU_ZERO(&myCpuSet);
    CPU_SET(0, &myCpuSet);
    sched_setaffinity(0, sizeof(cpu_set_t), &myCpuSet);

    Mutex mutex(false);
    Calibrator calibrator(1000,10);
    CpuLoop cpuLoop1(calibrator);
    CpuLoop cpuLoop2(calibrator);
    CpuLoop cpuLoop3(calibrator);

    // set priority
    int priority1 = 10;
    int priority2 = 40;
    int priority3 = 80;

    // in order to make sure tasks can be executed cyclically, ensuring fairness
    int policy = SCHED_RR;

    CpuLoopWithMutexPriority cpuLoopWithMutexPriority1(&cpuLoop1,&mutex,40,10,10);
    CpuLoopWithMutexPriority cpuLoopWithMutexPriority2(&cpuLoop1,&mutex,10,-1,-1);
    CpuLoopWithMutexPriority cpuLoopWithMutexPriority3(&cpuLoop3,&mutex,50,20,20);

    cpuLoopWithMutexPriority1.setScheduling(policy,priority1);
    cpuLoopWithMutexPriority2.setScheduling(policy,priority2);
    cpuLoopWithMutexPriority3.setScheduling(policy,priority3);

    cpuLoopWithMutexPriority1.start();
    cpuLoopWithMutexPriority2.start();
    timespec_wait(timespec_from_ms(1000));
    cpuLoopWithMutexPriority3.start();

    cpuLoopWithMutexPriority1.join();
    cpuLoopWithMutexPriority2.join();
    cpuLoopWithMutexPriority3.join();

    std::cout<<"Value of cpu looper 1 :"<<cpuLoopWithMutexPriority1.cpuLoop->getSample()<<"\n"
             <<"Execution time :" <<cpuLoopWithMutexPriority1.execTime_ms()<<std::endl;
    std::cout<<"Value of cpu looper 2 :"<<cpuLoopWithMutexPriority2.cpuLoop->getSample()<<"\n"
             <<"Execution time :" <<cpuLoopWithMutexPriority2.execTime_ms()<<std::endl;
    std::cout<<"Value of cpu looper 3 :"<<cpuLoopWithMutexPriority3.cpuLoop->getSample()<<"\n"
             <<"Execution time :" <<cpuLoopWithMutexPriority3.execTime_ms()<<std::endl;

    return 0;
}
