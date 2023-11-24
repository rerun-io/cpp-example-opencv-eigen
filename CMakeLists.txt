cmake_minimum_required(VERSION 3.16...3.27)

project(rerun_external_cpp_proj LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

include(FetchContent)
FetchContent_Declare(rerun_sdk URL https://build.rerun.io/commit/d5153cb/rerun_cpp_sdk.zip) # TODO: 2023-11-24. Update to latest commit.
FetchContent_MakeAvailable(rerun_sdk)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(rerun_ext_example src/main.cpp)

target_link_libraries(rerun_ext_example Eigen3::Eigen ${OpenCV_LIBS} rerun_sdk)
