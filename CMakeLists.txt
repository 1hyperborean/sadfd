cmake_minimum_required(VERSION 3.16)
project(redis-cpp VERSION 0.1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD_17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wall -Wextra")

# find required packages
find_package(Threads REQUIRED)

# automatically find all source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE SOURCES_RECURSIVE "src/**/*.cpp")

# combine all sources
set(ALL_SOURCES ${SOURCES} ${SOURCES_RECURSIVE})

message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "SOURCES_RECURSIVE: ${SOURCES_RECURSIVE}")
message(STATUS "ALL_SOURCES: ${ALL_SOURCES}")

# include directories for headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# main executable
add_executable(redis-cpp ${ALL_SOURCES})

# link libraries
target_link_libraries(redis-cpp Threads::Threads)

# set output directory
set_target_properties(redis-cpp PROPERTIES
    OUTPUT_NAME "redis-cpp"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)