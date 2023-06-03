#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   03.06.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export CXX   = g++
export LCOV := ../../vendor/lcov/lcov.perl

export CXXFLAGS = -fpermissive
export CFLAGS   = -fpermissive -fno-inline -g -fprofile-arcs -ftest-coverage --coverage
export LDFLAGS  = -L../../vendor/googletest/lib/ -lgtest -lgtest_main -lpthread

export LCOV_BRANCH_FLAG = --rc lcov_branch_coverage=1

all:
	$(MAKE) -C apitest

### RUN TESTS ###
run_tests:
	$(MAKE) run_tests -C apitest

### CLEAN ###
clean:
	$(MAKE) clean -C apitest
