cmake_minimum_required(VERSION 3.27)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(backend)

add_executable(Project3
        backend/Graph.cpp
        backend/Graph.h
        backend/Hashmap.cpp
        backend/Hashmap.h
        frontend/main.cpp
        backend/Channel.h
        backend/Channel.cpp)
