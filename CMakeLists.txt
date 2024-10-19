cmake_minimum_required(VERSION 3.14)
project(SHSML VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

# Add options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# Fetch Google Benchmark
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.0
)
FetchContent_MakeAvailable(benchmark)

if(BUILD_TESTS)
    enable_testing()
    
    # Find all test source files
    file(GLOB TEST_SOURCES tests/unit_test/*.cpp)
    
    # Create test executable
    add_executable(unit_tests ${TEST_SOURCES})
    
    # Link with Google Test
    target_link_libraries(unit_tests
        PRIVATE
        gtest
        gtest_main
    )
    
    # Add tests to CTest
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

# Benchmarks
if(BUILD_BENCHMARKS)
    # Find all benchmark source files
    file(GLOB BENCH_SOURCES "tests/benchmark/*.cpp")
    
    # Create benchmark executable
    add_executable(benchmarks ${BENCH_SOURCES})
    
    # Link with Google Benchmark
    target_link_libraries(benchmarks
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
    )
endif()

# Optional: Add custom targets for convenience
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS unit_tests
)

add_custom_target(run_benchmarks
    COMMAND benchmarks
    DEPENDS benchmarks
)

add_executable(main test.cpp)
