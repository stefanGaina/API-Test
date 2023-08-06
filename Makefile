#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated with rules for unit-test.                          #
#   05.06.2023  Gaina Stefan               Added detect_os rule.                                      #
#   11.06.2023  Gaina Stefan               Updated ut-clean rule.                                     #
#   22.06.2023  Gaina Stefan               Fix ut-clean rule on linux.                                #
#   06.08.2023  Gaina Stefan               Added apitest_version to info files.                       #
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

INFO_FILES = $(COVERAGE_REPORT)/apitest.info         \
			 $(COVERAGE_REPORT)/apitest_version.info \
			 $(COVERAGE_REPORT)/dummy_library.info

### MAKE SUBDIRECTORIES ###
all: detect_os
	$(MAKE) -C apitest
	$(MAKE) -C dummy-lib
	$(MAKE) -C test

### CLEAN SUBDIRECTORIES ###
clean: detect_os
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
	$(MAKE) clean -C test

### MAKE UNIT-TESTS ###
ut: detect_os create_dir
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CREATE DIRECTORY ###
create_dir:
ifeq (Windows_NT, $(OS))
	if not exist "$(COVERAGE_REPORT)" mkdir $(COVERAGE_REPORT)
endif
ifeq (Linux, $(shell uname))
	mkdir -p $(COVERAGE_REPORT)
endif

### CLEAN UNIT-TESTS ###
ut-clean: detect_os
ifeq (Windows_NT, $(OS))
	$(RM) $(COVERAGE_REPORT)\*
	$(RM) $(COVERAGE_REPORT)\apitest\src\*
	$(RM) $(COVERAGE_REPORT)\dummy-lib\src\*
	rd /s /q $(COVERAGE_REPORT)\apitest
	rd /s /q $(COVERAGE_REPORT)\dummy-lib
endif
ifeq (Linux, $(shell uname))
	$(RM) $(COVERAGE_REPORT)/*
endif

### DETECT OPERATING SYSTEM ###
detect_os:
ifeq (Windows_NT, $(OS))
export OS_DIR := windows
export LIB_EXTENSION := dll
export RM := del /f /q
else ifeq (Linux, $(shell uname))
export OS_DIR := linux
export LIB_EXTENSION := so
export RM := rm -rf
else
$(error Platform is not supported)
endif
