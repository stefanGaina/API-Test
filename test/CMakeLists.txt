#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This CMake file is used to generate an example for API-Test loading a dummy library and
# testing its API.
#######################################################################################################

include_directories(
	include
	../ApiTest/include
	../dummy-lib/include
)
file(GLOB SOURCES "src/*.cpp")

add_executable(${TEST_APP_NAME} ${SOURCES})
target_compile_options(${TEST_APP_NAME} PRIVATE -DAPI_TEST_ARGUMENT_TYPE=ArgumentExtended)

target_link_libraries(${TEST_APP_NAME} PRIVATE ${API_TEST_LIBRARY})
target_link_libraries(${TEST_APP_NAME} PRIVATE ${DUMMY_LIBRARY})

set_target_properties(${TEST_APP_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
