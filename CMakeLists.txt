cmake_minimum_required(VERSION 3.15)
project(LoggerCpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the loggerCppLib subdirectory
add_subdirectory(loggerCppLib)

# Add the executable
add_executable(LoggerDemo main.cpp)

# Link the library to the executable
target_link_libraries(LoggerDemo PRIVATE loggerCppLib)
# nlohmann/json is already handled by the library's CMakeLists.txt
