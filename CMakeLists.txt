cmake_minimum_required(VERSION 3.16...3.27)

project(rerun_external_cpp_proj LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

set(RERUN_CPP_URL "https://build.rerun.io/commit/359c2cd/rerun_cpp_sdk.zip" CACHE STRING "URL to the rerun_cpp zip.") # TODO: "https://github.com/rerun-io/rerun/releases/download/0.16.0/rerun_cpp_sdk.zip"
option(RERUN_FIND_PACKAGE "Whether to use find_package to find a preinstalled rerun package (instead of using FetchContent)." OFF)

if(RERUN_FIND_PACKAGE)
  find_package(rerun_sdk REQUIRED)
else()
  # Download the rerun_sdk
  include(FetchContent)
  FetchContent_Declare(rerun_sdk URL ${RERUN_CPP_URL})
  FetchContent_MakeAvailable(rerun_sdk)
endif()

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(rerun_ext_example src/main.cpp)

target_link_libraries(rerun_ext_example Eigen3::Eigen ${OpenCV_LIBS} rerun_sdk)
