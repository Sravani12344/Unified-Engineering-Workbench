cmake_minimum_required(VERSION 3.16)
project(UnifiedEngineeringWorkbench VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)
add_executable(workbench
    src/main.cpp
    src/thermal.cpp
    src/performance.cpp
    src/neural.cpp
    src/io.cpp
)
target_include_directories(workbench PRIVATE include)
target_link_libraries(workbench PRIVATE Threads::Threads)
if(MSVC)
  target_compile_options(workbench PRIVATE /W4 /O2)
else()
  target_compile_options(workbench PRIVATE -Wall -Wextra -Wpedantic -O2)
endif()
enable_testing()
add_executable(workbench_tests tests/test_main.cpp src/thermal.cpp src/neural.cpp)
target_include_directories(workbench_tests PRIVATE include)
add_test(NAME core_tests COMMAND workbench_tests)
