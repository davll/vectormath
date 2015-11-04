project(vectormath-test)

file(GLOB sources src/*.cpp)

if(APPLE)
  file(GLOB soa_sources soa_src/*.cpp)
  set(sources ${sources} ${soa_sources})
endif()

add_executable(core_test ${sources})
target_link_libraries(core_test vectormath)
target_compile_options(core_test PRIVATE
  $<$<CXX_COMPILER_ID:AppleClang>:-save-temps -O2 -msse2 -mavx>
  $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX /WX>
)
add_test(NAME vectormath-test
  COMMAND core_test
  #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
)
