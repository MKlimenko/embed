cmake_minimum_required (VERSION 3.16)

project(embed_benchmark)

add_executable (${PROJECT_NAME} 
							benchmark.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${PROJECT_NAME} PUBLIC -ftime-trace)
endif()

add_custom_target(embed_benchmark_pre_build
    COMMAND $<TARGET_FILE:embed> 
                                    ${CMAKE_CURRENT_LIST_DIR}/../benchmark_data/
                                    -o ${CMAKE_CURRENT_LIST_DIR}
)
add_dependencies(embed_benchmark_pre_build embed)
add_dependencies(embed_benchmark embed_benchmark_pre_build)
 
 