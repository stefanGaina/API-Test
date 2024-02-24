#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 03.06.2023
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

export LCOV     := ../../vendor/lcov/$(BIN)/lcov.perl
export VALGRIND := valgrind --leak-check=summary --show-leak-kinds=all

export CXXFLAGS := -fpermissive -fno-inline -g -fprofile-arcs -ftest-coverage --coverage
export LDFLAGS  := -L../../../vendor/gtest/$(LIB) -lgtest -lgtest_main -lpthread -L../../../vendor/gmock/$(LIB) -lgmock -lgmock_main

export LCOV_BRANCH_FLAG := --rc lcov_branch_coverage=1
export COVERAGE_REPORT  := ../coverage_report

GENHTML       = ../vendor/lcov/$(BIN)/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory $(COVERAGE_REPORT) --dark-mode

INFO_FILES = $(COVERAGE_REPORT)/apitest_internal.info \
			 $(COVERAGE_REPORT)/apitest_version.info  \
			 $(COVERAGE_REPORT)/apitest.info          \
			 $(COVERAGE_REPORT)/dummy_library.info

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE)           -C apitest
	$(MAKE)           -C dummy-lib
	$(MAKE) run_tests -C apitest
	$(MAKE) run_tests -C dummy-lib
	$(MAKE) clean     -C apitest
	$(MAKE) clean     -C dummy-lib
	mkdir -p $(COVERAGE_REPORT)
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
	rm -rf $(COVERAGE_REPORT)/*
