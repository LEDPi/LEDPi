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
# files to compile if you do not want to compile all .c files, just replace the
# wildcard with all files c-files you want to compile. 
SRC = mono.c gmm.c snake.c snake_maps.c photo.c photo_photo.c plasma.c ball.c
OBJ_PATH = ../bin/obj/
OBJ = $(SRC:%.c=$(OBJ_PATH)%.o)

################################################################################
# compiler settings
COMPILER = g++
COMPILER_FLAGS = -I../ -Wno-write-strings -D DEBUG_NET -Os

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
compile: $(OBJ)

clean_int:
	$(DELETE) $(OBJ)

################################################################################
# file dependencies

$(OBJ_PATH)%.o : %.c
	$(COMPILER) $< -c -o $@ $(COMPILER_FLAGS)
