cmake_minimum_required(VERSION 3.0)
project(Raipaint_V2)

set(EXECUTABLE_NAME "Raipaint")

set(CMAKE_CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3")
endif ()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE SOURCE_FILES src/*)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

find_package(SFML REQUIRED graphics window system audio PATHS "D:/SFML-2.5.1-MinGW-8.1.0/install/lib/cmake/SFML")
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${EXECUTABLE_NAME} stdc++fs)