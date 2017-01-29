cmake_minimum_required(VERSION 2.6)
project(hackerrank)

add_executable(euler14 collatz.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(.)

install(TARGETS euler14 RUNTIME DESTINATION bin)
