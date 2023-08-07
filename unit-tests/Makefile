#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   03.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated to invoke Makefile in dummy_library.               #
#   05.06.2023  Gaina Stefan               Added lib_path rule.                                       #
#   05.06.2023  Gaina Stefan               Improved lib_path rule.                                    #
#   06.08.2023  Gaina Stefan               Updated to invoke Makefile in apitest_version.             #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export CXX   = g++
export LCOV := ../../vendor/lcov/lcov.perl

export CXXFLAGS = -fpermissive
export CFLAGS   = -fpermissive -fno-inline -g -fprofile-arcs -ftest-coverage --coverage

export LCOV_BRANCH_FLAG = --rc lcov_branch_coverage=1

all: lib_path
	$(MAKE) -C apitest
	$(MAKE) -C apitest_version
	$(MAKE) -C dummy_library

### LIBRARY PATH ###
lib_path:
export LDFLAGS  = -L../../vendor/googletest/$(LIB)/$(OS_DIR)/ -lgtest -lgtest_main -lpthread

### RUN TESTS ###
run_tests:
	$(MAKE) run_tests -C apitest
	$(MAKE) run_tests -C apitest_version
	$(MAKE) run_tests -C dummy_library

### CLEAN ###
clean:
	$(MAKE) clean -C apitest
	$(MAKE) clean -C apitest_version
	$(MAKE) clean -C dummy_library
