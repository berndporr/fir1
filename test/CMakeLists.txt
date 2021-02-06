cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
include_directories(
  ..
  )

if (MSVC)
  add_compile_options(/W4 -D_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wconversion -Wextra -pedantic)
endif()

add_executable (impstep impstep.cpp)
target_link_libraries(impstep fir_static)
add_test(TestImpulseStep impstep)

add_executable (fixed fixed.cpp)
target_link_libraries(fixed fir_static)
add_test(TestFixed fixed)

add_executable (lms lms.cpp)
target_link_libraries(lms fir_static)
add_test(TestLms lms)

add_executable (coeffread coeffread.cpp)
target_link_libraries(coeffread fir_static)
add_test(
  NAME TestReadFile
  COMMAND coeffread
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
