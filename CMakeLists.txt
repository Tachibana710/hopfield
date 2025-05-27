cmake_minimum_required(VERSION 3.10)

# Project name
project(hopfield)

# Include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

find_package(nlohmann_json 3.2.0 REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link nlohmann/json to your project
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)