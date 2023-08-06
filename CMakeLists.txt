cmake_minimum_required(VERSION 3.15)

project(simple-moving-average LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp src/SimpleMovingAverage.h)
