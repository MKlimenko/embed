cmake_minimum_required (VERSION 3.16)

project (embed_root)

#find_package(benchmark CONFIG)

set (CMAKE_VS_JUST_MY_CODE_DEBUGGING 1)

enable_testing()
add_subdirectory ("src")
add_subdirectory("test")
add_dependencies(embed_test embed)

#if (benchmark_FOUND)
#	add_subdirectory ("benchmark")
#	add_dependencies(ugsdr_benchmark rtklib)
#endif()
