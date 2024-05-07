#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 02.06.2023
# Description: This Makefile is used to generate an example for API-Test loading a dummy library and
# testing its API.
#######################################################################################################

CFLAGS	:= `pkg-config --cflags glib-2.0` -Wall -Werror
LDFLAGS := `pkg-config --libs glib-2.0`														  \
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/../../apitest/$(LIB) -L../apitest/$(LIB)/ -lapitest \
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/../../dummy-lib/$(LIB) -L../dummy-lib/$(LIB)/ -ldummy

INCLUDES := -I../apitest/include \
			-I../dummy-lib/include

SOURCES	   := $(wildcard $(SRC)/*.c)
OBJECTS	   := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := apitest-test

all: | create_dirs $(EXECUTABLE)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	rm -rf $(OBJ)/*
	rm -rf $(BIN)/*
