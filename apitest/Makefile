#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated to support the creation of "apitest" directory.    #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
# Description: This Makefile is used to generate the API-Test library.                                #
#######################################################################################################

CFLAGS = -Wall -Werror -Wpointer-arith -fPIC

INCLUDES = -Iinclude/

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
LIBRARY := libapitest.$(LIB_EXTENSION)

all: | create_dirs $(LIBRARY)

### CREATE DIRECTORIES ###
create_dirs:
ifeq (Windows_NT, $(OS))
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(LIB)" mkdir $(LIB)
endif
ifeq (Linux, $(shell uname))
	mkdir -p $(OBJ)
	mkdir -p $(LIB)
endif

### BINARIES ###
$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(LIB)/$@ $^

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
ifeq (Windows_NT, $(OS))
	$(RM) $(OBJ)\*
	$(RM) $(LIB)\*
endif
ifeq (Linux, $(shell uname))
	$(RM) $(OBJ)/*
	$(RM) $(LIB)/*
endif
