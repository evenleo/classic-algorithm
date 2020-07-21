cmake_minimum_required(VERSION 3.13)
project(lru_cache_test)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_BUILD_TYPE "Debug")

add_executable(lru_cache_test lru_cache_test.cpp)