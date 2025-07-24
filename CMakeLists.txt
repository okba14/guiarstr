cmake_minimum_required(VERSION 3.10)
project(GuiarStr VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

add_library(guiarstr STATIC src/guiarstr.c)

add_executable(guiarstr_tests tests/main.c)
target_link_libraries(guiarstr_tests guiarstr)

enable_testing()
add_test(NAME GuiarStrTests COMMAND guiarstr_tests)

