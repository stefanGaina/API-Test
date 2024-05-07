#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 13.01.2024
# Description: This Makefile is used to compile unit-test for apitest_internal.c, run them and
# generate coverage report.
#######################################################################################################

CXXFLAGS += `pkg-config --cflags glib-2.0`
CFLAGS	 := `pkg-config --cflags glib-2.0` -fno-inline -g -fprofile-arcs -ftest-coverage --coverage
LDFLAGS  += `pkg-config --libs glib-2.0`

INCLUDES := -I../../../vendor/gtest/include \
			-I../../../apitest/include

TEST_FILE_NAME	 := apitest_internal_test
TESTED_FILE_NAME := apitest_internal
EXECUTABLE		 := apitest_internal_ut

all: | create_dir $(EXECUTABLE)

### CREATE DIRECTORY ###
create_dir:
	mkdir -p $(OBJ)

### BINARIES ###
$(EXECUTABLE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC)/$(TEST_FILE_NAME).cpp -o $(OBJ)/$(TEST_FILE_NAME).o
	$(CC) $(CFLAGS) $(INCLUDES) -c $(TESTED_FILE_DIR)/$(TESTED_FILE_NAME).c -o $(OBJ)/$(TESTED_FILE_NAME).o
	$(CXX) $(OBJ)/$(TEST_FILE_NAME).o $(OBJ)/$(TESTED_FILE_NAME).o $(CXXFLAGS) -o $(OBJ)/$@ $(LDFLAGS)

### RUN TESTS ###
run_tests: execute_tests copy_results

### EXECUTE TESTS ###
execute_tests:
	$(VALGRIND) --log-file="../../$(COVERAGE_REPORT)/memcheck_$(TESTED_FILE_NAME).txt" $(OBJ)/$(EXECUTABLE)

### COPY RESULTS ###
copy_results:
	cp $(OBJ)/$(TESTED_FILE_NAME).gcda $(TESTED_FILE_DIR)
	cp $(OBJ)/$(TESTED_FILE_NAME).gcno $(TESTED_FILE_DIR)
	cd $(TESTED_FILE_DIR) && gcov -b $(TESTED_FILE_NAME).c
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --capture $(LCOV_BRANCH_FLAG) --directory . --no-external --output-file $(TESTED_FILE_NAME)_all.info
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --extract $(TESTED_FILE_NAME)_all.info "*$(TESTED_FILE_NAME).c" $(LCOV_BRANCH_FLAG) --output-file $(TESTED_FILE_NAME).info
	cp $(TESTED_FILE_DIR)/$(TESTED_FILE_NAME).info ../../$(COVERAGE_REPORT)/$(TESTED_FILE_NAME).info

### CLEAN ###
clean:
	rm -rf $(OBJ)
	rm -rf $(TESTED_FILE_DIR)/*.info
	rm -rf $(TESTED_FILE_DIR)/*.gcov
	rm -rf $(TESTED_FILE_DIR)/*.gcda
	rm -rf $(TESTED_FILE_DIR)/*.gcno
