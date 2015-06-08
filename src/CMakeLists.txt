cmake_minimum_required(VERSION 2.8)

add_executable (EdisonDemo util.cpp LCD.cpp LED.cpp Knob.cpp Button.cpp main.cpp)

#include_directories(${PROJECT_SOURCE_DIR}/api)
#include_directories(/home/root/repos/libxively/src/libxively)
#include_directories(/home/root/repos/libxively/src/libxively/io/posix)

target_link_libraries (EdisonDemo pthread stdc++ m mraa upm-i2clcd upm-grove curl)
