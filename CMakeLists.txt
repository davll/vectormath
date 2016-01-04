cmake_minimum_required(VERSION 3.0)
project(vectormath-library)

option(BUILD_TEST "Enable testing" ON)

if(BUILD_TEST)
  enable_testing()
endif()

add_subdirectory(simdmath)
add_subdirectory(vectormath)
