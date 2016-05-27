cmake_minimum_required(VERSION 3.3)
project(handwritingdigits)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        mnist.cpp mnist.h
        knn.h
        kdtree.h
        dataBasic.h
        classifierBasic.h
        common.h)
add_executable(handwritingdigits ${SOURCE_FILES})