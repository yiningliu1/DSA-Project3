cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Project3)

include_directories(backend)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/Users/shelt/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(Project3
        backend/Graph.cpp
        backend/Graph.h
        backend/Hashmap.cpp
        backend/Hashmap.h
        frontend/main.cpp
        backend/Channel.h
        backend/Channel.cpp
        )


target_link_libraries(DSA_Project3 sfml-system sfml-window sfml-graphics sfml-audio)


