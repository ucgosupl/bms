cmake_minimum_required(VERSION 3.17)

enable_language(ASM)

project(bms)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

add_subdirectory(test/unit_test/unity unity)
add_subdirectory(test/unit_test/fff fff)

add_subdirectory(test/unit_test/test test)

add_subdirectory(src)
