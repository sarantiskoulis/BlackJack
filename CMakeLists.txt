cmake_minimum_required(VERSION 3.26)
project(BlackJack)

set(CMAKE_CXX_STANDARD 20)

add_executable(BlackJack main.cpp
        misc.h
        misc.cpp)
