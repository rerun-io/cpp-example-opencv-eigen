cmake_minimum_required(VERSION 3.16)

project(rerun_external_cpp_proj LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Arrow REQUIRED)
# find_package(rerun_sdk REQUIRED)  # this would be nice (i.e., installable rerun_sdk)

# assume rerun_sdk has been build beforehand
add_library(rerun_sdk INTERFACE)
target_include_directories(rerun_sdk INTERFACE /home/leo/code/rerun/rerun_cpp/src/)
target_link_libraries(rerun_sdk INTERFACE /home/leo/code/rerun/build/rerun_cpp/librerun_sdk.a)
target_link_libraries(rerun_sdk INTERFACE /home/leo/code/rerun/target/release/librerun_c.a)
if(ARROW_LINK_SHARED)
    target_link_libraries(rerun_sdk INTERFACE Arrow::arrow_shared)
else()
    target_link_libraries(rerun_sdk INTERFACE Arrow::arrow_static)
endif()


add_executable(rerun_ext_example src/main.cpp)

target_link_libraries(rerun_ext_example Eigen3::Eigen ${OpenCV_LIBS} rerun_sdk)
