#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   03.06.2023  Gaina Stefan               Initial version.                                           #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
# Description: This Makefile is used to compile unit-test for dummy_library.c, run them and generate  #
# coverage report.                                                                                    #
#######################################################################################################

INCLUDES = -I../../vendor/googletest/include/ \
		   -I../../dummy-lib/include/

TEST_FILE_NAME   := dummy_library_test
TESTED_FILE_NAME := dummy_library
TESTED_FILE_DIR  := ../../dummy-lib/src/
EXECUTABLE       := dummy_library-ut.exe

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
	copy $(OBJ)\$(TESTED_FILE_NAME).gcda ..\..\dummy-lib\src
	copy $(OBJ)\$(TESTED_FILE_NAME).gcno ..\..\dummy-lib\src
endif
ifeq (Linux, $(shell uname))
	cp $(OBJ)\$(TESTED_FILE_NAME).gcda ../../dummy-lib/src/
	cp $(OBJ)\$(TESTED_FILE_NAME).gcno ../../dummy-lib/src/
endif
	cd $(TESTED_FILE_DIR) && gcov -b $(TESTED_FILE_NAME).c
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --capture $(LCOV_BRANCH_FLAG) --directory . --output-file $(TESTED_FILE_NAME)_all.info
	cd $(TESTED_FILE_DIR) && perl $(LCOV) --extract $(TESTED_FILE_NAME)_all.info "*.c" $(LCOV_BRANCH_FLAG) --output-file $(TESTED_FILE_NAME).info
ifeq (Windows_NT, $(OS))
	copy ..\..\dummy-lib\src\$(TESTED_FILE_NAME).info ..\..\coverage_report\$(TESTED_FILE_NAME).info
endif
ifeq (Linux, $(shell uname))
	cp ../../dummy-lib/src/$(TESTED_FILE_NAME).info ../../coverage_report/$(TESTED_FILE_NAME).info
endif

### CLEAN ###
clean:
ifeq (Windows_NT, $(OS))
	$(RM) $(OBJ)\*
	$(RM) ..\..\dummy-lib\src\*.info
	$(RM) ..\..\dummy-lib\src\*.gcov
	$(RM) ..\..\dummy-lib\src\*.gcda
	$(RM) ..\..\dummy-lib\src\*.gcno
endif
ifeq (Linux, $(shell uname))
	$(RM) $(OBJ)/*
	$(RM) $(TESTED_FILE_DIR)*.info
	$(RM) $(TESTED_FILE_DIR)*.gcov
	$(RM) $(TESTED_FILE_DIR)*.gcda
	$(RM) $(TESTED_FILE_DIR)*.gcno
endif
