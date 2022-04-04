//
// Created by Yufei Hu on 03/04/2022.
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
    timer_delete(tid);
}

// calculate a and b with linear regression
void calculateParametersWithLeastSquares(struct parameters & paras){
    double x_average=0.0,y_average=0.0;
    double xy_sum=0.0, x2_sum=0.0;
    double y_value=0.0;
    int n = 10; // samples

    for (int i =0;i < n;i++){
        std::cout<<"Working on "<<i+1<<"th sample..."<<std::endl;
        y_value=0.0;
        x_average+=i+1;
        Timer(i+1,y_value);
        y_average+= y_value;
        xy_sum += (i+1)*y_value;
        x2_sum += (i+1)*(i+1);
    }
    x_average /= n;
    y_average /= n;
    paras.a = (xy_sum-n*x_average*y_average)/(x2_sum-n*x_average*x_average);
    paras.b = y_average-paras.a*x_average;
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

    // calculate a and b with linear regression
    calculateParametersWithLeastSquares(paras);
    std::cout<<" a :"<<paras.a
             <<" b :"<<paras.b<<std::endl;

    // test a and b
    double estimateValue,groundTruth;
    estimateValue = paras.a*8 + paras.b;
    groundTruth = 0.0;
    Timer(8,groundTruth);
    std::cout<< " (LeastSquares)Estimated value with parameters a and b when t=8s is :"<<estimateValue<<'\n'
             << " (LeastSquares)Real Value when t=8s is :"<<groundTruth<<std::endl;

    return 0;
}

