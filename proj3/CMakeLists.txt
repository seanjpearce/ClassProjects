cmake_minimum_required(VERSION 3.28)
project(proj3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj3
        HashMap.cpp
        HashMap.hpp
        HashNode.cpp
        HashNode.hpp
        mainHash.cpp
        MakeModel.cpp
        MakeModel.hpp)
