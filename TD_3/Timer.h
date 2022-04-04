//
// Created by Yufei Hu on 03/03/2022.
//

#ifndef TD_3_TIMER_H
#define TD_3_TIMER_H

#include <time.h>
#include <signal.h>

class Timer
{
public:
    Timer();
    ~Timer();

    void start(double duration_ms);
    void stop();

protected:
    timer_t timerId;
    virtual void callback() = 0;

private:
    static void call_callback(int, siginfo_t* si, void*);
};

class PeriodicTimer : public Timer
{
public:
    void start(double duration_ms);
};

#endif //TD_3_TIMER_H
