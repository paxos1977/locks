cmake_minimum_required(VERSION 2.8)
Project("Locks")

include(_cmake/CompilerFlags.cmake)
include(_cmake/LibraryFunction.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/_cmake")

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(locks)
