cmake_minimum_required(VERSION 3.1.0)

project(fir VERSION 1.5.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

include(GNUInstallDirs)
add_subdirectory(demo)

cmake_policy(SET CMP0048 NEW) # set VERSION in project()
cmake_policy(SET CMP0042 NEW) # enable MACOSX_RPATH by default


set(LIBSRC
  Fir1.cpp
  Fir1fixed.cpp
)

set(LIBINCLUDE
  Fir1fixed.h
  Fir1.h
  )

if (UNIX)
  add_library(fir
    SHARED
    ${LIBSRC}
    )
  
  set_target_properties(fir PROPERTIES
    SOVERSION 1
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "${LIBINCLUDE}")
  
  install(TARGETS fir EXPORT fir-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  
  configure_file(fir.pc.in fir.pc @ONLY)
  
endif ()

add_library(fir_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(fir_static PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "${LIBINCLUDE}")

install(TARGETS fir_static EXPORT fir-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fir)

install(EXPORT fir-targets
  DESTINATION lib/cmake/fir
  FILE fir-config.cmake
)
