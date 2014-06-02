################################################################################
# Compiles the Teensy3.1 software for the LED Pi project.
#
# Makefile commands:
# 	# all [default]	: rebuilds all files which have changed since  
#				 	 the last build.
#	# rebuild		: cleans the project and recompiles everything
#	# clean			: deletes all generated files
################################################################################

################################################################################
# output target
TARGET = LEDTeensy
OUTPUT_PATH = C:/Projects/Arduino/LEDTeensy/bin/
OUTPUT = $(OUTPUT_PATH)$(TARGET)
OBJ_PATH = C:/Projects/Arduino/LEDTeensy/bin/obj/

################################################################################
# needed to set the compilers include paths correctly. Must be an absolute path.
TEENSY_FOLDER = C:/Projects/Arduino/LEDTeensy/teensy3

################################################################################
# files to compile if you do not want to compile all .c files, just replace the
# wildcard with all files c-files you want to compile. 
SRC_C   = mux.c shift.c shiftmgr.c default.c
SRC_CPP =  main.cpp

#SRC_C   =  $(wildcard *.c)
#SRC_CPP =  $(wildcard *.cpp)

OBJ = $(SRC_C:%.c=$(OBJ_PATH)%.c.o) $(SRC_CPP:%.cpp=$(OBJ_PATH)%.cpp.o)

################################################################################
# compiler settings
COMPILER_C   = C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-gcc
COMPILER_CPP = C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-g++
OBJCOPY =  C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-objcopy
SIZE = C:/Program Files (x86)/Arduino/hardware/tools/arm-none-eabi/bin/arm-none-eabi-size
COMPILER_C_FLAGS =  -c -g -Os -Wall -ffunction-sections -fdata-sections -mcpu=cortex-m4 -DF_CPU=96000000 -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=118 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -I$(TEENSY_FOLDER)
COMPILER_CPP_FLAGS = -pedantic -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mcpu=cortex-m4 -DF_CPU=96000000 -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -mthumb -nostdlib -D__MK20DX256__ -DTEENSYDUINO=118 -fno-rtti -felide-constructors -std=gnu++0x -DUSB_SERIAL -DLAYOUT_US_ENGLISH -I$(TEENSY_FOLDER)

ALL_OBJ = $(wildcard $(OBJ_PATH)*.o)
#ALL_OBJ += $(OBJ_PATH)shift.c.o $(OBJ_PATH)shiftmgr.c.o

################################################################################
# linker settings 
LINKER = $(COMPILER_CPP)
LINKER_FLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -T$(TEENSY_FOLDER)/mk20dx256.ld
LIBS =  -lc -lgcc -lm

################################################################################
# teensy settings
TEENSY_POST_COMPILE = C:/Program Files (x86)/Arduino/hardware/tools/teensy_post_compile
TEENSY_REBOOT = C:/Program Files (x86)/Arduino/hardware/tools/teensy_reboot

# It is important to use the short dos style path name for this path. To get the
# short name use the script "shortpath.bat" found in the documents/srcipts 
# folder.
TOOLSPATH = C:\PROGRA~2\Arduino\hardware\tools\

################################################################################
# general variables
DELETE =  rm -f

################################################################################
# default rule make all
.PHONY = all rebuild clean

all: compile_all compile load

rebuild: clean_int compile_rebuild compile load

clean: clean_int

################################################################################
# internal commmands 
compile_all:
	make -C ./teensy3/ all
	
compile_rebuild:
	make -C ./teensy3/ rebuild 

compile: $(OUTPUT).hex

clean_int:
	make -C ./teensy3/ clean
	$(DELETE) $(OBJ_PATH)*
	$(DELETE) $(OUTPUT).hex
	$(DELETE) $(OUTPUT).elf

load:
	$(TEENSY_POST_COMPILE) -file=$(TARGET) -path=$(OUTPUT_PATH) -tools=$(TOOLSPATH)
	$(TEENSY_REBOOT)
	
################################################################################
# file dependencies

$(OUTPUT).hex: $(OUTPUT).elf	
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	
$(OUTPUT).elf: $(OBJ)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(ALL_OBJ) $(LIBS)
	
$(OBJ_PATH)%.c.o : %.c
	$(COMPILER_CPP) $(COMPILER_CPP_FLAGS) $< -o $@ 

$(OBJ_PATH)%.cpp.o : %.cpp
	$(COMPILER_CPP) $(COMPILER_CPP_FLAGS) $< -o $@
