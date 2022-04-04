cmake_minimum_required(VERSION 3.10)
project(TD_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(TD_2 main.cpp)

add_executable(TD_2a
        main_td2a.cpp)

add_executable(TD_2b
        main_td2b.cpp)

add_executable(TD_2c
        main_td3c.cpp)



find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(TD_2a ${LIBRT})
    target_link_libraries(TD_2b ${LIBRT})
    target_link_libraries(TD_2c ${LIBRT})
endif()

find_library(Library pthread)
if(Library)
    target_link_libraries(TD_2a ${Library})
    target_link_libraries(TD_2b ${Library})
    target_link_libraries(TD_2c ${Library})
endif()