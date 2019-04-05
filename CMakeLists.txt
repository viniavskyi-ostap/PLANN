cmake_minimum_required(VERSION 3.13)
project(PLANN)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc src)
<<<<<<< HEAD
add_library(PLANN src/plann.cpp inc/plann.h src/matrix.cpp src/Model.cpp inc/activation.h src/activation.cpp)
=======
add_library(PLANN src/plann.cpp inc/plann.h src/matrix.cpp src/Model.cpp inc/matrix.h src/trainCache.cpp inc/trainCache.h)

add_executable(test src/main.cpp)
target_link_libraries(test PLANN)
