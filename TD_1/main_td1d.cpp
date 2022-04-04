//
// Created by Yufei Hu on 10/02/2022.
//

#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "timespec.h"
#include <climits>
#include "signal.h"
#include <climits>

struct parameters{
    double a;
    double b;
};

void myHandler(int, siginfo_t* si, void*)
{
    *((bool*)si->si_value.sival_ptr) = true;
}

unsigned int incr(unsigned int nLoops, double* pCounter, bool* pStop)
{
    unsigned int iLoop;
    for(iLoop = 0; iLoop < nLoops; ++iLoop)
    {
        if (*pStop == true) break;
        *pCounter += 1.0;
    }
    return iLoop;
}

void Timer(double duration_s,double& counter){

    int nLoops = UINT_MAX;
    bool pStop = false;

    struct sigaction sa;
    timer_t tid;

    // define the sigaction
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    // define the sigevent
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*)&pStop;

    timer_create(CLOCK_REALTIME,&sev,&tid);
    itimerspec its;
    its.it_interval.tv_sec = 0;  // the time interval
    its.it_interval.tv_nsec = 0;
    its.it_value.tv_sec = duration_s;   // the delay time start
    its.it_value.tv_nsec = 0;
    timer_settime(tid,0,&its, nullptr);

    unsigned int iLoop = incr(nLoops, &counter, &pStop);
    std::cout<<"iLoop :"<<iLoop<<std::endl;
    timer_delete(tid);
}

void calculateParameters(struct parameters & paras){
    double couter_y_1 = 0.0;
    double couter_y_2 = 0.0;
    Timer(4,couter_y_1);
    Timer(6,couter_y_2);
    paras.a = (couter_y_2-couter_y_1)/(6-4);
    paras.b = couter_y_1-paras.a*4;
}

int main(int , char**)
{
    double counter = 0.0;
    Timer(1,counter);
    struct parameters paras;

    // test timer function
    timespec time_start,time_end;
    time_start = timespec_now();
    Timer(1,counter);
    time_end = timespec_now();
    std::cout<< " Time :" <<timespec_to_ms(time_end-time_start)<<std::endl;
    std::cout << " Counter :" << counter<<std::endl;

    // calculate a and b
    calculateParameters(paras);
    std::cout<<" a :"<<paras.a
             <<" b :"<<paras.b<<std::endl;

    // test a and b
    double estimateValue,groundTruth;
    estimateValue = paras.a*8 + paras.b;
    groundTruth = 0.0;
    Timer(8,groundTruth);
    std::cout<< " Estimated value with parameters a and b when t=8s is :"<<estimateValue<<'\n'
             << " Real Value when t=8s is :"<<groundTruth<<std::endl;

    return 0;
}



