cmake_minimum_required(VERSION 3.27)

project(cmake_task)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(menu_task)
add_subdirectory(sorting_task)
