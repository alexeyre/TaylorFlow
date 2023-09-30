cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(
  TaylorFlow
  VERSION 0.0.1
  DESCRIPTION "Library for TaylorModel arithmetic and FlowPipe approximations")

file(GLOB sources src/*.cpp)

# add_library(TaylorFlow SHARED ${sources})

add_library(TaylorFlow ${sources})

set_target_properties(TaylorFlow PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(TaylorFlow PRIVATE ./src)

include(GNUInstallDirs)

install(
  TARGETS TaylorFlow
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CMAKE_CXX_STANDARD 20)
set_property(TARGET TaylorFlow PROPERTY CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

# Catch2
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
# find_package(Catch2 3 REQUIRED)
file(GLOB test_sources tests/*.cpp)
add_executable(tests ${test_sources})
target_include_directories(tests PRIVATE ./src /opt/homebrew/include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE TaylorFlow)

include(CTest)
include(Catch)
catch_discover_tests(tests)
