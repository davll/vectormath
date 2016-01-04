project(vectormath)

add_library(vectormath INTERFACE)

target_include_directories(vectormath
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(vectormath
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:Clang>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:AppleClang>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:MSVC>:/W1>
)

target_link_libraries(vectormath
  INTERFACE
  simdmath
)

if(BUILD_TEST)
  add_subdirectory(test)
endif()
