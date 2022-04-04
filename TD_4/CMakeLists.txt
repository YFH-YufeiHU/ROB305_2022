cmake_minimum_required(VERSION 3.10)
project(TD_4)

set(CMAKE_CXX_STANDARD 11)

add_executable(TD_4 main.cpp)



add_executable(TD_4a
        main_td4a.cpp
        Mutex.h
        Mutex.cpp
        Chrono.h
        Chrono.cpp
        PosixThread.cpp
        PosixThread.h
        timespec.cpp
        timespec.h)

add_executable(TD_4b
        main_td4b.cpp
        Mutex.h
        Mutex.cpp
        Chrono.h
        Chrono.cpp
        PosixThread.cpp
        PosixThread.h
        timespec.cpp
        timespec.h)

add_executable(TD_4c
        main_td4c.cpp
        Mutex.h
        Mutex.cpp
        PosixThread.cpp
        PosixThread.h
        timespec.cpp
        timespec.h
        Semaphore.cpp
        Semaphore.h
        )


add_executable(TD_4d
        main_td4d.cpp
        Mutex.h
        Mutex.cpp
        PosixThread.cpp
        PosixThread.h
        timespec.cpp
        timespec.h
        Fifo.cpp
        Fifo.h
        )

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(TD_4a ${LIBRT})
    target_link_libraries(TD_4b ${LIBRT})
    target_link_libraries(TD_4c ${LIBRT})
    target_link_libraries(TD_4d ${LIBRT})
endif()

find_library(Library pthread)
if(Library)
    target_link_libraries(TD_4a ${Library})
    target_link_libraries(TD_4b ${Library})
    target_link_libraries(TD_4c ${Library})
    target_link_libraries(TD_4d ${Library})
endif()
