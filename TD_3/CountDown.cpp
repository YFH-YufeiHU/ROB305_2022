//
// Created by Yufei Hu on 03/03/2022.
//

#include <iostream>
#include "CountDown.h"

CountDown::CountDown(int n)
{
    count = n;
}

int CountDown::getCount()
{
    return count;
}

void CountDown::callback()
{
    if (count >= 0){
        std::cout << "Current Counter Value : " << count << std::endl;
        count-=1;
    }
    else{
        std::cout << "Current Counter Value is less than 0, and we stop here." << std::endl;
        CountDown::stop();
    }
}
