#Compiler
CC = gcc

#Compiler Flags  
CFLAGS  = 

#Special Flag OpenGl

OPGL = -lglut -lGL -lGLU -lGLEW

#Source .c files
SRC = main.c mux.c graphic.c

#Object files
OBJS = $(SRC:.c=.o)

#Define executable
MAIN = prog

#Generic Compile Part

.PHONY: depend clean

all:    $(MAIN)
        

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(OPGL) -o $(MAIN)  
	#$(CC) $(CFLAGS) -c $<  -o  $@
	$(RM) *.o *~

clean:
	$(RM) *.o *~ $(MAIN)

