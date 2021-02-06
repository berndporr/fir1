cmake_minimum_required(VERSION 3.1.0)

project(FIRdemo)

set (CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

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
