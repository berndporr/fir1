cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
include_directories(
  ..
  )

add_executable (step step.cpp)
target_link_libraries(step fir_static)
add_test(TestStep step)

add_executable (lms lms.cpp)
target_link_libraries(lms fir_static)
add_test(TestLms lms)

