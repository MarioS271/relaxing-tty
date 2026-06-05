cmake_minimum_required(VERSION 4.2)
project(relaxing-tty C)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
add_executable(relaxing-tty ${SOURCES})
