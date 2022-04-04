#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "timespec.h"

// part 1
double timespec_to_ms(const timespec& time_ts){
	double time_ms=0.0;
	time_ms = time_ts.tv_sec*1e3 + time_ts.tv_nsec/1e6;
	return time_ms;
}
timespec timespec_from_ms(double time_ms){
    timespec time_ts;
    time_ts.tv_sec = int(time_ms/1e3);
    time_ts.tv_nsec = (time_ms - time_ts.tv_sec*1e3) * 1e6;
    return time_ts;
}

// part 2
timespec timespec_now(){
    timespec time_ts_now;
	clock_gettime(CLOCK_REALTIME, &time_ts_now);
	return time_ts_now;
}
timespec timespec_negate(const timespec& time_ts){
    timespec time_ts_negative;
	time_ts_negative.tv_sec = - time_ts.tv_sec;
	time_ts_negative.tv_nsec = - time_ts.tv_nsec;
	return time_ts_negative; 
}

// part 3
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts){
    timespec time_ts_add;
	time_ts_add.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
	time_ts_add.tv_nsec  = time1_ts.tv_nsec + time2_ts.tv_nsec;
    if (time_ts_add.tv_nsec >= 1e9)
    {
        time_ts_add.tv_nsec -= 1e9;
        time_ts_add.tv_sec += 1;
    }
    return time_ts_add;
}
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){
	struct timespec time_ts_sub;
	time_ts_sub.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
	time_ts_sub.tv_nsec = time1_ts.tv_nsec-time2_ts.tv_nsec;
	if (time_ts_sub.tv_nsec < 0){
		time_ts_sub.tv_sec -=1;
		time_ts_sub.tv_nsec +=1e9;
	}
	return time_ts_sub;
}

// part 4
timespec timespec_wait(const timespec& delay_ts){
    nanosleep(&delay_ts,NULL);
    return delay_ts;
}

// part 5
timespec  operator- (const timespec& time_ts){
    return timespec_negate(time_ts);
}
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts){
    return timespec_add(time1_ts, time2_ts);
}
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts){
    return timespec_subtract(time1_ts, time2_ts);
}
timespec& operator+= (timespec& time_ts, const timespec& delay_ts){
    timespec* time;
    *time = timespec_add(time_ts, delay_ts);
    return *time;
}
timespec& operator-= (timespec& time_ts, const timespec& delay_ts){
    timespec* time;
    *time =  timespec_subtract(time_ts, delay_ts);
    return *time;
}
bool operator== (const timespec& time1_ts, const timespec& time2_ts){
    bool flag = false;
    if(time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec == time2_ts.tv_nsec){
        flag = true;
    }
    return flag;
}
bool operator!= (const timespec& time1_ts, const timespec& time2_ts){
    bool flag = false;
    if(time1_ts.tv_sec != time2_ts.tv_sec || time1_ts.tv_nsec != time2_ts.tv_nsec){
        flag = true;
    }
    return  flag;
}
bool operator< (const timespec& time1_ts, const timespec& time2_ts){
    bool flag = false;
    if(time1_ts.tv_sec < time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec < time2_ts.tv_nsec)){
        flag = true;
    }
    return flag;
}
bool operator> (const timespec& time1_ts, const timespec& time2_ts){
    bool flag = false;
    if(time1_ts.tv_sec > time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec > time2_ts.tv_nsec)){
       flag = true;
    }
    return flag;
}

