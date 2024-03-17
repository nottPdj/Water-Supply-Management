cmake_minimum_required(VERSION 3.26)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 main.cpp
        src/Graph.h
        src/Graph.cpp
        src/Pipe.h
        src/Pipe.cpp
        src/Reservoir.cpp
        src/City.h
        src/Station.h
        src/Station.cpp
        src/City.cpp
        src/ServicePoint.h
        src/ServicePoint.cpp
        src/Auxiliar.cpp
        src/Menu.cpp)
