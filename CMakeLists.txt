# CMakeList.txt : CMake project for Trie Spell Checker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)

include(FetchContent)

project ("Trie Spell Checker")


# Add source to this project's executable.
add_executable (CMakeTarget "Trie Spell Checker.cpp" "Trie Spell Checker.h" )


# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG main) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

add_executable(g_benchmark "main.cpp")
target_link_libraries(g_benchmark benchmark::benchmark)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
