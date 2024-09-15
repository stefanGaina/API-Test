#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 03.08.2024
# Description: This CMake file is used to invoke the CMake files in the subdirectories.
#######################################################################################################

find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(argument)
#add_subdirectory(invalid_argument)
#add_subdirectory(out_of_range)
