cmake_minimum_required(VERSION 3.0)
project(PLANN)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
set(header_files inc/activation.h inc/layersBuffer.h inc/matrix.h inc/trainCache.h inc/layer.h inc/loss.h
        inc/model.h inc/plann.h inc/plann_math.h inc/parallel_matrix.h inc/matrix_tasks.h inc/ThreadPool.h)
set(source_files src/activation.cpp src/layersBuffer.cpp src/matrix.cpp src/trainCache.cpp src/layer.cpp
        src/model.cpp src/loss.cpp src/plann_math.cpp src/parallel_matrix.cpp src/matrix_tasks.cpp)

include_directories(inc src)

add_library(PLANN ${header_files} ${source_files})

add_executable(plann_test src/main.cpp)
target_link_libraries(plann_test PLANN)
target_link_libraries(PLANN Threads::Threads)
