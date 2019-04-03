#Setting the target name, this will be the name of executable
TARGET = Integrate

#Asking makefile to link the libraries
LIBS = -lm

#Setting the compiler
CC = gcc
#Enabling few flags -g is for the debug build while -Wall enables the warnings to be handled 
#I chose to use -g because I was working on a TRACE which would print every debud statement as we don't have a
#debugger in place

CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

#I am using wildcard and patsubst from Make to include every .c and .h files in the current directory
#to compile and be linked togather

#The advantage is I don't have to mention separate .c and .h everytime I choose to create one
#This handles it all
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

#Actual linking to the library
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

#Cleaning all the .o and executable on make clean
clean:
	-rm -f *.o
	-rm -f $(TARGET)
