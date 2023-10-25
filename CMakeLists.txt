project(llist_main_project)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_compile_options( -Wall -pedantic -g )
subdirs(containers)
#subdirs(app_test)

add_executable(app_test app_test/app_test.cpp)
target_link_libraries(app_test containers)

subdirs(tests)


