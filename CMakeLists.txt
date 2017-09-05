cmake_minimum_required(VERSION 3.0)

project(sr_find)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -O")
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.64.0 REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS} /src/)

aux_source_directory(src SOURCE_LIST)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


