cmake_minimum_required(VERSION 3.20)
project(loggerCppLib VERSION 1.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3  # Specify the version you want to use
)
FetchContent_MakeAvailable(json)

# Collect source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "include/*.hpp"
    "utility/*.hpp"
)

# Ensure at least one source file is present
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found. Please check your directory structure.")
endif()

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/utility
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set compile features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Link nlohmann/json
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)