cmake_minimum_required(VERSION 3.10)
project(TripleDES)

set(CMAKE_CXX_STANDARD 11)

add_executable(TripleDES main.cpp)

target_link_libraries(TripleDES cryptopp)