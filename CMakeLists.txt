cmake_minimum_required(VERSION 3.16)
project(InvestmentGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/core)
add_subdirectory(src/interface)
add_subdirectory(src/ui)
add_subdirectory(tests)
