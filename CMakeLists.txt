cmake_minimum_required(VERSION 3.0)

project(fdtd-practice-1 CXX)

file(GLOB sources *.cpp)
file(GLOB targets *.h)


find_package(OpenCV 3.0 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRECTORIES})

set(target fdtd_1d)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall" )
add_executable(${target} ${sources} ${targets})
target_link_libraries(${target} ${OpenCV_LIBRARIES} m)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

