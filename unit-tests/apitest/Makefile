#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   03.06.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to compile unit-test for apitest.c, run them and generate        #
# coverage report.                                                                                    #
#######################################################################################################

INCLUDES = -I../../vendor/googletest/include/ \
		   -I../../apitest/include/

TEST_FILE_NAME   := apitest_test
TESTED_FILE_NAME := apitest
TESTED_FILE_DIR  := ../../apitest/src/
EXECUTABLE       := apitest-ut.exe

all: | create_dir $(EXECUTABLE)

### CREATE DIRECTORY ###
create_dir:
ifdef OS
	if not exist "$(OBJ)" mkdir $(OBJ)
else
	ifeq ($(shell uname), Linux)
		mkdir -p $(OBJ)
	else
		$(error Platform is not supported!)
	endif
endif

### BINARIES ###
$(EXECUTABLE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_FILE_NAME).cpp -o $(OBJ)/$(TEST_FILE_NAME).o
	$(CXX) $(CFLAGS) $(INCLUDES) -c $(TESTED_FILE_DIR)$(TESTED_FILE_NAME).c -o $(OBJ)/$(TESTED_FILE_NAME).o
	$(CXX) $(OBJ)/$(TEST_FILE_NAME).o $(OBJ)/$(TESTED_FILE_NAME).o $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -o $(OBJ)/$@

### RUN TESTS ###
run_tests: execute_tests copy_results clean

### EXECUTE TESTS ###
execute_tests:
	"$(OBJ)/$(EXECUTABLE)"

### COPY RESULTS ###
copy_results:
ifdef OS
	copy $(OBJ)\$(TESTED_FILE_NAME).gcda ..\..\apitest\src
	copy $(OBJ)\$(TESTED_FILE_NAME).gcno ..\..\apitest\src
else
	ifeq ($(shell uname), Linux)
		cp $(OBJ)\$(TESTED_FILE_NAME).gcda ../../apitest/src/
		cp $(OBJ)\$(TESTED_FILE_NAME).gcno ../../apitest/src/
	else
		$(error Platform is not supported!)
	endif
endif
	cd $(TESTED_FILE_DIR) && gcov -b $(TESTED_FILE_NAME).c
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --capture $(LCOV_BRANCH_FLAG) --directory . --output-file $(TESTED_FILE_NAME)_all.info
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --extract $(TESTED_FILE_NAME)_all.info "*.c" $(LCOV_BRANCH_FLAG) --output-file $(TESTED_FILE_NAME).info
ifdef OS
	copy ..\..\apitest\src\$(TESTED_FILE_NAME).info ..\..\coverage_report\$(TESTED_FILE_NAME).info
else
	ifeq ($(shell uname), Linux)
		cp ../../apitest/src/$(TESTED_FILE_NAME).info ../../coverage_report/$(TESTED_FILE_NAME).info
	else
		$(error Platform is not supported!)
	endif
endif

### CLEAN ###
clean:
ifdef OS
	rd /s /q $(OBJ)
	del ..\..\apitest\src\*.info
	del ..\..\apitest\src\*.gcov
	del ..\..\apitest\src\*.gcda
	del ..\..\apitest\src\*.gcno
else
	ifeq ($(shell uname), Linux)
		rm -rf $(TESTED_FILE_DIR)*.info
		rm -rf $(TESTED_FILE_DIR)*.gcov
		rm -rf $(TESTED_FILE_DIR)*.gcda
		rm -rf $(TESTED_FILE_DIR)*.gcno
	else
		$(error Platform is not supported!)
	endif
endif