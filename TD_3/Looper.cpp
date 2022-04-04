//
// Created by Yufei Hu on 16/03/2022.
//
#include <iostream>
#include "Looper.h"

Looper::Looper() {
    doStop = false;
    iLoop = 0;
}
Looper::~Looper() {}

void Looper::runLoop(double nLoops) {
    while(iLoop<nLoops && doStop== false){
        iLoop+=1;
    }
}

double Looper::getSample() {
    return iLoop;
}

double Looper::stopLoop() {
    doStop = true;
    return getSample();
}

//class Calibrator
Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples) {
    a=0.0, b=0.0;

    double x_average=0.0,y_average=0.0;
    double xy_sum=0.0, x2_sum=0.0;

    this->nSamples = nSamples;
    start(samplingPeriod_ms);
    looper.runLoop();
    stop();

    for (int i =0;i < nSamples;i++){
        std::cout<<"Working on "<<i+1<<"th sample..."<<std::endl;
        x_average+=(i+1)*samplingPeriod_ms;
        y_average+= samples[i];
        xy_sum += (i+1)*samplingPeriod_ms*samples[i];
        x2_sum += (i+1)*(i+1)*samplingPeriod_ms*samplingPeriod_ms;
    }
    x_average /= nSamples;
    y_average /= nSamples;
    a = (xy_sum-nSamples*x_average*y_average)/(x2_sum-nSamples*x_average*x_average);
    b = y_average-a*x_average;

    std::cout << "a :" << a << std::endl;
    std::cout << "b :" << b << std::endl;

}
Calibrator::~Calibrator() {}

double Calibrator::nLoops(double duration_ms) {
    double l = a*duration_ms + b;
    return l;
}

void Calibrator::callback() {
    double samples_ = looper.getSample();
    samples.push_back(samples_);
    if(samples.size()==nSamples){
        looper.stopLoop();
    }
}

//class CpuLoop
CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator(calibrator) {}

void CpuLoop::runTime(double duration_ms) {
    runLoop(calibrator.nLoops(duration_ms));
}