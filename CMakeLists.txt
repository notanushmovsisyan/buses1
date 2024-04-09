cmake_minimum_required(VERSION 3.0)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(buses1 ${SOURCES})