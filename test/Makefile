#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   02.06.2023  Gaina Stefan               Fixed copy_libraries rule.                                 #
# Description: This Makefile is used to generate an example for API-Test loading a dummy library and  #
# testing its API.                                                                                    #
#######################################################################################################

CC      = gcc
CFLAGS  = -Wall -Werror
LDFLAGS = -L../apitest/lib/ -lapitest \
		  -L../dummy-lib/lib/ -ldummy

SRC := src
OBJ := obj
BIN := bin

INCLUDES = -I../apitest/inc/ \
		   -I../dummy-lib/inc/

SOURCES    := $(wildcard $(SRC)/*.c)
OBJECTS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := apitest-test.exe

all: | create_dirs $(EXECUTABLE) copy_libraries

### CREATE DIRS ###
create_dirs:
ifdef OS
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(BIN)" mkdir $(BIN)
else
	ifeq ($(shell uname), Linux)
		mkdir -p $(OBJ)
		mkdir -p $(BIN)
	else
		$(error Platform is not supported!)
	endif
endif

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN)/$@ $^

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
ifdef OS
	rd /s /q $(OBJ)
	rd /s /q $(BIN)
else
	ifeq ($(shell uname), Linux)
		rm -rf $(OBJ)/*
		rm -rf $(BIN)/*
	else
		$(error Platform is not supported!)
	endif
endif

### COPY LIBRARIES ###
copy_libraries:
ifdef OS
	copy ..\apitest\lib\libapitest.dll bin
	copy ..\dummy-lib\lib\libdummy.dll bin
else
	ifeq ($(shell uname), Linux)
		cp ../apitest/lib/libapitest.so bin/
		cp ../dummy-lib/lib/libdummy.so bin/
	else
		$(error Platform is not supported!)
	endif
endif
