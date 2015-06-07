cmake_minimum_required(VERSION 2.8)

add_executable (EdisonDemo LCD.cpp LED.cpp Knob.cpp main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/api)

target_link_libraries (EdisonDemo mraa stdc++ m upm-i2clcd upm-grove)
