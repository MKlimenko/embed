cmake_minimum_required (VERSION 3.16)

project (embed_root)

set (CMAKE_VS_JUST_MY_CODE_DEBUGGING 1)

enable_testing()
add_subdirectory ("src")
add_subdirectory("test")
add_subdirectory("benchmark")
add_dependencies(embed_test embed)
add_dependencies(embed_benchmark embed)
