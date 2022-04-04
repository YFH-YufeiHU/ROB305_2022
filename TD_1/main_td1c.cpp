//
// Created by Yufei Hu on 03/02/2022.
//
#include <time.h>
#include <iostream>
#include <string.h>
#include "timespec.h"

////  test for 1 thread
//struct Data {
//    volatile bool stop;
//    volatile double counter;
//};
//
//void* incrementer(void* v_data) { Data* p_data = (Data*) v_data; while (not p_data->stop) {
//        p_data->counter += 1.0;
//    }
//    return v_data;
//}
//
//int main(){
//    Data data = { false, 0.0 };
//    pthread_t incrementThread;
//
//    pthread_create(&incrementThread, nullptr, incrementer, &data);
//    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
//        std::cout << "Type 's' to stop: " << std::flush;
//    data.stop = true;
//    pthread_join(incrementThread, nullptr);
//    std::cout << "Counter value = " << data.counter << std::endl;
//
//    return 0;
//}

//// test for 3 threads
//struct Data {
//    volatile bool stop;
//    volatile double counter;
//    pthread_mutex_t mutex;
//};
//
//void* incrementer(void* v_data) { Data* p_data = (Data*) v_data; while (not p_data->stop) {
//        pthread_mutex_lock(&p_data->mutex);
//        p_data->counter += 1.0;
//        pthread_mutex_unlock(&p_data->mutex); }
//    return v_data;
//}
//int main(int argc, char* argv[]){
//
//    Data data = { false, 0.0 };
//    pthread_mutex_init(&data.mutex, nullptr);
//    pthread_t incrementThread[3];
//    pthread_create(&incrementThread[0], nullptr, incrementer, &data);
//    pthread_create(&incrementThread[1], nullptr, incrementer, &data);
//    pthread_create(&incrementThread[2], nullptr, incrementer, &data);
//    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
//        std::cout << "Type 's' to stop: " << std::flush;
//    data.stop = true;
//    for (int i=0; i<3; ++i)
//        pthread_join(incrementThread[i], nullptr);
//
//    pthread_mutex_destroy(&data.mutex);
//    std::cout << "Counter value = " << data.counter << std::endl;
//}

//// test for td 1c
using loop_t = unsigned long int;
void incr(loop_t nLoops, double* pCounter){
    for(loop_t iLoops=0; iLoops<nLoops; ++iLoops){
        *pCounter +=1;
    }
}

int main(int argc, char* argv[]){
    loop_t nLoops = std::stoul(argv[1], NULL, 10);
    double counter = 0.0;
    struct timespec time_start, time_end;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time_start);
    incr(nLoops, &counter);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time_end);

    std::cout<<(time_end-time_start).tv_sec<<"s"<<(time_end-time_start).tv_nsec<<"us"<<std::endl;
    return 0;

}