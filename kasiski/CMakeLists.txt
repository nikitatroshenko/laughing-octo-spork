cmake_minimum_required(VERSION 3.8)
project(kasiski)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        kasiski.c
        kasiski.h)

add_executable(kasiski ${SOURCE_FILES})