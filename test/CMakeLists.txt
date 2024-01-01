cmake_minimum_required (VERSION 3.16)

# Setup GoogleTest
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

project(embed_test)

add_executable (${PROJECT_NAME} 
							test.cpp
                            resource.hpp
                            resource_holder.hpp
                            span.hpp
)
target_link_libraries(${PROJECT_NAME} gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${PROJECT_NAME} PUBLIC -ftime-trace)
endif()

add_compile_definitions(NMEA_FULL_PATH="${CMAKE_CURRENT_LIST_DIR}/../example/nmea.txt")
file (REMOVE_RECURSE 
                        ${CMAKE_CURRENT_LIST_DIR}/embedded_resources/
                        ${CMAKE_CURRENT_LIST_DIR}/resource.hpp
                        ${CMAKE_CURRENT_LIST_DIR}/resource_holder.hpp
                        ${CMAKE_CURRENT_LIST_DIR}/span.hpp
)
add_custom_target(embed_test_pre_build
    COMMAND $<TARGET_FILE:embed> 
                                    ${CMAKE_CURRENT_LIST_DIR}/../example
                                    -o ${CMAKE_CURRENT_LIST_DIR}
    BYPRODUCTS resource.hpp resource_holder.hpp span.hpp
)
add_dependencies(embed_test_pre_build embed)
add_dependencies(embed_test embed_test_pre_build)
 
 