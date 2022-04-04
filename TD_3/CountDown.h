//
// Created by Yufei Hu on 03/03/2022.
//

#ifndef TD_3_COUNTDOWN_H
#define TD_3_COUNTDOWN_H

#include "Timer.h"

class CountDown : public PeriodicTimer
{

public:
    CountDown(int n);
    int getCount();
protected:
    void callback();
private:
    int count;
};

#endif //TD_3_COUNTDOWN_H
