cmake_minimum_required(VERSION 3.13)

include(~/pico/pico-sdk/external/pico_sdk_import.cmake)

project(midivel C CXX ASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(midivel midivel.c)

pico_add_extra_outputs(midivel)

target_link_libraries(midivel pico_stdlib)

