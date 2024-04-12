cmake_minimum_required(VERSION 3.26)
project(calc_poker_rank)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-Wall -g)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "src/*.c")
add_executable(Main 
    ${SOURCES}
    main.c
)

target_include_directories(Main PRIVATE include)