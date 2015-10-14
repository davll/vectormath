cmake_minimum_required(VERSION 3.0)
project(vectormath)

option(BUILD_TEST "Enable testing" ON)

# ============================================
# Vectormath Library

add_library(vectormath INTERFACE)

target_compile_options(vectormath
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:Clang>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:AppleClang>:-std=c++11 -Wall>
)

target_include_directories(vectormath
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
