cmake_minimum_required(VERSION 3.31)
project(cache_false_sharing)

set(CMAKE_CXX_STANDARD 20)



include_directories(include)

add_executable(cache_false_sharing src/main.cpp)
