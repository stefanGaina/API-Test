#######################################################################################################
# Copyright (C) API-Test 2024                                                                         #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated with rules for unit-test.                          #
#   05.06.2023  Gaina Stefan               Added detect_os rule.                                      #
#   11.06.2023  Gaina Stefan               Updated ut-clean rule.                                     #
#   22.06.2023  Gaina Stefan               Fix ut-clean rule on linux.                                #
#   06.08.2023  Gaina Stefan               Added apitest_version to info files.                       #
#   03.01.2024  Gaina Stefan               Added dogygen.                                             #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export COVERAGE_REPORT := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory coverage_report/

INFO_FILES = $(COVERAGE_REPORT)/apitest.info         \
			 $(COVERAGE_REPORT)/apitest_version.info \
			 $(COVERAGE_REPORT)/dummy_library.info

### MAKE SUBDIRECTORIES ###
all: build doxygen
	$(MAKE) -C apitest
	$(MAKE) -C dummy-lib
	$(MAKE) -C test

build:
	$(MAKE) -C apitest
	$(MAKE) -C dummy-lib
	$(MAKE) -C test

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
	$(MAKE) clean -C test

### MAKE UNIT-TESTS ###
ut:
	mkdir -p $(COVERAGE_REPORT)
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CLEAN UNIT-TESTS ###
ut-clean:
	rm -rf $(COVERAGE_REPORT)/*

### MAKE DOXYGEN ###
doxygen:
	doxygen docs/doxygen.conf
