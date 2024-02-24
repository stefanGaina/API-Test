#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 13.01.2024
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

export TESTED_FILE_DIR := ../../../dummy-lib/$(SRC)

all:
	$(MAKE) -C dummy_library

### RUN TESTS ###
run_tests:
	$(MAKE) run_tests -C dummy_library

### CLEAN ###
clean:
	$(MAKE) clean -C dummy_library
