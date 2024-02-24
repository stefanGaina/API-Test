#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 13.01.2024
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

export TESTED_FILE_DIR := ../../../apitest/$(SRC)

all:
	$(MAKE) -C apitest
	$(MAKE) -C apitest_internal
	$(MAKE) -C apitest_version

### RUN TESTS ###
run_tests:
	$(MAKE) run_tests -C apitest
	$(MAKE) run_tests -C apitest_internal
	$(MAKE) run_tests -C apitest_version

### CLEAN ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C apitest_internal
	$(MAKE) clean -C apitest_version
