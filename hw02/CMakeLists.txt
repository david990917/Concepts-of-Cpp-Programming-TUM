cmake_minimum_required(VERSION 3.14)

project(hw02)

# require C++20
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME runhw02)

add_library(hw02 combinatorics.cpp)
include_directories($ { CMAKE CURRENT SOURCE DIR })

add_executable(${EXECUTABLE_NAME} run.cpp)
target_link_libraries(${EXECUTABLE_NAME} hw02)