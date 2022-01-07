cmake_minimum_required (VERSION 3.16)

project(embed)

add_executable (${PROJECT_NAME} 
							main.cpp
							embed.hpp
							resource.hpp
							saver.hpp 
							span.hpp
)
install(TARGETS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${PROJECT_NAME} PUBLIC -ftime-trace)
endif()
