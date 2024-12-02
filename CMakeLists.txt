cmake_minimum_required(VERSION 3.24)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3
        backend/Graph.cpp
        backend/Graph.h
        frontend/main.cpp
        backend/Channel.h
        backend/Channel.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML) # should be link to your SFML directory
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(Project3 sfml-system sfml-window sfml-graphics sfml-audio)