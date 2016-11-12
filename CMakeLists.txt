cmake_minimum_required(VERSION 3.6)
project(jnp3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES geometry.cc geometry.h)
add_executable(jnp3 ${SOURCE_FILES})