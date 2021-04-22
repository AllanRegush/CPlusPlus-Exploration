cmake_minimum_required(VERSION 3.5)

project(MethodOverriding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(MethodOverriding main.cpp
    person.cpp person.h employee.cpp employee.h
)
