#######################################################################################################
# Copyright (C) API-Test 2024                                                                         #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated to support parent Makefile updates.                #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
#   03.01.2024  Gaina Stefan               Added Glib.                                                #
# Description: This Makefile is used to generate a dummy library with different types as parameters   #
# to test the API-Test functionalities.                                                               #
#######################################################################################################

CFLAGS = `pkg-config --cflags glib-2.0` -Wall -Werror -fPIC

INCLUDES = -Iinclude/

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
LIBRARY := libdummy.so

all: | create_dirs $(LIBRARY)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
	mkdir -p $(LIB)

### BINARIES ###
$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(LIB)/$@ $^

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	rm -rf $(OBJ)/*
	rm -rf $(LIB)/*
