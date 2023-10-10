project(llist)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

include_directories($CMAKE_CURRENT_SOURCE_DIR)

subdirs(llist)
subdirs(tests)


