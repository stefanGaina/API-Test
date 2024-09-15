#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 03.08.2024
# Description: This Cmake file is used to compile unit-tests for the invalid_argument.cpp.
#######################################################################################################

set(TESTED_FILE invalid_argument)
set(TEST_FILE ${TESTED_FILE}_test)

include_directories(
	../mocks
	${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/include
	${CMAKE_SOURCE_DIR}/${API_TEST_DIRECTORY}/src
)

add_executable(${TEST_FILE} src/${TEST_FILE}.cpp)

target_link_libraries(${TEST_FILE} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME test_${TESTED_FILE} COMMAND ${TEST_FILE})
set_tests_properties(test_${TESTED_FILE} PROPERTIES ENVIRONMENT "GTEST_COLOR=1")
