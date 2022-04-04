//
// Created by Yufei Hu on 03/03/2022.
//

#ifndef TD_3_CHRONO_H
#define TD_3_CHRONO_H
#include <time.h>

class Chrono
{
private:
    timespec startTime_;
    timespec stopTime_;

public:
    Chrono();
    void stop();
    void restart();
    bool isActive();
    double startTime();
    double stopTime();
    double lap();
};

#endif //TD_3_CHRONO_H
