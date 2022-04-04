//
// Created by Yufei Hu on 03/03/2022.
//
#include <iostream>
#include <istream>
#include "CountDown.h"


int main()
{
    std::cout<<"Test for the new class CountDown which is based on timer!"<<std::endl;

    CountDown countDown(15);
    countDown.start(500);

    while (countDown.getCount() > 0){}

    return 0;
}