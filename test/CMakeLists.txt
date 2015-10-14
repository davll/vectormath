project(vectormath-test)

file(GLOB sources src/*.cpp)

add_executable(core_test ${sources})
target_link_libraries(core_test vectormath)
target_compile_options(core_test PRIVATE
  #-save-temps
  -O2
  -msse
  -msse2
  -mavx
)
add_test(NAME vectormath-test
  COMMAND core_test
  #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
)
