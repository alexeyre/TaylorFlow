cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

project(
  TaylorFlow
  VERSION 0.0.1
  DESCRIPTION "Library for TaylorModel arithmetic and FlowPipe approximations")

file(GLOB sources src/*.cpp)

# add_library(TaylorFlow SHARED ${sources})

add_executable(TaylorFlow ${sources})

set_target_properties(TaylorFlow PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(TaylorFlow PRIVATE ./src)

include(GNUInstallDirs)

install(
  TARGETS TaylorFlow
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
