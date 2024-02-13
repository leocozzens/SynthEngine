# CMake version settings
cmake_minimum_required(VERSION 3.27.9)
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.18)
    cmake_policy(SET CMP0135 NEW)
endif()
# Project data
project(DeepCore VERSION 0.1.0 LANGUAGES C)

# General build settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -O0")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# Build type detection
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Source files
set(SRC_DIR src/)

# Add compile segment function
set(INTERFACES daemon.c)
list(TRANSFORM INTERFACES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/)

set(INTERNALS player.c)
list(TRANSFORM INTERNALS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/internal/)

set(MODULES ${INTERNALS} ${INTERFACES})

# Dependencies
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake)
include(${SCRIPT_DIR}/setter.cmake)
include(${SCRIPT_DIR}/remotes.cmake)
include(${SCRIPT_DIR}/compile_tools.cmake)

set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)

set(DEPENDENCIES "")

# Set header locations
set(
    INTERNAL_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/internal/include
)
set(
    INTERFACE_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} STATIC ${MODULES})
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${INTERNAL_INCLUDES}
    PUBLIC
    ${INTERFACE_INCLUDES}
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ${DEPENDENCIES}
)

option(SPECTRAL_BUILD_TESTS "Enable tests" OFF)
if(${SPECTRAL_BUILD_TESTS})
    message(STATUS "Tests are enabled for ${PROJECT_NAME}")
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Tests are disabled for ${PROJECT_NAME}")
endif()

# option(SPECTRAL_BUILD_EXAMPLES "Build example executables" OFF)
# if(${SPECTRAL_BUILD_EXAMPLES})
#     message(STATUS "Example executables are enabled for ${PROJECT_NAME}")
#     add_subdirectory(examples)
# else()
#     message(STATUS "Example executables are disabled for ${PROJECT_NAME}")
# endif()

option(SPECTRAL_BUILD_APPS "Build executables" ON)
if(${SPECTRAL_BUILD_APPS})
    message(STATUS "Primary executables will be built for ${PROJECT_NAME}")
    add_subdirectory(app)
else()
    message(STATUS "Primary executables will not be built for ${PROJECT_NAME}")
endif()