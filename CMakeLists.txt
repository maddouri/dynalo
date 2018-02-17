cmake_minimum_required(VERSION 3.5.0)

# # hunter gate https://github.com/hunter-packages/gate
# if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/HunterGate.cmake")
#     file(DOWNLOAD
#         "https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake"
#         "${CMAKE_CURRENT_LIST_DIR}/HunterGate.cmake"
#     )
# endif()
# include("${CMAKE_CURRENT_LIST_DIR}/HunterGate.cmake")
# # hunter https://github.com/ruslo/hunter/releases
# HunterGate(
#     URL  "https://github.com/ruslo/hunter/archive/v0.20.9.tar.gz"
#     SHA1 "8f7cf6d719d05c49224a4ebeba90c6bb90b90f4a"
# )


project(dynalo)

#set(CMAKE_CXX_STANDARD          11 )
#set(CMAKE_CXX_STANDARD_REQUIRED ON )
#set(CMAKE_CXX_EXTENSIONS        OFF)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"  # <prefix>/include
)

#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "$<INSTALL_INTERFACE:include>")
if (UNIX)
    target_link_libraries(${PROJECT_NAME} INTERFACE dl)
    #set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES dl)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} INTERFACE kernel32)
    #set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES kernel32)
endif()



install(
    DIRECTORY   "include/${PROJECT_NAME}"
    DESTINATION "include"
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets)

include (CMakePackageConfigHelpers)
write_basic_package_version_file (
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 0.9.0
    COMPATIBILITY AnyNewerVersion
)
export(
    EXPORT ${PROJECT_NAME}Targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake"
    #NAMESPACE ${PROJECT_NAME}::
)
configure_file(
    "cmake/Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    #COPYONLY
    @ONLY
)
set(ConfigPackageLocation cmake/${PROJECT_NAME})
install(
    EXPORT      ${PROJECT_NAME}Targets
    FILE        ${PROJECT_NAME}Targets.cmake
    #NAMESPACE   ${PROJECT_NAME}::
    DESTINATION ${ConfigPackageLocation}
)
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation}
)

add_subdirectory(test)
