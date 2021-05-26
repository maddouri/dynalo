cmake_minimum_required(VERSION 3.0.0)

project(dynalo)

#set(CMAKE_CXX_STANDARD          11 )
#set(CMAKE_CXX_STANDARD_REQUIRED ON )
#set(CMAKE_CXX_EXTENSIONS        OFF)

option(CLEAN_BUILD "Clean build with no warnings allowed" OFF)
message(STATUS "Clean build, warnings are not allowed: " ${CLEAN_BUILD})
option(BUILD_TESTS "Build tests for ${PROJECT_NAME}: " ON)

if (${CLEAN_BUILD})
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/W4 /WX)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(-Wall -Wextra -pedantic -Werror)
    else()
        # TODO: implement flags for other compilers
        message(STATUS "CLEAN_BUILD is not supported for ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"  # <prefix>/include
)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} INTERFACE dl)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} INTERFACE kernel32)
endif()



install(
    DIRECTORY   "include/${PROJECT_NAME}"
    DESTINATION "include"
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets)

include (CMakePackageConfigHelpers)
set(CONFIG_PACKAGE_BUILD_LOCATION   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(CONFIG_PACKAGE_INSTALL_LOCATION "lib/cmake/${PROJECT_NAME}")
write_basic_package_version_file (
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 1.0.3
    COMPATIBILITY AnyNewerVersion
)
export(
    EXPORT ${PROJECT_NAME}Targets
    FILE "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Targets.cmake"
    #NAMESPACE ${PROJECT_NAME}::
)
configure_file(
    "cmake/Config.cmake"
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Config.cmake"
    @ONLY
)
install(
    EXPORT      "${PROJECT_NAME}Targets"
    FILE        "${PROJECT_NAME}Targets.cmake"
    #NAMESPACE   ${PROJECT_NAME}::
    DESTINATION "${CONFIG_PACKAGE_INSTALL_LOCATION}"
)
install(
    FILES
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Config.cmake"
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CONFIG_PACKAGE_INSTALL_LOCATION}"
)

get_directory_property(IS_EXCLUDED ${CMAKE_CURRENT_SOURCE_DIR} EXCLUDE_FROM_ALL)

if (NOT IS_EXCLUDED AND BUILD_TESTS)
    message(STATUS "Building tests for ${PROJECT_NAME}")
    enable_testing()
    add_subdirectory(test)
endif()
