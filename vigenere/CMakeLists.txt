cmake_minimum_required(VERSION 3.5)
project(dss_vigenere)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c vigenere.c)
add_executable(dss_vigenere ${SOURCE_FILES})
