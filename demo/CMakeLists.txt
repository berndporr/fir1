cmake_minimum_required(VERSION 3.5)

add_executable (firdemo firdemo.cpp)
target_link_libraries(firdemo fir_static)
target_include_directories(firdemo PRIVATE ..)

add_executable (fixeddemo fixeddemo.cpp)
target_link_libraries(fixeddemo fir_static)
target_include_directories(fixeddemo PRIVATE ..)
