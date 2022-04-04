//
// Created by Yufei Hu on 16/03/2022.
//

#include "Looper.h"
#include <iostream>

int main(){
    Calibrator calibrator = Calibrator(1000, 10);
    CpuLoop cpuLoop = CpuLoop(calibrator);

    cpuLoop.runTime(2000);
    std::cout<< "Current value of Loop:"<<cpuLoop.getSample()<<std::endl;
    std::cout<< "Estimated value of Loop:"<<calibrator.nLoops(2000)<<std::endl;
    return 0;
}