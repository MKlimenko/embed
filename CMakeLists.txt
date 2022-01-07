cmake_minimum_required (VERSION 3.16)

project (embed_root)

set (CMAKE_VS_JUST_MY_CODE_DEBUGGING 1)

add_subdirectory ("src")
if(NOT BYPASS_TESTS)
	enable_testing()
	add_subdirectory("test")
	add_dependencies(embed_test embed)
endif()

add_subdirectory("benchmark")
add_dependencies(embed_benchmark embed)
