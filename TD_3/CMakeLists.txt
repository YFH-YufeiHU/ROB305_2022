cmake_minimum_required(VERSION 3.10)
project(TD_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(TD_3 main.cpp)

add_executable(TD_3a
        main_td3a.cpp
        timespec.cpp
        timespec.h
        Chrono.cpp
        Chrono.h)

add_executable(TD_3b
        main_td3b.cpp
        timespec.cpp
        timespec.h
        Timer.cpp
        Timer.h
        CountDown.cpp
        CountDown.h)

add_executable(TD_3c
        main_td3c.cpp
        timespec.cpp
        timespec.h
        Timer.cpp
        Timer.h
        Looper.cpp
        Looper.h)

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(TD_3a ${LIBRT})
    target_link_libraries(TD_3b ${LIBRT})
    target_link_libraries(TD_3c ${LIBRT})
endif()

find_library(Library pthread)
if(Library)
    target_link_libraries(TD_3a ${Library})
    target_link_libraries(TD_3b ${Library})
    target_link_libraries(TD_3c ${Library})
endif()