cmake_minimum_required(VERSION 3.27)
project(proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj1
        DLL.cpp
        DLL.hpp
        DNode.cpp
        DNode.hpp
        MainDLL.cpp
        Task.cpp
        Task.hpp
        TaskManager.cpp
        TaskManager.hpp)
