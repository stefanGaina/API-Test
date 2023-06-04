#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   02.06.2023  Gaina Stefan               Fixed copy_libraries rule.                                 #
#   03.06.2023  Gaina Stefan               Updated to support parent Makefile updates.                #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
# Description: This Makefile is used to generate an example for API-Test loading a dummy library and  #
# testing its API.                                                                                    #
#######################################################################################################

CFLAGS  = -Wall -Werror
LDFLAGS = -Wl,-rpath='.' -L../apitest/lib/ -lapitest \
		  -Wl,-rpath='.' -L../dummy-lib/lib/ -ldummy

INCLUDES = -I../apitest/include/ \
		   -I../dummy-lib/include/

SOURCES    := $(wildcard $(SRC)/*.c)
OBJECTS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := apitest-test.exe

all: | create_dirs $(EXECUTABLE) copy_libraries

### CREATE DIRECTORIES ###
create_dirs:
ifeq (Windows_NT, $(OS))
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(BIN)" mkdir $(BIN)
endif
ifeq (Linux, $(shell uname))
	mkdir -p $(OBJ)
	mkdir -p $(BIN)
endif

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

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

### COPY LIBRARIES ###
copy_libraries:
ifeq (Windows_NT, $(OS))
	copy ..\apitest\lib\libapitest.$(LIB_EXTENSION) bin
	copy ..\dummy-lib\lib\libdummy.$(LIB_EXTENSION) bin
endif
ifeq (Linux, $(shell uname))
	cp ../apitest/lib/libapitest.$(LIB_EXTENSION) bin/
	cp ../dummy-lib/lib/libdummy.$(LIB_EXTENSION) bin/
endif
