cmake_minimum_required(VERSION 3.14)
project(Dining-philosophers.problem)

set (SRC_LIST main.cpp philosopher.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SRC_LIST})