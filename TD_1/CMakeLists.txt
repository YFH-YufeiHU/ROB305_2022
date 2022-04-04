cmake_minimum_required(VERSION 3.10)
project(TD_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TD_1a
        main_td1a.cpp
        timespec.cpp
        timespec.h)
add_executable(TD_1b
        main_td1b.cpp
        timespec.h
        )
add_executable(TD_1c
        main_td1c.cpp
        timespec.cpp
        timespec.h)

add_executable(TD_1d
        main_td1d.cpp
        timespec.cpp
        timespec.h)

add_executable(TD_1e
        main_td1e.cpp
        timespec.cpp
        timespec.h)

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(TD_1a ${LIBRT})
    target_link_libraries(TD_1b ${LIBRT})
    target_link_libraries(TD_1c ${LIBRT})
    target_link_libraries(TD_1d ${LIBRT})
    target_link_libraries(TD_1e ${LIBRT})
endif()

find_library(Library pthread)
if(Library)
    target_link_libraries(TD_1a ${Library})
    target_link_libraries(TD_1b ${Library})
    target_link_libraries(TD_1c ${Library})
    target_link_libraries(TD_1d ${Library})
    target_link_libraries(TD_1e ${Library})
endif()