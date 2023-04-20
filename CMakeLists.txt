cmake_minimum_required(VERSION 3.21)

## Disable in-source build.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source build is not allowed! Please specify a build folder.\n\tex:cmake -B build")
endif()

## Project declaration
project(pdm_recorder)

## Enable languages for project
enable_language(CXX C ASM)

## Add app
# add_subdirectory(src)

## Add library
# add_subdirectory(lib_mic_array)