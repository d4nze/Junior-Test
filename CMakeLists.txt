cmake_minimum_required(VERSION 3.10)
project(JuniorTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "Source/**.cpp" "Source/**.hpp")

add_executable(JuniorTest ${SOURCES})

add_custom_command(TARGET JuniorTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Resources"
    $<TARGET_FILE_DIR:JuniorTest>/)
