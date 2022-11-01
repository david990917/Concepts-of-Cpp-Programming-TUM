cmake_minimum_required(VERSION 3.14)

project(hw01)

# require C++20 
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME hw01)
add_executable(${EXECUTABLE_NAME} hw01.cpp)
target_link_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_link_libraries(${EXECUTABLE_NAME} library)