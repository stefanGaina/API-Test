#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   02.06.2023  Gaina Stefan               Initial version.                                           #
#   02.06.2023  Gaina Stefan               Fixed copy_libraries rule.                                 #
#   03.06.2023  Gaina Stefan               Updated to support parent Makefile updates.                #
#   05.06.2023  Gaina Stefan               Fixed rules for linux.                                     #
#   06.08.2023  Gaina Stefan               Renamed linked library.                                    #
# Description: This Makefile is used to generate an example for API-Test loading a dummy library and  #
# testing its API.                                                                                    #
#######################################################################################################

CFLAGS  = -Wall -Werror
LDFLAGS = -Wl,-rpath='.' -L../apitest/$(LIB)/ -lapitest \
		  -Wl,-rpath='.' -L../dummy-lib/$(LIB)/ -ldummy

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
	$(RM) $(BIN)\*
endif
ifeq (Linux, $(shell uname))
	$(RM) $(OBJ)/*
	$(RM) $(BIN)/*
endif

### COPY LIBRARIES ###
copy_libraries:
ifeq (Windows_NT, $(OS))
	copy ..\apitest\$(LIB)\libapitest.$(LIB_EXTENSION) $(BIN)
	copy ..\dummy-lib\$(LIB)\libdummy.$(LIB_EXTENSION) $(BIN)
endif
ifeq (Linux, $(shell uname))
	cp ../apitest/$(LIB)/libapitest.$(LIB_EXTENSION) $(BIN)/
	cp ../dummy-lib/$(LIB)/libdummy.$(LIB_EXTENSION) $(BIN)/
endif
