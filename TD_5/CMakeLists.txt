cmake_minimum_required(VERSION 3.10)
project(TD_5)

set(CMAKE_CXX_STANDARD 11)

add_executable(TD_5 main.cpp)

add_executable(TD_5a
        main_td5a.cpp
        Mutex.h
        Mutex.cpp
        PosixThread.cpp
        PosixThread.h
        Timer.cpp
        Timer.h
        timespec.cpp
        timespec.h
        Looper.cpp
        Looper.h
        Chrono.cpp
        Chrono.h
        )


find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(TD_5a ${LIBRT})
endif()

find_library(Library pthread)
if(Library)
    target_link_libraries(TD_5a ${Library})
endif()
