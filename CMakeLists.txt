#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This CMake file is used to invoke the CMake files in the subdirectories.
#######################################################################################################

cmake_minimum_required(VERSION 3.22.1)
project(API-Test VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(API_TEST_LIBRARY apitest)
set(DUMMY_LIBRARY dummy)
set(TEST_APP_NAME apitest-test)

set(API_TEST_DIRECTORY ApiTest)
set(DUMMY_LIB_DIRECTORY dummy-lib)
set(TEST_DIRECTORY test)

file(GLOB_RECURSE FORMAT_FILES
	 "${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/src/*.cpp"
	 "${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/include/*/*.hpp"
	 "${CMAKE_SOURCE_DIR}/${DUMMY_LIB_DIRECTORY}/include/*.h"
	 "${CMAKE_SOURCE_DIR}/${DUMMY_LIB_DIRECTORY}/src/*.c"
	 "${CMAKE_SOURCE_DIR}/${TEST_DIRECTORY}/src/*.cpp")

add_custom_target(clang-format
				  COMMAND clang-format
				  -i
				  ${FORMAT_FILES})

add_custom_target(pre-build ALL
				  DEPENDS clang-format)

add_subdirectory(${API_TEST_DIRECTORY})
add_subdirectory(${DUMMY_LIB_DIRECTORY})
add_subdirectory(${TEST_DIRECTORY})
