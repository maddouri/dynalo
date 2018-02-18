cmake_minimum_required(VERSION 3.0.0)

project(dynalo-test)

set(CMAKE_CXX_STANDARD          11 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

add_executable(loader loader.cpp)
target_link_libraries(loader dynalo)

add_library(shared SHARED shared.cpp)

add_dependencies(loader shared)

enable_testing()
add_test(NAME all_tests COMMAND
    "$<TARGET_FILE:loader>" "$<TARGET_FILE_DIR:shared>" "shared"
)
