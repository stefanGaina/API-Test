#######################################################################################################
# Copyright (C) API-Test 2024                                                                         #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   03.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated to invoke Makefile in dummy_library.               #
#   05.06.2023  Gaina Stefan               Added lib_path rule.                                       #
#   05.06.2023  Gaina Stefan               Improved lib_path rule.                                    #
#   06.08.2023  Gaina Stefan               Updated to invoke Makefile in apitest_version.             #
#   13.01.2024  Gaina Stefan               Moved unit tests into different subdirectories.            #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export LCOV     := ../../vendor/lcov/lcov.perl
export VALGRIND := valgrind --leak-check=summary --show-leak-kinds=all

export CXXFLAGS = -fpermissive -fno-inline -g -fprofile-arcs -ftest-coverage --coverage
export LDFLAGS  = -L../../../vendor/gtest/$(LIB) -lgtest -lgtest_main -lpthread -L../../../vendor/gmock/$(LIB) -lgmock -lgmock_main

export LCOV_BRANCH_FLAG = --rc lcov_branch_coverage=1

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE)           -C apitest
	$(MAKE)           -C dummy-lib
	$(MAKE) run_tests -C apitest
	$(MAKE) run_tests -C dummy-lib
	$(MAKE) clean     -C apitest
	$(MAKE) clean     -C dummy-lib

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
