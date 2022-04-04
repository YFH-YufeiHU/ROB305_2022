//
// Created by Yufei Hu on 02/02/2022.
//
#include <iostream>
#include <time.h>

#include "timespec.h"

int main(){
    timespec time_ts_1,time_ts_2;
    timespec time_ts_now,time_ts_negate;
    double time_ms;
    bool flag;
    timespec time_ts;
    time_ts_1.tv_sec = 1;
    time_ts_1.tv_nsec = 5e8;
    time_ts_2.tv_sec = 2;
    time_ts_2.tv_nsec = 6e8;
	// Test part2

	time_ts_now = timespec_now();
    std::cout<<"Test part 2"<<std::endl;
    std::cout <<"Test for the function timespec_now()   ===>"<< "secondes:" << time_ts_now .tv_sec << ", nanosec: " << time_ts_now.tv_nsec << std::endl;
    time_ts_negate = timespec_negate(time_ts_now);
    std::cout <<"Test for the function timespec_negate()    ===>"<< "secondes:" << time_ts_negate .tv_sec << ", nanosec: " << time_ts_negate.tv_nsec << std::endl;


    // Test part1
    time_ms = 2500;
    time_ts = timespec_from_ms(time_ms);
    std::cout<<"Test part 1"<<std::endl;
    std::cout <<"Test for the function timespec_to_ms()   ===>"<< "ms:" << timespec_to_ms(time_ts_1) << std::endl;
    std::cout <<"Test for the function timespec_from_ms()   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;


    // Test part3
    time_ts = timespec_add(time_ts_1,time_ts_2);
    std::cout<<"Test part 3"<<std::endl;
    std::cout <<"Test for the function timespec_add()   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;
    time_ts = timespec_subtract(time_ts_1,time_ts_2);
    std::cout <<"Test for the function timespec_subtract()   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;

    // Test part4
    time_ts = timespec_wait(time_ts_1);
    std::cout<<"Test part 4"<<std::endl;
    std::cout <<"Test for the function timespec_wait()   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;

    // Test part5
    time_ts = -time_ts_1;
    std::cout<<"Test part 5"<<std::endl;
    std::cout <<"Test for the function operator -   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;
    time_ts = time_ts_1 + time_ts_2;
    std::cout <<"Test for the function operator +   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;
    time_ts = time_ts_1 - time_ts_2;
    std::cout <<"Test for the function operator -   ===>"<< "secondes:" << time_ts.tv_sec << ", nanosec: " << time_ts.tv_nsec << std::endl;
    if (time_ts_1==time_ts_2)
        std::cout <<"Test for the function operator ==   ===>"<< "=="  << std::endl;
    if (time_ts_1!=time_ts_2)
        std::cout <<"Test for the function operator !=   ===>"<< "!="  << std::endl;
    if (time_ts_1>time_ts_2)
        std::cout <<"Test for the function operator >   ===>"<< ">"  << std::endl;
    if (time_ts_1<time_ts_2)
        std::cout <<"Test for the function operator <   ===>"<< "<"  << std::endl;
    return 0;
}
