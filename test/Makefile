#######################################################################################################
# Copyright (C) API-Test 2024                                                                         #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   02.06.2023  Gaina Stefan               Fixed copy_libraries rule.                                 #
#   03.06.2023  Gaina Stefan               Updated to support parent Makefile updates.                #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
#   06.08.2023  Gaina Stefan               Renamed linked library.                                    #
#   03.01.2024  Gaina Stefan               Added Glib.                                                #
# Description: This Makefile is used to generate an example for API-Test loading a dummy library and  #
# testing its API.                                                                                    #
#######################################################################################################

CFLAGS  = `pkg-config --cflags glib-2.0` -Wall -Werror
LDFLAGS = `pkg-config --libs glib-2.0`                                                        \
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/../../apitest/$(LIB) -L../apitest/$(LIB)/ -lapitest \
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/../../dummy-lib/$(LIB) -L../dummy-lib/$(LIB)/ -ldummy

INCLUDES = -I../apitest/include \
		   -I../dummy-lib/include

SOURCES    := $(wildcard $(SRC)/*.c)
OBJECTS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
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
