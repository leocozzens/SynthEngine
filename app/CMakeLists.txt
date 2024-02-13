cmake_minimum_required(VERSION 3.25.1)

CompileApp(
    NAME "${PROJECT_NAME}_daemon_v${PROJECT_VERSION}"
    SRC_DIR daemon
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include
    SRCS main.c
)

CompileApp(
    NAME "${PROJECT_NAME}_standalone_v${PROJECT_VERSION}"
    SRC_DIR standalone
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include
    SRCS main.c
)