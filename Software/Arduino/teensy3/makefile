################################################################################
# Compiles the modified teensy library for the LED Pi Project.1
#
# Makefile commands:
# 	# all [default]	: rebuilds all files which have changed since  
#				  		the last build.
#	# rebuild		: cleans the project and recompiles everthing
#	# clean			: deletes all generated files
################################################################################

################################################################################
# needed to set the compilers include paths correctly. Must be an absolute path.
TEENSY_FOLDER = C:/Projects/Arduino/LEDTeensy/teensy3

################################################################################
# files to compile if you do not want to compile all .c files, just replace the
# wildcard with all files c-files you want to compile. 
SRC_C   =  $(wildcard *.c)
SRC_CPP =  $(wildcard *.cpp)

OBJ_PATH = ../bin/obj/
OBJ = $(SRC_C:%.c=$(OBJ_PATH)%.c.o) $(SRC_CPP:%.cpp=$(OBJ_PATH)%.cpp.o)

################################################################################
# compiler settings
COMPILER_C   = C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-gcc
COMPILER_CPP = C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-g++
COMPILER_C_FLAGS =  -c -g -Os -Wall -ffunction-sections -fdata-sections -mcpu=cortex-m4 -DF_CPU=96000000 -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=118 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -I$(TEENSY_FOLDER)
COMPILER_CPP_FLAGS = -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mcpu=cortex-m4 -DF_CPU=96000000 -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=118 -fno-rtti -felide-constructors -std=gnu++0x -DUSB_SERIAL -DLAYOUT_US_ENGLISH -I$(TEENSY_FOLDER)

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

$(OBJ_PATH)%.c.o : %.c
	$(COMPILER_C) $(COMPILER_C_FLAGS) $< -o $@ 

$(OBJ_PATH)%.cpp.o : %.cpp
	$(COMPILER_CPP) $(COMPILER_CPP_FLAGS) $< -o $@