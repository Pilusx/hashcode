cmake_minimum_required (VERSION 2.6)
project (streaming)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
add_executable(validate tester.cc)
