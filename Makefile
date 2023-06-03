#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated with rules for unit-test.                          #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export CC = gcc

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export COVERAGE_REPORT := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory coverage_report/

INFO_FILES = $(COVERAGE_REPORT)/apitest.info \
			 $(COVERAGE_REPORT)/dummy_library.info

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE) -C apitest
	$(MAKE) -C dummy-lib
	$(MAKE) -C test

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
	$(MAKE) clean -C test

### MAKE UNIT-TESTS ###
ut: create_dir
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CREATE DIRECTORY ###
create_dir:
ifdef OS
	if not exist "$(COVERAGE_REPORT)" mkdir $(COVERAGE_REPORT)
else
	ifeq ($(shell uname), Linux)
		mkdir -p $(COVERAGE_REPORT)
	else
		$(error Platform is not supported!)
	endif
endif

### CLEAN UNIT-TESTS ###
ut-clean:
ifdef OS
	rd /s /q $(COVERAGE_REPORT)
else
	ifeq ($(shell uname), Linux)
		rm -rf $(COVERAGE_REPORT)/*
	else
		$(error Platform is not supported!)
	endif
endif
