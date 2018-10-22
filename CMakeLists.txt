cmake_minimum_required(VERSION 3.12.2)

project(cfun)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.c")

add_executable(cfun ${SOURCES})
