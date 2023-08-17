# Minimum CMake required
cmake_minimum_required(VERSION 3.11)

# Project
project(anti-ttd LANGUAGES CXX VERSION 1.0.0)

# Config
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(anti-ttd)

# Summary
message(STATUS "Configuration summary")
message(STATUS "Project name                 : ${PROJECT_NAME}")
message(STATUS "Project version              : ${PROJECT_VERSION}")
