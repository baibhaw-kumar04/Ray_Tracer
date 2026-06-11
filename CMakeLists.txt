cmake_minimum_required(VERSION 3.15)
project(inOneWeekend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(inOneWeekend src/main.cpp)

find_package(OpenMP REQUIRED)

target_link_libraries(inOneWeekend PRIVATE OpenMP::OpenMP_CXX)
