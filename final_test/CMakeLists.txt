cmake_minimum_required(VERSION 3.21)
project(final_test)

set(CMAKE_CXX_STANDARD 14)

set(Headers AirQuality.h Date.h Time.h)

add_executable(AirQualityTest AirQualityTest.cpp Time.cpp Date.cpp AirQuality.cpp)
add_executable(main main.cpp Time.cpp Date.cpp AirQuality.cpp)
add_executable(dateTest dateTest.cpp Date.cpp Time.cpp AirQuality.cpp)
add_executable(timeTest timeTest.cpp Date.cpp Time.cpp AirQuality.cpp)