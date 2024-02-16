# CMake version settings
cmake_minimum_required(VERSION 3.25.1)
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.18)
    cmake_policy(SET CMP0135 NEW)
endif()
# Project data
project(SynthEngine VERSION 0.1.0 LANGUAGES C)

# User options
option(DC_BUILD_TESTS "Enable tests" OFF)
option(DC_BUILD_EXAMPLES "Build example executables" OFF)
option(DC_BUILD_APPS "Build executables" ON)

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
set(INTERFACES daemon.c fmt.c player.c result.c stream_info.c)
list(TRANSFORM INTERFACES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/)

set(INTERNALS endint.c fio.c serializer.c)
list(TRANSFORM INTERNALS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/internal/)

set(MODULES ${INTERNALS} ${INTERFACES})

# Dependencies
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake)
include(${SCRIPT_DIR}/setter.cmake)
include(${SCRIPT_DIR}/remotes.cmake)
include(${SCRIPT_DIR}/compile_tools.cmake)

set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(DISABLES PA_BUILD_SHARED_LIBS)
DisableSettings("${DISABLES}")

set(PA_VERSION 19.7.0)
GetRemoteURL(
    NAME        portaudio
    VERSION     ${PA_VERSION}
    URL         https://github.com/PortAudio/portaudio/archive/refs/tags/v${PA_VERSION}.zip
    PARENT_DIR  ${LIB_DIR}
)

set(DEPENDENCIES portaudio_static)

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

if(${DC_BUILD_TESTS})
    message(STATUS "Tests are enabled for ${PROJECT_NAME}")
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Tests are disabled for ${PROJECT_NAME}")
endif()

if(${DC_BUILD_EXAMPLES})
    message(STATUS "Example executables are enabled for ${PROJECT_NAME}")
    add_subdirectory(examples)
else()
    message(STATUS "Example executables are disabled for ${PROJECT_NAME}")
endif()

if(${DC_BUILD_APPS})
    message(STATUS "Primary executables will be built for ${PROJECT_NAME}")
    add_subdirectory(app)
else()
    message(STATUS "Primary executables will not be built for ${PROJECT_NAME}")
endif()