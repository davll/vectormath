project(simdmath_test)

file(GLOB sources src/*.cpp)

add_executable(simdmath_test ${sources})

target_include_directories(simdmath_test
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(simdmath_test
  PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:Clang>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:AppleClang>:-std=c++11 -Wall>
  $<$<CXX_COMPILER_ID:MSVC>:/WX>
)

target_link_libraries(simdmath_test
  PRIVATE
  simdmath
)

add_test(NAME simdmath_test COMMAND simdmath_test)
