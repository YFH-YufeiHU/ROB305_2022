//
// Created by Yufei Hu on 03/03/2022.
//

#include <iostream>
#include <unistd.h>
#include "Chrono.h"
#include "timespec.h"

int main() {
    std::cout << "Test for the class timespec and the class chrono" << std::endl;
    std::cout << "Sleeping for 2s" << std::endl;

    timespec myTimeStart;
    timespec myTimeStop;

    Chrono chrono;
    myTimeStart = timespec_now();
    sleep(2);
    chrono.stop();
    myTimeStop = timespec_now();

    // Verify the object Chrono
    std::cout << "Time measured by TimeSpec :" << (timespec_to_ms(myTimeStop-myTimeStart)) << "ms" << std::endl;
    std::cout << "Time measured by Chrono :" << chrono.lap() << " ms" << std::endl;
    return 0;
}