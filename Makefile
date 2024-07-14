#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This Makefile is used to abstract some common commands over CMake.
#######################################################################################################

BUILD_DIRECTORY := build
CMAKE_TIME		:= cmake -E time

all:
	$(CMAKE_TIME) $(MAKE) -C $(BUILD_DIRECTORY)

cmake:
	mkdir -p $(BUILD_DIRECTORY)
	$(CMAKE_TIME) cmake -S . -B $(BUILD_DIRECTORY)
.PHONY: cmake

clean:
	$(CMAKE_TIME) $(MAKE) clean -C $(BUILD_DIRECTORY)
.PHONY: clean

format:
	$(CMAKE_TIME) $(MAKE) clang-format -C $(BUILD_DIRECTORY)
.PHONY: format
