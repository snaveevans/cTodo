cmake_minimum_required(VERSION 3.12.2)

project(cfun)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(cfun ${SOURCES})
