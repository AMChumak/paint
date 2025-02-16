cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME paint)
project(paint)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/anton/Qt/6.8.1/gcc_64/lib/cmake")


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Widgets)
