cmake_minimum_required(VERSION 3.27.9)

CompileApp(
    NAME "${PROJECT_NAME}_daemonv${PROJECT_VERSION}"
    SRC_DIR daemon
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include
    SRCS main.c
)