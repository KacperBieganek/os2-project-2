cmake_minimum_required(VERSION 3.5)

set(APP_NAME Tetris)
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SRC)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(Threads REQUIRED)

add_executable(${APP_NAME} ${SRC})

target_link_libraries(${APP_NAME} Threads::Threads ${CURSES_LIBRARIES})

