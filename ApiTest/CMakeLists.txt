#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This CMake file is used to generate the API-Test static library.
#######################################################################################################

find_library(READLINE_LIBRARY readline)

include_directories(
	include
	include/details
	include/internal
)
file(GLOB SOURCES "src/*.cpp")

add_library(${API_TEST_LIBRARY} STATIC ${SOURCES})

if(READLINE_LIBRARY)
	target_link_libraries(${API_TEST_LIBRARY} PRIVATE ${READLINE_LIBRARY})
else()
	message(FATAL_ERROR "Readline library not found. Please install libreadline-dev.")
endif()

set_target_properties(${API_TEST_LIBRARY} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
