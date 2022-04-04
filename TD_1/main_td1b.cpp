//
// Created by Yufei Hu on 02/02/2022.
//
#include <time.h>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

void myHandler(int, siginfo_t* si, void*)
{
    int* p_counter = (int*)si->si_value.sival_ptr;
    *p_counter += 1;
    std::cout <<*p_counter << std::endl;
}

int main()
{
    volatile int counter = 0;

    // define the sigaction
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  // in order to use the sa_sigaction as the call_back function
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    // define the sigevent
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*) &counter;

    timer_t tid;
    int ret;
    ret = timer_create(CLOCK_REALTIME, &sev, &tid);

    // launch timer
    struct itimerspec its;
    its.it_value.tv_sec = 0; // the delay time start
    its.it_value.tv_nsec = 5e8;
    its.it_interval.tv_sec = 0;  // the time interval
    its.it_interval.tv_nsec = 5e8;

    timer_settime(tid, 0, &its, NULL);

    while(counter < 15)
        continue;

    // destroy the timer
    timer_delete(tid);
    return 0;
}


