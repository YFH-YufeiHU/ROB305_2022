//
// Created by Yufei Hu on 16/03/2022.
//

#ifndef TD_3_LOOPER_H
#define TD_3_LOOPER_H

#include <vector>

#include "Timer.h"
#include "Mutex.h"
#include "PosixThread.h"
#include "timespec.h"

class Looper {
public:
    Looper();
    ~Looper();
    void runLoop(double nLoops = __DBL_MAX__);
    double getSample();
    double stopLoop();
private:
    bool doStop;
    double iLoop;
};

class Calibrator : public PeriodicTimer{
public:
    Calibrator(double samplingPeriod_ms, unsigned nSamples);
    ~Calibrator();
    double nLoops(double duration_ms);

protected:
    void callback();

private:
    double a,b;
    std::vector<double> samples;
    Looper looper;
    unsigned int nSamples;
};

class CpuLoop : public Looper{
public:
    CpuLoop(Calibrator& calibrator);
    void runTime(double duration_ms);
private:
    Calibrator& calibrator;
};

class CpuLoopWithMutexPriority : public Thread{
public:
    CpuLoopWithMutexPriority(CpuLoop* cpuLoop, Mutex* mutex,double timeBeforeStart,double timeExecution, double timeTotal);
    ~CpuLoopWithMutexPriority();
    void run();
    CpuLoop* cpuLoop;

private:
    Mutex* mutex;
    double timeBeforeStart;
    double timeExecution;
    double timeTotal;
};



#endif //TD_3_LOOPER_H
