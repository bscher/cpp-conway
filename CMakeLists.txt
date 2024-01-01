cmake_minimum_required (VERSION 3.8)

project ("ConwayGameOfLifeCpp")

include_directories(./src/)
file(GLOB SOURCES "./src/*.cpp")

add_executable (app ${SOURCES})
