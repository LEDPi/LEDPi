#sIple projects.
#
# Makefile commands:
# 	# all [default]		: rebuilds all files which have changed since  
#				  the last build.
#	# rebuild		: cleans the project and recompiles everthing
#	# clean			: deletes all generated files
################################################################################

################################################################################
# output target
TARGET = sender

################################################################################
# files to compile if you do not want to compile all .c files, just replace the
# wildcard with all files c-files you want to compile. 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)

################################################################################
# compiler settings
COMPILER = g++
COMPILER_FLAGS =

################################################################################
# linker settings 
LINKER = g++
LINKER_FLAGS = -lrt

################################################################################
# general variables
DELETE =  rm -f

################################################################################
# default rule make all
.PHONY = all rebuild clean

all: compile

rebuild: clean_int compile

clean: clean_int

################################################################################
# internal commmands 
compile: $(TARGET)

clean_int:
	$(DELETE) $(OBJ)
	$(DELETE) $(TARGET)

################################################################################
# file dependencies
$(TARGET): $(OBJ)
	$(LINKER) $(OBJ) -o $(TARGET) $(LINKER_FLAGS)

%.o : %.c
	$(COMPILER) $< -c -o $@ $(COMPILER_FLAGS)


