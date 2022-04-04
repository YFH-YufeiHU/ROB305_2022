//
// Created by Yufei Hu on 03/03/2022.
//

#include <signal.h>
#include "Timer.h"
#include "timespec.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;
    timer_create(CLOCK_REALTIME, &sev, &timerId);
}

Timer::~Timer()
{
    timer_delete(timerId);
}


void Timer::start(double duration_ms)
{
    itimerspec its;

    its.it_value = timespec_from_ms(duration_ms);
    its.it_interval=timespec_from_ms(duration_ms);

    timer_settime(timerId, 0, &its, NULL);
}


void Timer::stop()
{
    itimerspec its;

    its.it_value = timespec_from_ms(0.0);
    its.it_interval= timespec_from_ms(0.0);

    timer_settime(timerId, 0, &its, NULL);
}

void Timer::call_callback(int, siginfo_t* si, void*)
{
    Timer* timer = (Timer*) si->si_value.sival_ptr;
    timer->callback();
}

// class PeriodicTimer
void PeriodicTimer::start(double duration_ms) {

    itimerspec its;

    its.it_value = timespec_from_ms(duration_ms);
    its.it_interval = timespec_from_ms(duration_ms);;

    timer_settime(timerId, 0, &its, NULL);
}
