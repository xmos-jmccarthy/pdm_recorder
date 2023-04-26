cmake_minimum_required(VERSION 3.21)

## Disable in-source build.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source build is not allowed! Please specify a build folder.\n\tex:cmake -B build")
endif()

## Project declaration
project(pdm_recorder)

## Enable languages for project
enable_language(CXX C ASM)

#**********************
# Flags
#**********************
set(APP_COMPILER_FLAGS
    -Os
    -g
    -report
    -fxscope
    -mcmodel=large
    -Wno-xcore-fptrgroup
    ${CMAKE_CURRENT_LIST_DIR}/src/config.xscope
)
set(APP_COMPILE_DEFINITIONS
)

set(APP_LINK_OPTIONS
    -report
    ${CMAKE_CURRENT_LIST_DIR}/src/config.xscope
)

add_executable(xk_voice_l71_pdm_recorder)
target_sources(xk_voice_l71_pdm_recorder
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/main.xc
)
target_include_directories(xk_voice_l71_pdm_recorder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(xk_voice_l71_pdm_recorder
    PUBLIC
)
target_compile_options(xk_voice_l71_pdm_recorder
    PUBLIC
        ${APP_COMPILER_FLAGS}
        ${CMAKE_CURRENT_LIST_DIR}/src/XK_VOICE_L71.xn
)
target_link_options(xk_voice_l71_pdm_recorder
    PUBLIC
        ${APP_LINK_OPTIONS}
        ${CMAKE_CURRENT_LIST_DIR}/src/XK_VOICE_L71.xn
)
target_compile_definitions(xk_voice_l71_pdm_recorder
    PUBLIC
        ${APP_COMPILE_DEFINITIONS}
)

