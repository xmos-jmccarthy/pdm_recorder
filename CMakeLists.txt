cmake_minimum_required(VERSION 3.21)

## Disable in-source build.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source build is not allowed! Please specify a build folder.\n\tex:cmake -B build")
endif()

## Project declaration
project(pdm_recorder)

## Enable languages for project
enable_language(CXX C ASM)

## Add library
add_subdirectory(lib_mic_array)
add_subdirectory(lib_xcore_math)

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
    MIC_ARRAY_CONFIG_MCLK_FREQ=24576000
    MIC_ARRAY_CONFIG_PDM_FREQ=3072000
    MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME=240
    MIC_ARRAY_CONFIG_MIC_COUNT=2
    MIC_ARRAY_CONFIG_CLOCK_BLOCK_A=XS1_CLKBLK_1
    MIC_ARRAY_CONFIG_CLOCK_BLOCK_B=XS1_CLKBLK_2
    MIC_ARRAY_CONFIG_PORT_MCLK=PORT_MCLK_IN_OUT
    MIC_ARRAY_CONFIG_PORT_PDM_CLK=PORT_PDM_CLK
    MIC_ARRAY_CONFIG_PORT_PDM_DATA=PORT_PDM_DATA
)
set(APP_LINK_OPTIONS
    -report
    ${CMAKE_CURRENT_LIST_DIR}/src/config.xscope
)

add_executable(xk_voice_l71_pdm_recorder)
target_sources(xk_voice_l71_pdm_recorder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)
target_include_directories(xk_voice_l71_pdm_recorder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(xk_voice_l71_pdm_recorder
    PUBLIC
        lib_mic_array
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

