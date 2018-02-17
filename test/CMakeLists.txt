cmake_minimum_required(VERSION 3.5.0)

# linux
# cmake -DCMAKE_CXX_STANDARD=11 -DCMAKE_BUILD_TYPE=Debug -H. -Bbuild-linux && cmake --build build-linux --config Debug -- -j4

# windows
# cmake -G"Visual Studio 15 2017 Win64" -DCMAKE_CXX_STANDARD=11 -DCMAKE_BUILD_TYPE=Debug -H. -Bbuild-windows && cmake --build build-windows --config Debug -- /m:4

# test
# cd build-{linux,window}
# ctest -V

project(dynalo-test)

set(CMAKE_CXX_STANDARD          11 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

add_executable(loader loader.cpp)
target_link_libraries(loader dynalo)

add_library(some SHARED some.cpp)

add_dependencies(loader some)

enable_testing()
add_test(NAME all_tests COMMAND
    "$<TARGET_FILE:loader>" "$<TARGET_FILE_DIR:some>" "some" # --log_level=all --color_output=true
)
