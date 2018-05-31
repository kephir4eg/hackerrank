cmake_minimum_required(VERSION 2.6)
project(hackerrank)

add_executable(euler14 private/collatz.cpp)
add_executable(euler02 private/euler02.cpp)
add_executable(tests private/tests.cpp)
add_executable(queens private/queens.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(.)

# No install targets
#install(TARGETS euler14 RUNTIME DESTINATION bin)
