cmake_minimum_required(VERSION 3.10)
project(M_Trivia)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get all cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Create executable with all source files
add_executable(main ${SOURCES})

# Link Windows socket library if on Windows
if (WIN32)
    target_link_libraries(main PRIVATE ws2_32)
endif()

