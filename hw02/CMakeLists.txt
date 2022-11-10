cmake_minimum_required(VERSION 3.14)

project(hw02)

# require C++20
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME runhw02)

add_library(hw02 combinatorics.cpp)
target_include_directories(hw02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${EXECUTABLE_NAME} run.cpp)
target_link_libraries(${EXECUTABLE_NAME} hw02)

# set(SOURCES combinatorics.cpp)

# set(LIBRARY_NAME hw02)
# set(EXECUTABLE_NAME runhw02)

# add_library(${LIBRARY_NAME} SHARED ${SOURCES})
# target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_compile_features(${LIBRAEY_NAME} cxx_std_20)

# add_executable(${EXECUTABLE_NAME} run.cpp)
# target_link_libraries(${EXECUTABLE_NAME} ${LIBRAEY_NAME})
