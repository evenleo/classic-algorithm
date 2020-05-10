cmake_minimum_required(VERSION 3.13)
project(con_hash_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(../rb_tree)

add_executable(con_hash_test con_hash_test.cpp md5.cpp)