#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   03.06.2023  Gaina Stefan               Updated to support parent Makefile updates.                #
# Description: This Makefile is used to generate a dummy library with different types as parameters   #
# to test the API-Test functionalities.                                                               #
#######################################################################################################

CFLAGS = -Wall -Werror -Wpointer-arith -fPIC

INCLUDES = -Iinclude/

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

ifdef OS
	LIBRARY := libdummy.dll
else
	ifeq ($(shell uname), Linux)
		LIBRARY := libdummy.so
	else
		$(error Platform is not supported!)
	endif
endif

all: | create_dirs $(LIBRARY)

### CREATE DIRECTORIES ###
create_dirs:
ifdef OS
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(LIB)" mkdir $(LIB)
else
	ifeq ($(shell uname), Linux)
		mkdir -p $(OBJ)
		mkdir -p $(LIB)
	else
		$(error Platform is not supported!)
	endif
endif

### BINARIES ###
$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(LIB)/$@ $^

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
ifdef OS
	rd /s /q $(OBJ)
	rd /s /q $(LIB)
else
	ifeq ($(shell uname), Linux)
		rm -rf $(OBJ)/*
		rm -rf $(LIB)/*
	else
		$(error Platform is not supported!)
	endif
endif
