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

set(API_TEST_DIRECTORY ApiTest)
set(DUMMY_LIB_DIRECTORY dummy-lib)
set(TEST_DIRECTORY test)

if(NOT BUILD_UNIT_TESTS)
	set(API_TEST_LIBRARY apitest)
	set(DUMMY_LIBRARY dummy)
	set(TEST_APP_NAME apitest-test)

	file(GLOB_RECURSE FORMAT_FILES
		 "${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/src/*.cpp"
		 "${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/include/*/*.hpp"
		 "${CMAKE_SOURCE_DIR}/${DUMMY_LIB_DIRECTORY}/include/*.h"
		 "${CMAKE_SOURCE_DIR}/${DUMMY_LIB_DIRECTORY}/src/*.c"
		 "${CMAKE_SOURCE_DIR}/${TEST_DIRECTORY}/src/*.cpp")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Werror -DNDEBUG -flto")

	add_custom_target(clang-format
					  COMMAND clang-format -i ${FORMAT_FILES})

	add_custom_target(pre-build ALL
					  DEPENDS clang-format)

	add_subdirectory(${API_TEST_DIRECTORY})
	add_subdirectory(${DUMMY_LIB_DIRECTORY})
	add_subdirectory(${TEST_DIRECTORY})
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -DUNIT_TEST -DNDEBUG -fpermissive -fno-inline -fprofile-arcs -ftest-coverage --coverage")
	set(LCOV_DIRECTORY "${CMAKE_SOURCE_DIR}/vendor/lcov/bin")

	add_custom_target(coverage
		COMMAND perl ${LCOV_DIRECTORY}/lcov.perl --capture --directory . --exclude *_test* --exclude *_mock* --exclude usr/* --rc lcov_branch_coverage=1
			--demangle-cpp --output-file coverage.info
		COMMAND perl ${LCOV_DIRECTORY}/genhtml.perl --branch-coverage --num-spaces=4 coverage.info --output-directory coverage_report --dark-mode)

	add_subdirectory(unit-tests)
endif()
