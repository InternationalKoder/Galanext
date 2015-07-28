cmake_minimum_required(VERSION 2.6)

project(Galanext)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set version information in a config.h file
set(Galanext_VERSION_MAJOR 0)
set(Galanext_VERSION_MINOR "\"1-SNAPSHOT\"")
configure_file(
    "include/config.hpp.in"
    "include/config.hpp"
    )
include_directories("${PROJECT_BINARY_DIR}")

# Project settings

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

file(
    GLOB_RECURSE
    source_files
    src/*
)

file(
    GLOB_RECURSE
    include_files
    include/*
)

set(EXECUTABLE_NAME "Galanext")

add_executable(
    ${EXECUTABLE_NAME}
    ${source_files}
    ${include_files}
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
