#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This CMake file is used to generate a dummy library with different types as parameters
# to test the API-Test functionalities.
#######################################################################################################

include_directories(
	include
	../ApiTest/include
)
file(GLOB SOURCES "src/*.c")

add_library(${DUMMY_LIBRARY} SHARED ${SOURCES})

set_target_properties(${DUMMY_LIBRARY} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
