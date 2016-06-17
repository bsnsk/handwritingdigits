cmake_minimum_required(VERSION 3.3)
project(handwritingdigits)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

set(SOURCE_FILES
        main.cpp
        mnist.cpp mnist.h
        distances.cpp distances.h
        knn.h knn_no_kdtree.h
        kdtree.h
        dataBasic.h
        classifierBasic.h
        preprocess.h
        common.h)

option(KNN "use KNN (kd-tree) classifier" ON)
if(KNN)
    add_definitions(-DKNN)
endif(KNN)


option(KNNNOKD "do not use KNN (kd-tree) classifier" OFF)
if(KNNNOKD)
    add_definitions(-DKNN_NO_KD)
endif(KNNNOKD)


add_executable(handwritingdigits ${SOURCE_FILES})
