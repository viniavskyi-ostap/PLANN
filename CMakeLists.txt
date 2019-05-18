cmake_minimum_required(VERSION 3.0)
project(PLANN)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
set(header_files inc/activation.h inc/layersBuffer.h inc/trainCache.h inc/layer.h inc/loss.h
        inc/model.h inc/plann.h inc/plannMath.h inc/matrixTasks.h inc/parallelMatrix.h)
set(source_files src/activation.cpp src/layersBuffer.cpp src/trainCache.cpp src/layer.cpp
        src/model.cpp src/loss.cpp src/plannMath.cpp src/matrixTasks.cpp src/parallelMatrix.cpp)

include_directories(inc src)

add_library(PLANN ${header_files} ${source_files})

add_executable(plann_test src/main.cpp)
target_link_libraries(plann_test PLANN)
target_link_libraries(PLANN Threads::Threads)

add_executable(test_matrix src/test_matrix.cpp inc/timeMeasure.h src/matrix.cpp inc/matrix.h)
target_link_libraries(test_matrix PLANN)

add_executable(test_matrix_parallel src/test_matrix_parallel.cpp inc/timeMeasure.h src/parallelMatrix.cpp
        inc/parallelMatrix.h inc/matrixTasks.h src/matrixTasks.cpp)
target_link_libraries(test_matrix_parallel Threads::Threads)
#target_link_libraries(test_matrix_parallel PLANN)
