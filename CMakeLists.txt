cmake_minimum_required(VERSION 3.24)
project(BCCR_Impact C)

set(CMAKE_C_STANDARD 90)

add_executable(BCCR_Impact src/test/main.c src/base/base.h src/base/base.c src/base/object.h src/base/macros.h src/test/base_test.cpp src/base/layer.c src/base/layer.h)
