#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

FORMAT			  := clang-format -i
COMPILATION_TIMER := cd vendor/Compilation-Timer && ./compilation-timer

### MAKE SUBDIRECTORIES ###
all: start_timer format build doxygen end_timer

build:
	$(MAKE) -C apitest
	$(MAKE) -C dummy-lib
	$(MAKE) -C test

### CLEAN SUBDIRECTORIES ###
clean: start_timer
	$(MAKE) clean -C apitest
	$(MAKE) clean -C dummy-lib
	$(MAKE) clean -C test
	$(COMPILATION_TIMER) end

### MAKE UNIT-TESTS ###
ut: start_timer ut-clean
	$(FORMAT) unit-tests/*/*/*/*.cpp
	$(FORMAT) unit-tests/*/*.hpp
	$(MAKE) -C unit-tests
	$(COMPILATION_TIMER) end

### CLEAN UNIT-TESTS ###
ut-clean:
	$(MAKE) clean -C unit-tests

### MAKE DOXYGEN ###
doxygen:
	doxygen docs/doxygen.conf

### MAKE FORMAT ###
format:
	$(FORMAT) apitest/src/*.c
	$(FORMAT) apitest/include/*.h
	$(FORMAT) dummy-lib/src/*.c
	$(FORMAT) dummy-lib/include/*.h
	$(FORMAT) test/src/*.c

### START TIMER ###
start_timer:
	$(COMPILATION_TIMER) start

### END TIMER ###
end_timer:
	$(COMPILATION_TIMER) end
