cmake_minimum_required(VERSION 3.5...4.10)
set(CMAKE_CXX_STANDARD 17)

project(Solution)
set(PROJECT ${CMAKE_PROJECT_NAME})
set(PROJECT_LIB ${PROJECT}_lib)

add_executable(${PROJECT})
include_directories(067)
add_subdirectory(067)

enable_testing()
add_subdirectory(../lib/googletest ./lib/googletest)
#add_subdirectory(tst)
