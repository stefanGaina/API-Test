#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   06.08.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to compile unit-test for apitest_version.c, run them and         #
# generate coverage report.                                                                           #
#######################################################################################################

INCLUDES = -I../../vendor/googletest/include/ \
		   -I../../apitest/include/

TEST_FILE_NAME   := apitest_version_test
TESTED_FILE_NAME := apitest_version
TESTED_FILE_DIR  := ../../apitest/src/
EXECUTABLE       := apitest-version-ut.exe

all: | create_dir $(EXECUTABLE)

### CREATE DIRECTORY ###
create_dir:
ifeq (Windows_NT, $(OS))
	if not exist "$(OBJ)" mkdir $(OBJ)
endif
ifeq (Linux, $(shell uname))
	mkdir -p $(OBJ)
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
ifeq (Windows_NT, $(OS))
	copy $(OBJ)\$(TESTED_FILE_NAME).gcda ..\..\apitest\src
	copy $(OBJ)\$(TESTED_FILE_NAME).gcno ..\..\apitest\src
endif
ifeq (Linux, $(shell uname))
	cp $(OBJ)/$(TESTED_FILE_NAME).gcda ../../apitest/src/
	cp $(OBJ)/$(TESTED_FILE_NAME).gcno ../../apitest/src/
endif
	cd $(TESTED_FILE_DIR) && gcov -b $(TESTED_FILE_NAME).c
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --capture $(LCOV_BRANCH_FLAG) --directory . --output-file $(TESTED_FILE_NAME)_all.info
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --extract $(TESTED_FILE_NAME)_all.info "*.c" $(LCOV_BRANCH_FLAG) --output-file $(TESTED_FILE_NAME).info
ifeq (Windows_NT, $(OS))
	copy ..\..\apitest\src\$(TESTED_FILE_NAME).info ..\..\coverage_report\$(TESTED_FILE_NAME).info
endif
ifeq (Linux, $(shell uname))
	cp ../../apitest/src/$(TESTED_FILE_NAME).info ../../coverage_report/$(TESTED_FILE_NAME).info
endif

### CLEAN ###
clean:
ifeq (Windows_NT, $(OS))
	$(RM) $(OBJ)\*
	$(RM) ..\..\apitest\src\*.info
	$(RM) ..\..\apitest\src\*.gcov
	$(RM) ..\..\apitest\src\*.gcda
	$(RM) ..\..\apitest\src\*.gcno
endif
ifeq (Linux, $(shell uname))
	$(RM) $(OBJ)/*
	$(RM) $(TESTED_FILE_DIR)*.info
	$(RM) $(TESTED_FILE_DIR)*.gcov
	$(RM) $(TESTED_FILE_DIR)*.gcda
	$(RM) $(TESTED_FILE_DIR)*.gcno
endif
