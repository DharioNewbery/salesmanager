cmake_minimum_required(VERSION 3.10)
project(SalesManager)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Discover all mod headers
file(GLOB MOD_HEADERS "modules/*.h" "modules/*.hpp")

# 2. Define the main source files
# Add all your .cpp files here (e.g., SalesManager.cpp if you have one)
set(SOURCES 
    src/main.cpp 
    # SalesManager.cpp 
)

# 3. Create the executable
add_executable(salesmanager ${SOURCES})

# 4. Handle the "Auto-Include" logic
# This is the CMake way of doing -include for every mod found
foreach(header ${MOD_HEADERS})
    target_compile_options(salesmanager PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-include${header}>")
endforeach()

# 5. Include the root directory so the compiler can find Sale.h, Vector.h, etc.
target_include_directories(salesmanager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})