project(simdmath)

add_library(simdmath INTERFACE)

target_include_directories(simdmath
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(BUILD_TEST)
  add_subdirectory(test)
endif()
