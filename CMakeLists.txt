cmake_minimum_required(VERSION 2.6)
project(stat)

add_executable(stat main.cpp)

install(TARGETS stat RUNTIME DESTINATION bin)
