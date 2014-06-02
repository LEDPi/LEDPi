################################################################################
# Default makefile for sample projects.
#
# Makefile commands:
# 	# all [default]		: rebuilds all files which have changed since  
#				  the last build.
#	# rebuild		: cleans the project and recompiles everthing
#	# clean			: deletes all generated files
################################################################################

################################################################################
# output target
TARGET = led_pi
OUTPUT = bin/$(TARGET)

################################################################################
# files to compile if you do not want to compile all .c files, just replace the
# wildcard with all files c-files you want to compile. 
SRC = main.c
OBJ_PATH = bin/obj/
OBJ = $(SRC:%.c=$(OBJ_PATH)%.o)

ALL_OBJ = $(wildcard $(OBJ_PATH)*.o)
#ALL_OBJ += $(OBJ)

################################################################################
# compiler settings
COMPILER = g++
COMPILER_FLAGS = -I./ -Wno-write-strings -Os
COMPILER_FLAGS += -DDESKTOP

################################################################################
# linker settings 
LINKER = g++
LINKER_FLAGS = -lncurses -lrt -lpthread -L./bin 
LINKER_FLAGS += -lGL -lGLU -lglut

################################################################################
# general variables
DELETE =  rm -f

################################################################################
# default rule make all
.PHONY = all rebuild clean copy

all: compile_all compile copy

rebuild: clean_int compile_rebuild compile copy

clean: clean_int

################################################################################
# internal commmands 
compile_all:
	make -C ./gmm/ all
	make -C ./gui/ all
	make -C ./mux/ all
	make -C ./net/ all
	make -C ./utils/ all

compile_rebuild:
	make -C ./gmm/ rebuild
	make -C ./gui/ rebuild
	make -C ./mux/ rebuild
	make -C ./net/ rebuild
	make -C ./utils/ rebuild

compile: $(TARGET)
	$(LINKER) $(ALL_OBJ) -o $(OUTPUT) $(LINKER_FLAGS)


clean_int:
	make -C ./gmm/ clean
	make -C ./gui/ clean
	make -C ./mux/ clean
	make -C ./net/ clean
	make -C ./utils/ clean
	$(DELETE) $(OBJ)
	$(DELETE) $(OUTPUT)
	$(DELETE) $(AR_TEMP)
	$(DELETE) $(TARGET)
	$(DELETE) ./bin/obj/*

copy:
	cp $(OUTPUT) $(TARGET) 


################################################################################
# file dependencies
$(TARGET): $(OBJ)
	$(LINKER) $(ALL_OBJ) -o $(OUTPUT) $(LINKER_FLAGS)

$(OBJ_PATH)%.o : %.c
	$(COMPILER) $< -c -o $@ $(COMPILER_FLAGS)
