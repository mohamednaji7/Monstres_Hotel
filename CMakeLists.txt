cmake_minimum_required(VERSION 3.17)
project(hotel)

set(CMAKE_CXX_STANDARD 14)

add_executable(hotel main.cpp Room.cpp Room.h Account.cpp Account.h)