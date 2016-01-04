project(vectormath_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(vectormath_enable_test_core ON)
set(vectormath_enable_test_soa ON)

# Core Test
if (vectormath_enable_test_core)
  file(GLOB core_sources core/*.cpp)
  add_executable(vectormath_core_test ${core_sources})
  target_link_libraries(vectormath_core_test vectormath)
  target_compile_options(vectormath_core_test
    PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang>:-O2 -msse2 -mavx>
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX>
    $<0:-save-temps>
  )
  add_test(NAME vectormath_core_test
    COMMAND vectormath_core_test
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
  )
endif(vectormath_enable_test_core)

# SOA Test
if (vectormath_enable_test_soa)
  file(GLOB soa_sources soa/*.cpp)
  add_executable(vectormath_soa_test ${soa_sources})
  target_link_libraries(vectormath_soa_test vectormath)
  target_compile_options(vectormath_soa_test
    PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang>:-O2 -msse2 -mavx>
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX>
    $<0:-save-temps>
  )
  add_test(NAME vectormath_soa_test
    COMMAND vectormath_soa_test
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
  )
endif(vectormath_enable_test_soa)
