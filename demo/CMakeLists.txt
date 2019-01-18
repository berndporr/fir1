cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)

add_executable (firdemo firdemo.cpp)
target_link_libraries(firdemo fir_static)
target_include_directories(firdemo PRIVATE ..)

add_executable (coeffarraydemo coeffarraydemo.cpp)
target_link_libraries(coeffarraydemo fir_static)
target_include_directories(coeffarraydemo PRIVATE ..)

add_executable (fixeddemo fixeddemo.cpp)
target_link_libraries(fixeddemo fir_static)
target_include_directories(fixeddemo PRIVATE ..)

add_executable (lmsdemo lmsdemo.cpp)
target_link_libraries(lmsdemo fir_static)
target_include_directories(lmsdemo PRIVATE ..)
