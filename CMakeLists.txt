cmake_minimum_required(VERSION 3.20)
project(loggerCpp VERSION 1.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Try to find nlohmann/json package first
find_package(nlohmann_json QUIET)

if(NOT nlohmann_json_FOUND)
    # If not found, fetch from GitHub
    include(FetchContent)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3  # Specify the version you want to use
    )
    FetchContent_MakeAvailable(json)
endif()

# Try to find fmt package first
find_package(fmt QUIET)

if(NOT fmt_FOUND)
    # If not found, fetch from GitHub
    include(FetchContent)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1  # Specify the version you want to use
    )
    FetchContent_MakeAvailable(fmt)
endif()

# Collect source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Collect header files
file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/loggerCpp/*.hpp"
)

# Ensure source files are present
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src directory.")
endif()

# Ensure header files are present
if(NOT HEADERS)
    message(FATAL_ERROR "No header files found in include/loggerCpp directory.")
endif()

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set compile features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Link nlohmann/json and fmt
target_link_libraries(${PROJECT_NAME} 
    nlohmann_json::nlohmann_json
    fmt::fmt
)