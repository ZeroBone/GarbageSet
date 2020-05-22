cmake_minimum_required(VERSION 3.14)
project(garbageset C)

set(CMAKE_C_STANDARD 99)

add_executable(garbageset src/garbageset.c src/garbageset.h main.c)