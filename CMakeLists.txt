cmake_minimum_required(VERSION 3.14)
project(stm32-memory-game-tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(game_tests
    tests/game_test.cpp
    Src/game.c
)

target_link_libraries(game_tests gtest gtest_main)

target_include_directories(game_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

set_source_files_properties(Src/game.c PROPERTIES LANGUAGE C)

gtest_discover_tests(game_tests)
