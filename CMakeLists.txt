project(BangMath C CXX)
cmake_minimum_required(VERSION 3.7)
set (CMAKE_CXX_STANDARD 11)

set(BANG_MATH_INCLUDE_DIR "include")
set(BANG_MATH_INCLUDE_FULL_DIR "${BANG_MATH_INCLUDE_DIR}/BangMath")
file(GLOB BANG_MATH_HEADER_FILES "${BANG_MATH_INCLUDE_FULL_DIR}/*.h" "${BANG_MATH_INCLUDE_FULL_DIR}/*.tcc")

add_library(BangMath INTERFACE)
target_sources(BangMath INTERFACE ${BANG_MATH_HEADER_FILES})
target_include_directories(BangMath INTERFACE "${BANG_MATH_INCLUDE_DIR}/")

